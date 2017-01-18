#include "pch.h"
#include "CppUnitTest.h"
#include <SList.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(SListTest)
	{
	public:
		/**
		 * Sets up leak detection logic
		 */
		static void initializeLeakDetection()
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}
		
		/**
		 * Detects if memory state has been corrupted
		 */
		static void finalizeLeakDetection()
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			// Initialize data needed for every test
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			// Cleanup class level data
		}

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			initializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			finalizeLeakDetection();
		}

		TEST_METHOD(TestPushPopFront)
		{
			SList<int> list{};
			auto iterations = 100;

			for (int i = 0; i < iterations; i++)
			{
				list.pushFront(i);
			}

			for (int i = iterations-1; i >= 0; i--)
			{
				Assert::AreEqual(i, list.popFront());
			}
		}

		TEST_METHOD(TestPushBackSequence)
		{
			SList<int> list{};
			auto iterations = 100;

			for (int i = 0; i < iterations; i++)
			{
				list.pushBack(i);
			}

			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, list.popFront());
			}
		}

		TEST_METHOD(TestIsEmptyAfterPop)
		{
			SList<int> list{};
			Assert::IsTrue(list.isEmpty());

			list.pushFront(1);
			list.popFront();
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(TestFront)
		{
			SList<int> list{};

			list.pushFront(1);
			Assert::AreEqual(1, list.front());

			list.pushBack(2);
			Assert::AreEqual(1, list.front());

			list.popFront();
			Assert::AreEqual(2, list.front());

			list.front() = 5;
			Assert::AreEqual(5, list.front());
		}

		TEST_METHOD(TestBack)
		{
			SList<int> list{};

			list.pushFront(1);
			Assert::AreEqual(1, list.back());

			list.pushBack(2);
			Assert::AreEqual(2, list.back());
		}

		TEST_METHOD(TestSize)
		{
			SList<int> list{};
			Assert::AreEqual(0, list.size());

			list.pushFront(1);
			Assert::AreEqual(1, list.size());

			list.pushBack(2);
			Assert::AreEqual(2, list.size());

			list.popFront();
			Assert::AreEqual(1, list.size());

			list.popFront();
			Assert::AreEqual(0, list.size());
		}

		TEST_METHOD(TestCopy)
		{
			SList<int> oldList{};
			auto iterations = 10;

			for (auto i = 0; i < iterations; i++)
			{
				oldList.pushBack(i);
			}

			auto newList(oldList);

			while (!oldList.isEmpty())
			{
				auto expected = oldList.popFront();
				auto actual = newList.popFront();
				Assert::AreEqual(expected, actual);
			}
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			SList<int> list{};
			list.pushFront(1);
			list.pushFront(2);
			list.pushFront(3);

			SList<int> newList{};
			newList = list;

			for (int i = 0; i < list.size(); i++)
			{
				auto expected = list.popFront();
				auto result = newList.popFront();
				Assert::AreEqual(expected, result, L"List values do not match");
			}
		}

		TEST_METHOD(TestClear)
		{
			SList<int> list{};
			
			list.pushFront(1);
			list.clear();

			Assert::AreEqual(0, list.size());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}