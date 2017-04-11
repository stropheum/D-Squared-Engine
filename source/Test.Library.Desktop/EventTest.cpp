#include "pch.h"
#include "CppUnitTest.h"
#include "TestSharedData.h"
#include "GameTime.h"
#include "Event.h"
#include "EventQueue.h"
#include "MyEventSubscriber.h"


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
		}

		TEST_METHOD(TestSubscriberNotify)
		{
			std::int32_t i = 1;
			Event<std::int32_t> myEvent(i);
			MyEventSubscriber subscriber;

			Assert::AreNotEqual(1, subscriber.mValue);
			subscriber.notify(myEvent);
			Assert::AreEqual(1, subscriber.mValue);
		}

		TEST_METHOD(TestEventQueue)
		{
			GameTime gameTime;
			EventQueue eq;

			std::int32_t i = 5;
			Event<std::int32_t> myEvent(i);
			eq.enqueue(myEvent, gameTime);

			eq.update(gameTime);
			Assert::IsFalse(eq.isEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1000)));
			eq.update(gameTime);
			Assert::IsTrue(eq.isEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			myEvent.setTime(gameTime.CurrentTime(), milliseconds(100));
			eq.enqueue(myEvent, gameTime);

			MyEventSubscriber subscriber;
			eq.update(gameTime);
			Assert::IsFalse(eq.isEmpty());

			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(1000)));
			Assert::AreNotEqual(i, subscriber.mValue);
			Assert::AreNotEqual(myEvent.message(), subscriber.mValue);
			
			eq.update(gameTime);
			Assert::IsTrue(eq.isEmpty());
			Assert::AreEqual(i, subscriber.mValue);
			Assert::AreEqual(myEvent.message(), subscriber.mValue);
		}

		TEST_METHOD(TestSubscribe)
		{
			GameTime gameTime;

			int i = 5;
			Event<std::int32_t> myevent(i);

			MyEventSubscriber subscriber;
			Assert::IsFalse(subscriber.mValue == i);
			
			myevent.deliver();
			Assert::IsTrue(subscriber.mValue == i);

			myevent.setTime(gameTime.CurrentTime(), milliseconds(10));
			subscriber.mValue = 0;
			Assert::IsFalse(subscriber.mValue == i);

			myevent.deliver();
			Assert::IsTrue(subscriber.mValue == i);
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState EventTest::sStartMemState;
}