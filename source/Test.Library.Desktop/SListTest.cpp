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

		TEST_METHOD(TestPushPopFrontSingle)
		{	
			SList<int> list{};

			list.pushFront(1);
			Assert::AreEqual(1, list.popFront(), L"Single pop front failed");
		}

		TEST_METHOD(TestPushPopFrontSequence)
		{
			SList<int> list{};
			auto iterations = 100;

			for (auto i = 0; i < iterations; i++)
			{
				list.pushFront(i);
			}

			for (auto i = iterations-1; i >= 0; i--)
			{
				Assert::AreEqual(i, list.popFront());
			}
		}

		TEST_METHOD(TestPushBackSingle)
		{
			SList<int> list{};

			list.pushBack(10);
			Assert::AreEqual(10, list.popFront());
		}

		TEST_METHOD(TestPushBackSequence)
		{
			SList<int> list{};
			auto iterations = 100;

			for (auto i = 0; i < iterations; i++)
			{
				list.pushBack(i);
			}

			for (auto i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, list.popFront());
			}
		}

		TEST_METHOD(TestIsEmptyInitial)
		{
			SList<int> list{};
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(TestIsEmptyAfterPop)
		{
			SList<int> list{};
			list.pushFront(1);
			list.popFront();
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(TestFrontAfterPushFront)
		{
			SList<int> list{};
			list.pushFront(1);
			Assert::AreEqual(1, list.front());
		}

		TEST_METHOD(TestFrontAfterPushBack)
		{
			SList<int> list{};
			list.pushBack(1);
			Assert::AreEqual(1, list.front());
		}

		TEST_METHOD(TestFrontAfterPop)
		{
			SList<int> list{};
			list.pushFront(1);
			list.pushFront(2);
			list.popFront();
			Assert::AreEqual(1, list.front());
		}

		TEST_METHOD(TestBackAfterPushFrontSingle)
		{
			SList<int> list{};
			list.pushFront(1);
			Assert::AreEqual(1, list.back());
		}

		TEST_METHOD(TestBackAfterPushBackSingle)
		{
			SList<int> list{};
			list.pushBack(1);
			Assert::AreEqual(1, list.back());
		}

		TEST_METHOD(TestInitialSize)
		{
			SList<int> list{};
			Assert::AreEqual(0, list.size());
		}

		TEST_METHOD(TestSizeAfterPushFrontSingle)
		{
			SList<int> list{};
			list.pushFront(1);
			Assert::AreEqual(1, list.size());
		}

		TEST_METHOD(TestSizeAfterPushFrontMultiple)
		{
			SList<int> list{};
			for (auto i = 0; i < 10; i++)
			{
				list.pushFront(i);
			}
			Assert::AreEqual(10, list.size());
		}

		TEST_METHOD(TestSizeAfterPushBackSingle)
		{
			SList<int> list{};
			list.pushBack(1);
			Assert::AreEqual(1, list.size());
		}

		TEST_METHOD(TestSizeAfterPushBackMultiple)
		{
			SList<int> list{};
			for (auto i = 0; i < 10; i++)
			{
				list.pushBack(i);
			}
			Assert::AreEqual(10, list.size());
		}

		TEST_METHOD(TestSizeAfterPop)
		{
			SList<int> list{};
			list.pushFront(1);
			list.pushBack(1);
			list.popFront();
			Assert::AreEqual(1, list.size());
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

			Assert::AreEqual(oldList.front(), newList.front());
			for (auto i = 0; i < iterations; i++)
			{
				
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

//			Assert::AreEqual(list.size(), newList.size(), L"Copied list has different size");

			for (auto i = 0; i < list.size(); i++)
			{
				auto expected = list.popFront();
				auto result = newList.popFront();
				Assert::AreEqual(expected, result, L"List values do not match");
			}
		}

		TEST_METHOD(TestListSizeOnClear)
		{
			SList<int> list{};
			list.pushFront(1);
			list.clear();
			Assert::AreEqual(0, list.size());
		}

		TEST_METHOD(TestFrontNullOnClear)
		{
			SList<int> list{};
			list.pushFront(1);
			list.clear();
			Assert::AreEqual(0, list.front());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}