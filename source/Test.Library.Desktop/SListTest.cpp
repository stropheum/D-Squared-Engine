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
			const int iterations = 100;

			for (int i = 0; i < iterations; i++)
			{
				list.pushFront(i);
			}

			for (int i = iterations-1; i >= 0; i--)
			{
				Assert::AreEqual(i, list.popFront(), L"Integer list values not equal");
			}

			SList<int*> pList{};
			int values[iterations];
			for (int i = 0; i < iterations; i++)
			{
				values[i] = i;
			}
			for (int i = 0; i < iterations; i++)
			{
				pList.pushBack(&values[i]);
			}
			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, *pList.popFront(), L"Pointer list values not equal");
			}

		}

		TEST_METHOD(TestPushBack)
		{
			SList<int> list{};
			auto iterations = 100;

			for (int i = 0; i < iterations; i++)
			{
				list.pushBack(i);
			}

			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, list.popFront(), L"Integer list values not equal");
			}
		}

		TEST_METHOD(TestIsEmptyAfterPop)
		{
			SList<int> list{};
			Assert::IsTrue(list.isEmpty(), L"List is not empty on initialization");

			list.pushFront(1);
			list.popFront();
			Assert::IsTrue(list.isEmpty(), L"List is not empty after popping last value");
		}

		TEST_METHOD(TestFront)
		{
			SList<int> list{};

			list.pushFront(1);
			Assert::AreEqual(1, list.front(), L"First item pushed is not equal to front value");

			list.pushBack(2);
			Assert::AreEqual(1, list.front(), L"Front item changed after push back called");
			
			list.popFront();
			Assert::AreEqual(2, list.front(), L"Front item incorrect after calling pop front");
			
			list.front() = 5;
			Assert::AreEqual(5, list.front(), L"Error attempting to change list.front()");

			SList<int*> pList{};
			int x = 1; 
			int y = 2; 
			int z = 3;
			pList.pushFront(&x);
			Assert::AreEqual(&x, pList.front(), L"Conflicting addresses on front after push front");
			Assert::AreEqual(1, *pList.front(), L"Conflicting values on front after push front");

			pList.pushBack(&y);
			Assert::AreEqual(&x, pList.front(), L"Conflicting addresses on front after push back");
			Assert::AreEqual(1, *pList.front(), L"Conflicting values on front after push back");

			pList.front() = &z;
			Assert::AreEqual(&z, pList.front(), L"Conflicting addresses on front after changing front directly");
			Assert::AreEqual(3, *pList.front(), L"Conflicting values on front after changing front directly");
		}

		TEST_METHOD(TestBack)
		{
			SList<int> list{};

			list.pushFront(1);
			Assert::AreEqual(1, list.back(), L"Conflicting back values after push front");

			list.pushBack(2);
			Assert::AreEqual(2, list.back(), L"Conflicting back values after push back");

			list.back() = 5;
			Assert::AreEqual(5, list.back(), L"Error attempting to change list.back()");
		}

		TEST_METHOD(TestSize)
		{
			SList<int> list{};
			Assert::AreEqual(0, list.size(), L"List size not zero on initialization");

			list.pushFront(1);
			Assert::AreEqual(1, list.size(), L"List size not accurate after pushing front");

			list.pushBack(2);
			Assert::AreEqual(2, list.size(), L"List size not accurate after pushing back");

			list.popFront();
			Assert::AreEqual(1, list.size(), L"List size not accurate after popping front");

			list.popFront();
			Assert::AreEqual(0, list.size(), L"List size not accurate after popping last value");
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
				Assert::AreEqual(expected, actual, L"Copied list contains different values from original");
			}
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			SList<int> list{};
			list.pushFront(1);
			list.pushFront(2);
			list.pushFront(3);

			SList<int> newList;
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

			Assert::AreEqual(0, list.size(), L"List size non-zero after clear");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}