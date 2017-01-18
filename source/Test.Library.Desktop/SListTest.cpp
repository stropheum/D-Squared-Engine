#include "pch.h"
#include "CppUnitTest.h"
#include <SList.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(SListTest)
	{
	private:
		SList<int>* list;
		SList<int*>* pList;
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

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			initializeLeakDetection();
			list = new SList<int>();
			pList = new SList<int*>();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			delete(list);
			delete(pList);
			finalizeLeakDetection();
		}

		TEST_METHOD(TestPushPopFront)
		{
			const int iterations = 100;

			for (int i = 0; i < iterations; i++)
			{
				list->pushFront(i);
			}

			for (int i = iterations-1; i >= 0; i--)
			{
				Assert::AreEqual(i, list->popFront(), L"Integer list values not equal");
			}

			int values[iterations];
			for (int i = 0; i < iterations; i++)
			{
				values[i] = i;
				pList->pushBack(&values[i]);
			}
			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, *pList->popFront(), L"Pointer list values not equal");
			}

		}

		TEST_METHOD(TestPushBack)
		{
			const auto iterations = 100;

			for (int i = 0; i < iterations; i++)
			{
				list->pushBack(i);
			}

			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, list->popFront(), L"Integer list values not equal");
			}

			int values[iterations];
			for (int i = 0; i < iterations; i++)
			{
				values[i] = i;
				pList->pushBack(&values[i]);
			}
			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, *pList->popFront(), L"Pointer list values not equal");
			}
		}

		TEST_METHOD(TestIsEmptyAfterPop)
		{
			Assert::IsTrue(list->isEmpty(), L"Integer list is not empty on initialization");

			list->pushFront(1);
			list->popFront();
			Assert::IsTrue(list->isEmpty(), L"Integer list is not empty after popping last value");

			Assert::IsTrue(pList->isEmpty(), L"Pointer list is not empty on initialization");

			int x = 1;
			pList->pushFront(&x);
			pList->popFront();
			Assert::IsTrue(pList->isEmpty(), L"Pointer list is not empty after popping last value");
		}

		TEST_METHOD(TestFront)
		{
			list->pushFront(1);
			Assert::AreEqual(1, list->front(), L"First item pushed is not equal to front value");

			list->pushBack(2);
			Assert::AreEqual(1, list->front(), L"Front item changed after push back called");
			
			list->popFront();
			Assert::AreEqual(2, list->front(), L"Front item incorrect after calling pop front");
			
			list->front() = 5;
			Assert::AreEqual(5, list->front(), L"Error attempting to change list.front()");

			int x = 1; 
			int y = 2; 
			int z = 3;
			pList->pushFront(&x);
			Assert::AreEqual(&x, pList->front(), L"Conflicting addresses on front after push front");
			Assert::AreEqual(1, *pList->front(), L"Conflicting values on front after push front");

			pList->pushBack(&y);
			Assert::AreEqual(&x, pList->front(), L"Conflicting addresses on front after push back");
			Assert::AreEqual(1, *pList->front(), L"Conflicting values on front after push back");

			pList->front() = &z;
			Assert::AreEqual(&z, pList->front(), L"Conflicting addresses on front after changing front directly");
			Assert::AreEqual(3, *pList->front(), L"Conflicting values on front after changing front directly");
		}

		TEST_METHOD(TestBack)
		{
			list->pushFront(1);
			Assert::AreEqual(1, list->back(), L"Conflicting back values after push front");

			list->pushBack(2);
			Assert::AreEqual(2, list->back(), L"Conflicting back values after push back");

			list->back() = 5;
			Assert::AreEqual(5, list->back(), L"Error attempting to change list.back()");

			int x = 1;
			int y = 2;
			int z = 3;

			pList->pushFront(&x);
			Assert::AreEqual(&x, pList->back(), L"Conflicting back values after push front");
			Assert::AreEqual(x, *pList->back(), L"Value changed after pushing address to list");

			pList->pushBack(&y);
			Assert::AreEqual(&y, pList->back(), L"Conflicting back values after push back");
			Assert::AreEqual(y, *pList->back(), L"Back value changed after pushing back");

			pList->back() = &z;
			Assert::AreEqual(&z, pList->back(), L"Back pointer not changed after assigning directly");
			Assert::AreEqual(z, *pList->back(), L"Value corrupted after assigning back address directly");
		}

		TEST_METHOD(TestSize)
		{
			Assert::AreEqual(0, list->size(), L"List size not zero on initialization");

			list->pushFront(1);
			Assert::AreEqual(1, list->size(), L"List size not accurate after pushing front");
			list->pushBack(2);
			Assert::AreEqual(2, list->size(), L"List size not accurate after pushing back");
			list->popFront();
			Assert::AreEqual(1, list->size(), L"List size not accurate after popping front");
			list->popFront();
			Assert::AreEqual(0, list->size(), L"List size not accurate after popping last value");

			int x = 1;
			int y = 2;

			Assert::AreEqual(0, pList->size(), L"List size not zero on initialization");
			pList->pushFront(&x);
			Assert::AreEqual(1, pList->size(), L"List size not accurate after pushing front");
			pList->pushBack(&y);
			Assert::AreEqual(2, pList->size(), L"List size not accurate after pushing back");
			pList->popFront();
			Assert::AreEqual(1, pList->size(), L"List sizen ot accurate after popping front");
			pList->popFront();
			Assert::AreEqual(0, pList->size(), L"List size not accurate after popping last value");
		}

		TEST_METHOD(TestCopy)
		{
			const auto iterations = 10;

			for (int i = 0; i < iterations; i++)
			{
				list->pushBack(i);
			}

			auto listCopy(*list);

			while (!list->isEmpty())
			{
				auto expected = list->popFront();
				auto actual = listCopy.popFront();
				Assert::AreEqual(expected, actual, L"Copied list contains different values from original");
			}

			int values[iterations];
			
			for (int i = 0; i < iterations; i++)
			{
				values[i] = i;
				pList->pushBack(&values[i]);
			}

			auto pListCopy(*pList);

			while (!pList->isEmpty())
			{
				auto expected = pList->popFront();
				auto actual = pListCopy.popFront();
				Assert::AreEqual(expected, actual, L"Copied list contains different pointer values from original");
			}
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			list->pushFront(1);
			list->pushFront(2);
			list->pushFront(3);

			SList<int> newList;
			newList = *list;

			for (int i = 0; i < list->size(); i++)
			{
				auto expected = list->popFront();
				auto result = newList.popFront();
				Assert::AreEqual(expected, result, L"List values do not match");
			}

			int x = 1;
			int y = 2;
			int z = 3;
			pList->pushFront(&x);
			pList->pushFront(&y);
			pList->pushFront(&z);

			SList<int*> pListCopy;
			pListCopy = *pList;

			for (int i = 0; i < pList->size(); i++)
			{
				auto expected = pList->popFront();
				auto result = pListCopy.popFront();
				Assert::AreEqual(expected, result, L"List values do not match");
			}
		}

		TEST_METHOD(TestClear)
		{
			list->pushFront(1);
			list->clear();

			Assert::AreEqual(0, list->size(), L"List size non-zero after clear");

			int x = 1;
			pList->pushFront(&x);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}