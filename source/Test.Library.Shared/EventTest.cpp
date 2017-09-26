#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "TestSharedData.h"
#include "GameTime.h"
#include "Event.h"
#include "EventQueue.h"
#include "MyEventSubscriber.h"
#include "Foo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
using namespace std::chrono;


namespace TestLibraryDesktop
{
	TEST_CLASS(EventTest)
	{
	public:

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			LeakDetector::Initialize();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			LeakDetector::Finalize();
			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(TestSubscriberNotify)
		{
			Foo foo(1);
			Event<Foo> myEvent(foo);
			MyEventSubscriber subscriber;

			Assert::IsFalse(foo == subscriber.mValue);
			subscriber.Notify(myEvent);
			Assert::IsTrue(foo == subscriber.mValue);
		}

		TEST_METHOD(TestEventQueue)
		{
			GameTime gameTime;
			EventQueue eq;

			Foo foo(5);
			Event<Foo> myEvent(foo);
			eq.Enqueue(myEvent, gameTime);

			eq.Update(gameTime);
			Assert::IsFalse(eq.IsEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1)));
			eq.Update(gameTime);
			Assert::IsTrue(eq.IsEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			myEvent.SetTime(gameTime.CurrentTime(), milliseconds(100));
			eq.Enqueue(myEvent, gameTime);

			MyEventSubscriber subscriber;
			eq.Update(gameTime);
			Assert::IsFalse(eq.IsEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1000)));
			Assert::IsFalse(foo == subscriber.mValue);
			Assert::IsFalse(myEvent.Message() == subscriber.mValue);
			
			eq.Update(gameTime);
			Assert::IsTrue(eq.IsEmpty());
			Assert::IsTrue(foo == subscriber.mValue);
			Assert::IsTrue(myEvent.Message() == subscriber.mValue);
		}

		TEST_METHOD(TestSubscribe)
		{
			GameTime gameTime;

			Foo foo(5);
			Event<Foo> myevent(foo);

			MyEventSubscriber subscriber;
			Assert::IsFalse(subscriber.mValue == foo);
			
			myevent.Deliver();
			Assert::IsTrue(subscriber.mValue == foo);

			myevent.SetTime(gameTime.CurrentTime(), milliseconds(10));
			subscriber.mValue = Foo(0);
			Assert::IsFalse(subscriber.mValue == foo);

			myevent.Deliver();
			Assert::IsTrue(subscriber.mValue == foo);
		}

		TEST_METHOD(TestQueueDelay)
		{
			GameTime gameTime;

			Foo foo(5);
			Event<Foo> myEvent(foo);

			MyEventSubscriber subscriber;
			Assert::IsFalse(subscriber.mValue == foo);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			myEvent.SetTime(gameTime.CurrentTime(), milliseconds(100));

			EventQueue queue;
			queue.Enqueue(myEvent, gameTime, myEvent.Delay());

			Assert::IsFalse(queue.IsEmpty());
			Assert::IsFalse(subscriber.mValue == foo);

			queue.Update(gameTime);
			Assert::IsFalse(queue.IsEmpty());
			Assert::IsFalse(subscriber.mValue == foo);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(99)));
			queue.Update(gameTime);
			Assert::IsFalse(queue.IsEmpty());
			Assert::IsFalse(subscriber.mValue == foo);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(201)));
			queue.Update(gameTime);
			Assert::IsTrue(queue.IsEmpty());
			Assert::IsTrue(subscriber.mValue == foo);
		}

		TEST_METHOD(TestSend)
		{
			EventQueue queue;

			MyEventSubscriber subscriber;
			Foo foo(5);
			Event<Foo> myEvent(foo);

			Assert::IsFalse(subscriber.mValue == foo);
			Assert::IsFalse(myEvent.Message() == subscriber.mValue);

			queue.Send(myEvent);
			Assert::IsTrue(subscriber.mValue == foo);
			Assert::IsTrue(myEvent.Message() == subscriber.mValue);
		}

		TEST_METHOD(TestEventQueueClear)
		{
			EventQueue queue;
			Assert::IsTrue(queue.IsEmpty());

			Event<Foo> event(Foo(5));
			GameTime gameTime;
			queue.Enqueue(event, gameTime, milliseconds(0));
			Assert::IsFalse(queue.IsEmpty());

			queue.Clear();
			Assert::IsTrue(queue.IsEmpty());

			queue.Clear();
			Assert::IsTrue(queue.IsEmpty());

			queue.Enqueue(event, gameTime, milliseconds(0));
			Assert::IsFalse(queue.IsEmpty());

			queue.Clear();
			Assert::IsTrue(queue.IsEmpty());
		}

		TEST_METHOD(TestEventQueueSize)
		{
			EventQueue queue;
			Assert::AreEqual(0u, queue.Size());

			Event<Foo> event(Foo(5));
			GameTime gameTime;
			queue.Enqueue(event, gameTime, milliseconds(0));
			Assert::AreEqual(1u, queue.Size());

			queue.Enqueue(event, gameTime, milliseconds(0));
			Assert::AreEqual(1u, queue.Size());
		}

		TEST_METHOD(TestDeleteAfterPublishing)
		{
			Event<Foo>* event = new Event<Foo>(Foo(5), true);
			Assert::IsTrue(event->DeleteAfterPublishing());
			EventQueue queue;
			GameTime gameTime;
			queue.Enqueue(*event, gameTime, milliseconds(0));
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1)));
			queue.Update(gameTime);
			Assert::IsTrue(queue.IsEmpty());

			Event<Foo>* hangingEvent = new Event<Foo>(Foo(5), true);
			Assert::IsTrue(hangingEvent->DeleteAfterPublishing());
			queue.Enqueue(*hangingEvent, gameTime, milliseconds(0));
			Assert::IsFalse(queue.IsEmpty());

			Event<Foo> dontDeleteMeBro(Foo(5));
			Event<Foo> dontDeleteMeExplicit(Foo(5), false);
			Assert::IsFalse(dontDeleteMeBro.DeleteAfterPublishing());
			Assert::IsFalse(dontDeleteMeExplicit.DeleteAfterPublishing());
		}

		TEST_METHOD(TestTimeEnqueuedAndDelay)
		{
			Event<Foo> event(Foo(5));
			EventQueue queue;
			GameTime time;
			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(10)));

			Assert::IsFalse(time.CurrentTime() == event.TimeEnqueued());
			Assert::IsTrue(event.Delay() == milliseconds(0));

			queue.Enqueue(event, time, milliseconds(10));
			Assert::IsTrue(time.CurrentTime() == event.TimeEnqueued());
			Assert::IsTrue(event.Delay() == milliseconds(10));
			
			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(500)));
			Assert::IsFalse(time.CurrentTime() == event.TimeEnqueued());
			Assert::IsTrue(event.Delay() == milliseconds(10));
		}

		TEST_METHOD(TestCopySemantics)
		{
			Event<Foo> eventOG(Foo(5));
			Event<Foo> eventCopy(Foo(1));
			Assert::IsFalse(eventOG.Message() == eventCopy.Message());

			eventCopy = eventOG;
			Assert::IsTrue(eventOG.Message() == eventCopy.Message());

			Event<Foo> eventCopy2(eventOG);
			Assert::IsTrue(eventOG.Message() == eventCopy2.Message());

			Event<Foo> movedEvent(Foo(1));
			movedEvent = std::move(eventOG);
			Assert::IsTrue(movedEvent.Message() == Foo(5));

			Event<Foo> movedCopyEvent(std::move(movedEvent));
			Assert::IsTrue(movedCopyEvent.Message() == Foo(5));

			Event<Foo> selfAssignmentEvent(Foo(15));
			selfAssignmentEvent = selfAssignmentEvent;
			Assert::IsTrue(selfAssignmentEvent.Message() == Foo(15));

			selfAssignmentEvent = std::move(selfAssignmentEvent);
			Assert::IsTrue(selfAssignmentEvent.Message() == Foo(15));
		}

		TEST_METHOD(TestPartitioning)
		{
			EventQueue queue;
			Event<Foo> event1(Foo(1));
			Event<Foo> event2(Foo(2));
			Event<Foo> event3(Foo(3));
			Event<Foo> event4(Foo(4));

			GameTime time;
			queue.Enqueue(event1, time, milliseconds(0));
			queue.Enqueue(event2, time, milliseconds(10));
			queue.Enqueue(event3, time, milliseconds(0));
			queue.Enqueue(event4, time, milliseconds(10));

			MyEventSubscriber sub1;

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1)));
			Assert::IsTrue(queue.Size() == 4);

			queue.Update(time);
			Assert::IsTrue(queue.Size() == 2);
			Assert::IsTrue(sub1.mValue == Foo(1) || sub1.mValue == Foo(2) || sub1.mValue == Foo(3) || sub1.mValue == Foo(4));
		}

	};

}