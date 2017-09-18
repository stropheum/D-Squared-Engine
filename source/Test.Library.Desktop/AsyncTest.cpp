#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "TestSharedData.h"
#include "Datum.h"
#include "GameTime.h"
#include "Factory.h"
#include "Entity.h"
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionListIf.h"
#include "ActionIncrement.h"
#include "Event.h"
#include "Foo.h"
#include "MyEventSubscriber.h"
#include "IntEventSubscriber.h"
#include "ListClearingSubscriber.h"
#include "EnqueueSubscriber.h"
#include "QueueClearSubscriber.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
using namespace std;
using namespace std::chrono;


namespace TestLibraryDesktop
{
	TEST_CLASS(AsyncTest)
	{
	public:

		EntityFactory mEntityFactory;
		ActionListFactory mActionListFactory;
		ActionCreateActionFactory mActionCreateActionFactory;
		ActionDestroyActionFactory mActionDestroyActionFactory;
		ActionListIfFactory mActionListIfFactory;
		ActionIncrementFactory mActionIncrementFactory;

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			LeakDetector::Initialize();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			LeakDetector::Finalize();
		}

		TEST_METHOD(TestEvents)
		{
			for (int i = 0; i < 1000; i++)
			{
				EventQueue queue;
				Event<Foo> event2(Foo(2));
				Event<Foo> event3(Foo(3));
				Event<Foo> event4(Foo(4));

				GameTime time;
				queue.Enqueue(event2, time, milliseconds(10));
				queue.Enqueue(event3, time, milliseconds(0));
				queue.Enqueue(event4, time, milliseconds(10));

				MyEventSubscriber sub1;

				time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(10000000)));
				Assert::AreEqual(3u, queue.Size());

				queue.Update(time);
				std::int32_t data = sub1.mValue.getData();
				Assert::IsTrue(data == 2 || data == 3 || data == 4);
			}
		}

		TEST_METHOD(TestMultipleSubscribers)
		{
			EventQueue queue;
			Event<std::int32_t> event(10);
			GameTime time;
			queue.Enqueue(event, time, milliseconds(0));

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(500000)));
			Assert::AreEqual(1u, queue.Size());

			IntEventSubscriber sub1;
			IntEventSubscriber sub2;
			IntEventSubscriber sub3;
			IntEventSubscriber sub4; 
			IntEventSubscriber sub5;

			queue.Update(time);
			Assert::AreEqual(0u, queue.Size());

			bool notified1 = sub1.mNotified;
			bool notified2 = sub2.mNotified;
			bool notified3 = sub3.mNotified;
			bool notified4 = sub4.mNotified;
			bool notified5 = sub5.mNotified;

			int32_t val1 = sub1.mValue;
			int32_t val2 = sub2.mValue;
			int32_t val3 = sub3.mValue;
			int32_t val4 = sub4.mValue; 
			int32_t val5 = sub5.mValue;
				 
			Assert::AreEqual(true, notified1);
			Assert::AreEqual(true, notified2);
			Assert::AreEqual(true, notified3);
			Assert::AreEqual(true, notified4);
			Assert::AreEqual(true, notified5);

			Assert::AreEqual(10, val1);
			Assert::AreEqual(10, val2);
			Assert::AreEqual(10, val3);
			Assert::AreEqual(10, val4);
			Assert::AreEqual(10, val5);
		}

		TEST_METHOD(TestUnsubscribeEvent)
		{
			EventQueue queue;
			Event<Foo> event1(Foo(10));
			Event<Foo> event2(Foo(10));
			Event<Foo> event3(Foo(10));

			GameTime time;
			queue.Enqueue(event1, time, milliseconds(0));
			queue.Enqueue(event2, time, milliseconds(0));
			queue.Enqueue(event3, time, milliseconds(0));

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(500000)));
			Assert::AreEqual(3u, queue.Size());

			MyEventSubscriber eventSub;
			ListClearingSubscriber clearSub;
			queue.Update(time);
			Assert::AreEqual(0u, queue.Size());
		}

		TEST_METHOD(TestEnqueueEvent)
		{
			EventQueue queue;
			Event<std::int32_t> event1(10);
			GameTime time;
			queue.Enqueue(event1, time, milliseconds(0));
			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(50000)));
			EnqueueSubscriber sub(queue, time, milliseconds(0));
			Assert::AreEqual(1u, queue.Size());
			queue.Update(time);
			Assert::AreEqual(0u, queue.Size());
		}

		TEST_METHOD(TestClearQueue)
		{
			EventQueue queue;
			Event<Foo> event1(Foo(10));
			Event<Foo> event2(Foo(10));
			Event<Foo> event3(Foo(10));
			Event<Foo> event4(Foo(10));
			Event<Foo> event5(Foo(10));

			GameTime time;
			queue.Enqueue(event1, time, milliseconds(0));
			queue.Enqueue(event2, time, milliseconds(0));
			queue.Enqueue(event3, time, milliseconds(0));
			queue.Enqueue(event4, time, milliseconds(0));
			queue.Enqueue(event5, time, milliseconds(0));

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(50000)));

			QueueClearSubscriber sub(queue);
			Assert::AreEqual(5u, queue.Size());
			queue.Update(time);
			Assert::AreEqual(0u, queue.Size());
		}

		TEST_METHOD(TestHugeNumbers)
		{
			EventQueue queue;

			Vector<Event<Foo>> events;
			for (std::uint32_t i = 0; i < 100; i++)
			{
				events.PushBack(Event<Foo>(Foo(i)));
			}

			MyEventSubscriber sub1;
			MyEventSubscriber sub2;
			MyEventSubscriber sub3;
			MyEventSubscriber sub4;
			MyEventSubscriber sub5;
			MyEventSubscriber sub6;
			MyEventSubscriber sub7;
			MyEventSubscriber sub8;
			MyEventSubscriber sub9; 

			GameTime time;
			
			for (std::uint32_t i = 0; i < events.Size(); i++)
			{
				queue.Enqueue(events[i], time, milliseconds(0));
			}

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(50000)));

			Assert::AreEqual(100u, queue.Size());
			queue.Update(time);
			Assert::AreEqual(0u, queue.Size());
		}

	};

}