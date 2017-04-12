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

		static _CrtMemState sStartMemState;
	};
	_CrtMemState EventTest::sStartMemState;
}