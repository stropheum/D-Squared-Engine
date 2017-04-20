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
			Event<Foo> event(Foo(10));
			GameTime time;
			queue.enqueue(event, time, milliseconds(0));

			time.SetCurrentTime(high_resolution_clock::time_point(milliseconds(500000)));
			Assert::AreEqual(1u, queue.size());

			MyEventSubscriber sub1, sub2, sub3, sub4, sub5;

			queue.update(time);
			Assert::AreEqual(0u, queue.size());

			std::int32_t val1 = sub1.mValue.getData();
			std::int32_t val2 = sub2.mValue.getData();
			std::int32_t val3 = sub3.mValue.getData();
			std::int32_t val4 = sub4.mValue.getData();
			std::int32_t val5 = sub5.mValue.getData();

			UNREFERENCED_PARAMETER(val1);
			UNREFERENCED_PARAMETER(val2);
			UNREFERENCED_PARAMETER(val3);
			UNREFERENCED_PARAMETER(val4);

			bool result = 
//				(val1 == 10) &&
//				(val2 == 10) &&
//				(val3 == 10) &&
//				(val4 == 10) &&
				(val5 == 10);
			Assert::IsTrue(result);
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState AsyncTest::sStartMemState;
}