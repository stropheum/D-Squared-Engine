#include "pch.h"
#include "CppUnitTest.h"
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

		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_DEBUG
		}

		/// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#if _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif //_DEBUG
		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			initializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			finalizeLeakDetection();
			Event<Foo>::unsubscribeAll();
		}

		TEST_METHOD(TestSubscriberNotify)
		{
			Foo foo(1);
			Event<Foo> myEvent(foo);
			MyEventSubscriber subscriber;

			Assert::IsFalse(foo == subscriber.mValue);
			subscriber.notify(myEvent);
			Assert::IsTrue(foo == subscriber.mValue);
		}

		TEST_METHOD(TestEventQueue)
		{
			GameTime gameTime;
			EventQueue eq;

			Foo foo(5);
			Event<Foo> myEvent(foo);
			eq.enqueue(myEvent, gameTime);

			eq.update(gameTime);
			Assert::IsFalse(eq.isEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1)));
			eq.update(gameTime);
			Assert::IsTrue(eq.isEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			myEvent.setTime(gameTime.CurrentTime(), milliseconds(100));
			eq.enqueue(myEvent, gameTime);

			MyEventSubscriber subscriber;
			eq.update(gameTime);
			Assert::IsFalse(eq.isEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1000)));
			Assert::IsFalse(foo == subscriber.mValue);
			Assert::IsFalse(myEvent.message() == subscriber.mValue);
			
			eq.update(gameTime);
			Assert::IsTrue(eq.isEmpty());
			Assert::IsTrue(foo == subscriber.mValue);
			Assert::IsTrue(myEvent.message() == subscriber.mValue);
		}

		TEST_METHOD(TestSubscribe)
		{
			GameTime gameTime;

			Foo foo(5);
			Event<Foo> myevent(foo);

			MyEventSubscriber subscriber;
			Assert::IsFalse(subscriber.mValue == foo);
			
			myevent.deliver();
			Assert::IsTrue(subscriber.mValue == foo);

			myevent.setTime(gameTime.CurrentTime(), milliseconds(10));
			subscriber.mValue = Foo(0);
			Assert::IsFalse(subscriber.mValue == foo);

			myevent.deliver();
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
			myEvent.setTime(gameTime.CurrentTime(), milliseconds(100));

			EventQueue queue;
			queue.enqueue(myEvent, gameTime, myEvent.delay());

			Assert::IsFalse(queue.isEmpty());
			Assert::IsFalse(subscriber.mValue == foo);

			queue.update(gameTime);
			Assert::IsFalse(queue.isEmpty());
			Assert::IsFalse(subscriber.mValue == foo);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(99)));
			queue.update(gameTime);
			Assert::IsFalse(queue.isEmpty());
			Assert::IsFalse(subscriber.mValue == foo);

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(101)));
			queue.update(gameTime);
			Assert::IsTrue(queue.isEmpty());
			Assert::IsTrue(subscriber.mValue == foo);
		}

		TEST_METHOD(TestSend)
		{
			EventQueue queue;

			MyEventSubscriber subscriber;
			Foo foo(5);
			Event<Foo> myEvent(foo);

			Assert::IsFalse(subscriber.mValue == foo);
			Assert::IsFalse(myEvent.message() == subscriber.mValue);

			queue.send(myEvent);
			Assert::IsTrue(subscriber.mValue == foo);
			Assert::IsTrue(myEvent.message() == subscriber.mValue);
		}

		TEST_METHOD(TestEventQueueClear)
		{
			EventQueue queue;
			Assert::IsTrue(queue.isEmpty());

			Event<Foo> event(Foo(5));
			GameTime gameTime;
			queue.enqueue(event, gameTime, milliseconds(0));
			Assert::IsFalse(queue.isEmpty());

			queue.clear();
			Assert::IsTrue(queue.isEmpty());

			queue.clear();
			Assert::IsTrue(queue.isEmpty());

			queue.enqueue(event, gameTime, milliseconds(0));
			Assert::IsFalse(queue.isEmpty());

			queue.clear();
			Assert::IsTrue(queue.isEmpty());
		}

		TEST_METHOD(TestEventQueueSize)
		{
			EventQueue queue;
			Assert::AreEqual(0u, queue.size());

			Event<Foo> event(Foo(5));
			GameTime gameTime;
			queue.enqueue(event, gameTime, milliseconds(0));
			Assert::AreEqual(1u, queue.size());

			queue.enqueue(event, gameTime, milliseconds(0));
			Assert::AreEqual(1u, queue.size());
		}

		TEST_METHOD(TestDeleteAfterPublishing)
		{
			Event<Foo>* event = new Event<Foo>(Foo(5), true);
			Assert::IsTrue(event->deleteAfterPublishing());
			EventQueue queue;
			GameTime gameTime;
			queue.enqueue(*event, gameTime, milliseconds(0));
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1)));
			queue.update(gameTime);
			Assert::IsTrue(queue.isEmpty());

			Event<Foo>* hangingEvent = new Event<Foo>(Foo(5), true);
			Assert::IsTrue(hangingEvent->deleteAfterPublishing());
			queue.enqueue(*hangingEvent, gameTime, milliseconds(0));
			Assert::IsFalse(queue.isEmpty());

			Event<Foo> dontDeleteMeBro(Foo(5));
			Event<Foo> dontDeleteMeExplicit(Foo(5), false);
			Assert::IsFalse(dontDeleteMeBro.deleteAfterPublishing());
			Assert::IsFalse(dontDeleteMeExplicit.deleteAfterPublishing());
		}

		TEST_METHOD(TestTimeEnqueuedAndDelay)
		{
			Event<Foo> event(Foo(5));
			EventQueue queue;
			GameTime time;
			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(10)));

			Assert::IsFalse(time.CurrentTime() == event.timeEnqueued());
			Assert::IsTrue(event.delay() == milliseconds(0));

			queue.enqueue(event, time, milliseconds(10));
			Assert::IsTrue(time.CurrentTime() == event.timeEnqueued());
			Assert::IsTrue(event.delay() == milliseconds(10));
			
			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(500)));
			Assert::IsFalse(time.CurrentTime() == event.timeEnqueued());
			Assert::IsTrue(event.delay() == milliseconds(10));
		}

		TEST_METHOD(TestCopySemantics)
		{
			Event<Foo> eventOG(Foo(5));
			Event<Foo> eventCopy(Foo(1));
			Assert::IsFalse(eventOG.message() == eventCopy.message());

			eventCopy = eventOG;
			Assert::IsTrue(eventOG.message() == eventCopy.message());

			Event<Foo> eventCopy2(eventOG);
			Assert::IsTrue(eventOG.message() == eventCopy2.message());

			Event<Foo> movedEvent = std::move(eventOG);
			Assert::IsTrue(movedEvent.message() == Foo(5));

			Event<Foo> movedCopyEvent(std::move(movedEvent));
			Assert::IsTrue(movedCopyEvent.message() == Foo(5));

			Event<Foo> selfAssignmentEvent(Foo(15));
			selfAssignmentEvent = selfAssignmentEvent;
			Assert::IsTrue(selfAssignmentEvent.message() == Foo(15));

			selfAssignmentEvent = std::move(selfAssignmentEvent);
			Assert::IsTrue(selfAssignmentEvent.message() == Foo(15));
		}

		TEST_METHOD(TestPartitioning)
		{
			EventQueue queue;
			Event<Foo> event1(Foo(1));
			Event<Foo> event2(Foo(2));
			Event<Foo> event3(Foo(3));
			Event<Foo> event4(Foo(4));

			GameTime time;
			queue.enqueue(event1, time, milliseconds(0));
			queue.enqueue(event2, time, milliseconds(10));
			queue.enqueue(event3, time, milliseconds(0));
			queue.enqueue(event4, time, milliseconds(10));

			MyEventSubscriber sub1;

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1)));
			Assert::IsTrue(queue.size() == 4);

			queue.update(time);
			Assert::IsTrue(queue.size() == 2);
			Assert::IsTrue(sub1.mValue == Foo(1) || sub1.mValue == Foo(2) || sub1.mValue == Foo(3) || sub1.mValue == Foo(4));
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState EventTest::sStartMemState;
}