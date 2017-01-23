#include "pch.h"
#include "CppUnitTest.h"
#include <SList.h>
#include "Foo.h"
#include "implementation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(SListTest)
	{
		SList<int>*  list;
		SList<int*>* pList;
		SList<Foo>*  fooList;
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
			list    = new SList<int> ();
			pList   = new SList<int*>();
			fooList = new SList<Foo> ();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			delete(fooList);
			delete(pList);
			delete(list);
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

			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				fooList->pushBack(foo);
			}
			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				Assert::AreEqual(foo, fooList->popFront(), L"Foo list values not equal");
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

			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				fooList->pushBack(foo);
			}
			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				Assert::AreEqual(foo, fooList->popFront(), L"Foo list values not equal");
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

			Foo foo(1);
			fooList->pushFront(foo);
			fooList->popFront();
			Assert::IsTrue(fooList->isEmpty(), L"Foo list is not empty after popping last value");
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

			Foo f1(1);
			Foo f2(2);
			Foo f3(3);
			fooList->pushFront(f1);
			Assert::AreEqual(f1, fooList->front(), L"Front of Foo list does not match value pushed");
			fooList->pushBack(f2);
			Assert::AreEqual(f1, fooList->front(), L"Front of Foo list changed after push back");
			fooList->front() = f3;
			Assert::AreEqual(f3, fooList->front(), L"Error changing front of Foo list directly");
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

			Foo f1(1);
			Foo f2(2);
			Foo f3(3);

			fooList->pushFront(f1);
			Assert::AreEqual(f1, fooList->back(), L"Conflicting back values after push front Foo list");

			fooList->pushBack(f2);
			Assert::AreEqual(f2, fooList->back(), L"Back of Foo list does not match value pushed to back");

			fooList->back() = f3;
			Assert::AreEqual(f3, fooList->back(), L"Back value of Foo list not set properly");
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
			Assert::AreEqual(1, pList->size(), L"List size not accurate after popping front");
			pList->popFront();
			Assert::AreEqual(0, pList->size(), L"List size not accurate after popping last value");

			Foo f1(1);
			Foo f2(2);

			Assert::AreEqual(0, fooList->size(), L"Foo list size not zero on initialization");
			fooList->pushFront(f1);
			Assert::AreEqual(1, fooList->size(), L"Foo list not accurate after pushing front");
			fooList->pushBack(f2);
			Assert::AreEqual(2, fooList->size(), L"Foo list size not accurate after pushing back");
			fooList->popFront();
			Assert::AreEqual(1, fooList->size(), L"Foo list size not accurate after popping front");
			fooList->popFront();
			Assert::AreEqual(0, fooList->size(), L"Foo list size not accurate after popping last value");
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

			for (int i = 0; i < iterations; i++)
			{
				Foo f(i);
				fooList->pushBack(f);
			}
			auto fooListCopy(*fooList);
			while (!fooList->isEmpty())
			{
				auto expected = fooList->popFront();
				auto actual = fooListCopy.popFront();
				Assert::AreEqual(expected, actual, L"Foo list copied values do not match original");
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
				auto actual = pListCopy.popFront();
				Assert::AreEqual(expected, actual, L"List values do not match");
			}

			Foo f1(1);
			Foo f2(2);
			Foo f3(3);
			fooList->pushFront(f1);
			fooList->pushFront(f2);
			fooList->pushFront(f3);

			SList<Foo> fooListCopy;
			fooListCopy = *fooList;

			for (int i = 0; i < fooList->size(); i++)
			{
				auto expected = fooList->popFront();
				auto actual = fooListCopy.popFront();
				Assert::AreEqual(expected, actual, L"Foo list values do not match");
			}
		}

		TEST_METHOD(TestClear)
		{
			list->pushFront(1);
			list->clear();

			Assert::AreEqual(0, list->size(), L"List size non-zero after clear");

			int x = 1;
			pList->pushFront(&x);
			pList->clear();

			Assert::AreEqual(0, pList->size(), L"List size non-zero after clear");

			Foo foo(1);
			fooList->pushFront(foo);
			fooList->clear();

			Assert::AreEqual(0, fooList->size(), L"List size non-zero after clear");
		}

		TEST_METHOD(TestIteratorStartEndUnique)
		{
			list->pushFront(1);
			list->pushFront(2);
			auto iter = list->begin();
			auto comparison = (iter == list->begin());
			Assert::IsTrue(comparison, L"Owners do not match");

//			++iter;
			auto checkIncrement = (iter == list->end());
			Assert::IsTrue(checkIncrement, L"Increment failing to reach end");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}