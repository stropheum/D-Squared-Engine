#include "pch.h"
#include "CppUnitTest.h"
#include "TestSharedData.h"
#include "Datum.h"
#include "GameTime.h"
#include "Factory.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Action.h"
#include "ActionList.h"
#include "WorldState.h"
#include "ActionCreateAction.h"
#include "Scope.h"
#include "ActionDestroyAction.h"
#include "ActionListIf.h"
#include "SharedDataScope.h"
#include "XmlParseHelperEntity.h"
#include "ActionIncrement.h"
#include "Event.h"
#include "Foo.h"
#include "MyEventSubscriber.h"
#include "IntEventSubscriber.h"


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
				queue.enqueue(event2, time, milliseconds(10));
				queue.enqueue(event3, time, milliseconds(0));
				queue.enqueue(event4, time, milliseconds(10));

				MyEventSubscriber sub1;

				time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(10000000)));
				Assert::AreEqual(3u, queue.size());

				queue.update(time);
				std::int32_t data = sub1.mValue.getData();
				Assert::IsTrue(data == 2 || data == 3 || data == 4);
			}
		}

		TEST_METHOD(TestMultipleSubscribers)
		{
			EventQueue queue;
			Event<std::int32_t> event(10);
			GameTime time;
			queue.enqueue(event, time, milliseconds(0));

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(500000)));
			Assert::AreEqual(1u, queue.size());

			IntEventSubscriber sub1;
			IntEventSubscriber sub2;
			IntEventSubscriber sub3;
			IntEventSubscriber sub4; 
			IntEventSubscriber sub5;

			queue.update(time);
			Assert::AreEqual(0u, queue.size());

			bool notified1 = sub1.mNotified;
			bool notified2 = sub2.mNotified;
			bool notified3 = sub3.mNotified;
			bool notified4 = sub4.mNotified;
			bool notified5 = sub5.mNotified;
				 
			Assert::AreEqual(true, notified1);
			Assert::AreEqual(true, notified2);
			Assert::AreEqual(true, notified3);
			Assert::AreEqual(true, notified4);
			Assert::AreEqual(true, notified5);
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState AsyncTest::sStartMemState;
}