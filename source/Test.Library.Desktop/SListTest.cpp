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
		Library::SList<int>*  list;
		Library::SList<int*>* pList;
		Library::SList<Foo>*  fooList;
	public:
		// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#ifdef _Debug
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
		}
		
		// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#ifdef _Debug
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif //_Debug
		}

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			initializeLeakDetection();
			list    = new Library::SList<int> ();
			pList   = new Library::SList<int*>();
			fooList = new Library::SList<Foo> ();
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
				list->PushFront(i);
			}

			for (int i = iterations-1; i >= 0; i--)
			{
				Assert::AreEqual(i, list->PopFront(), L"Integer list values not equal");
			}

			int values[iterations];
			for (int i = 0; i < iterations; i++)
			{
				values[i] = i;
				pList->PushBack(&values[i]);
			}
			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, *pList->PopFront(), L"Pointer list values not equal");
			}

			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				fooList->PushBack(foo);
			}
			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				Assert::AreEqual(foo, fooList->PopFront(), L"Foo list values not equal");
			}
		}

		TEST_METHOD(TestPushBack)
		{
			const auto iterations = 100;

			for (int i = 0; i < iterations; i++)
			{
				list->PushBack(i);
			}

			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, list->PopFront(), L"Integer list values not equal");
			}

			int values[iterations];
			for (int i = 0; i < iterations; i++)
			{
				values[i] = i;
				pList->PushBack(&values[i]);
			}
			for (int i = 0; i < iterations; i++)
			{
				Assert::AreEqual(i, *pList->PopFront(), L"Pointer list values not equal");
			}

			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				fooList->PushBack(foo);
			}
			for (int i = 0; i < iterations; i++)
			{
				Foo foo(i);
				Assert::AreEqual(foo, fooList->PopFront(), L"Foo list values not equal");
			}
		}

		TEST_METHOD(TestIsEmptyAfterPop)
		{
			Assert::IsTrue(list->IsEmpty(), L"Integer list is not empty on initialization");

			list->PushFront(1);
			list->PopFront();
			Assert::IsTrue(list->IsEmpty(), L"Integer list is not empty after popping last value");

			Assert::IsTrue(pList->IsEmpty(), L"Pointer list is not empty on initialization");

			int x = 1;
			pList->PushFront(&x);
			pList->PopFront();
			Assert::IsTrue(pList->IsEmpty(), L"Pointer list is not empty after popping last value");

			Foo foo(1);
			fooList->PushFront(foo);
			fooList->PopFront();
			Assert::IsTrue(fooList->IsEmpty(), L"Foo list is not empty after popping last value");
		}

		TEST_METHOD(TestFront)
		{
			list->PushFront(1);
			Assert::AreEqual(1, list->Front(), L"First item pushed is not equal to Front value");

			list->PushBack(2);
			Assert::AreEqual(1, list->Front(), L"Front item changed after push Back called");
			
			list->PopFront();
			Assert::AreEqual(2, list->Front(), L"Front item incorrect after calling pop Front");
			
			list->Front() = 5;
			Assert::AreEqual(5, list->Front(), L"Error attempting to change list.Front()");

			int x = 1; 
			int y = 2; 
			int z = 3;
			pList->PushFront(&x);
			Assert::AreEqual(&x, pList->Front(), L"Conflicting addresses on Front after push Front");
			Assert::AreEqual(1, *pList->Front(), L"Conflicting values on Front after push Front");

			pList->PushBack(&y);
			Assert::AreEqual(&x, pList->Front(), L"Conflicting addresses on Front after push Back");
			Assert::AreEqual(1, *pList->Front(), L"Conflicting values on Front after push Back");

			pList->Front() = &z;
			Assert::AreEqual(&z, pList->Front(), L"Conflicting addresses on Front after changing Front directly");
			Assert::AreEqual(3, *pList->Front(), L"Conflicting values on Front after changing Front directly");

			Foo f1(1);
			Foo f2(2);
			Foo f3(3);
			fooList->PushFront(f1);
			Assert::AreEqual(f1, fooList->Front(), L"Front of Foo list does not match value pushed");
			fooList->PushBack(f2);
			Assert::AreEqual(f1, fooList->Front(), L"Front of Foo list changed after push Back");
			fooList->Front() = f3;
			Assert::AreEqual(f3, fooList->Front(), L"Error changing Front of Foo list directly");
		}

		TEST_METHOD(TestBack)
		{
			list->PushFront(1);
			Assert::AreEqual(1, list->Back(), L"Conflicting Back values after push Front");

			list->PushBack(2);
			Assert::AreEqual(2, list->Back(), L"Conflicting Back values after push Back");

			list->Back() = 5;
			Assert::AreEqual(5, list->Back(), L"Error attempting to change list.Back()");

			int x = 1;
			int y = 2;
			int z = 3;

			pList->PushFront(&x);
			Assert::AreEqual(&x, pList->Back(), L"Conflicting Back values after push Front");
			Assert::AreEqual(x, *pList->Back(), L"Value changed after pushing address to list");

			pList->PushBack(&y);
			Assert::AreEqual(&y, pList->Back(), L"Conflicting Back values after push Back");
			Assert::AreEqual(y, *pList->Back(), L"Back value changed after pushing Back");

			pList->Back() = &z;
			Assert::AreEqual(&z, pList->Back(), L"Back pointer not changed after assigning directly");
			Assert::AreEqual(z, *pList->Back(), L"Value corrupted after assigning Back address directly");

			Foo f1(1);
			Foo f2(2);
			Foo f3(3);

			fooList->PushFront(f1);
			Assert::AreEqual(f1, fooList->Back(), L"Conflicting Back values after push Front Foo list");

			fooList->PushBack(f2);
			Assert::AreEqual(f2, fooList->Back(), L"Back of Foo list does not match value pushed to Back");

			fooList->Back() = f3;
			Assert::AreEqual(f3, fooList->Back(), L"Back value of Foo list not set properly");
		}

		TEST_METHOD(TestSize)
		{
			Assert::AreEqual(0U, list->Size(), L"List Size not zero on initialization");

			list->PushFront(1);
			Assert::AreEqual(1U, list->Size(), L"List Size not accurate after pushing Front");
			
			list->PushBack(2);
			Assert::AreEqual(2U, list->Size(), L"List Size not accurate after pushing Back");
			
			list->PopFront();
			Assert::AreEqual(1U, list->Size(), L"List Size not accurate after popping Front");
			
			list->PopFront();
			Assert::AreEqual(0U, list->Size(), L"List Size not accurate after popping last value");

			int x = 1;
			int y = 2;

			Assert::AreEqual(0U, pList->Size(), L"List Size not zero on initialization");
			
			pList->PushFront(&x);
			Assert::AreEqual(1U, pList->Size(), L"List Size not accurate after pushing Front");
			
			pList->PushBack(&y);
			Assert::AreEqual(2U, pList->Size(), L"List Size not accurate after pushing Back");
			
			pList->PopFront();
			Assert::AreEqual(1U, pList->Size(), L"List Size not accurate after popping Front");
			
			pList->PopFront();
			Assert::AreEqual(0U, pList->Size(), L"List Size not accurate after popping last value");

			Foo f1(1);
			Foo f2(2);

			Assert::AreEqual(0U, fooList->Size(), L"Foo list Size not zero on initialization");
			
			fooList->PushFront(f1);
			Assert::AreEqual(1U, fooList->Size(), L"Foo list not accurate after pushing Front");
			
			fooList->PushBack(f2);
			Assert::AreEqual(2U, fooList->Size(), L"Foo list Size not accurate after pushing Back");
			
			fooList->PopFront();
			Assert::AreEqual(1U, fooList->Size(), L"Foo list Size not accurate after popping Front");
			
			fooList->PopFront();
			Assert::AreEqual(0U, fooList->Size(), L"Foo list Size not accurate after popping last value");
		}

		TEST_METHOD(TestCopy)
		{
			const auto iterations = 10;

			for (int i = 0; i < iterations; i++)
			{
				list->PushBack(i);
			}
			auto listCopy(*list);
			while (!list->IsEmpty())
			{
				auto expected = list->PopFront();
				auto actual = listCopy.PopFront();
				Assert::AreEqual(expected, actual, L"Copied list contains different values from original");
			}

			int values[iterations];
			for (int i = 0; i < iterations; i++)
			{
				values[i] = i;
				pList->PushBack(&values[i]);
			}
			auto pListCopy(*pList);
			while (!pList->IsEmpty())
			{
				auto expected = pList->PopFront();
				auto actual = pListCopy.PopFront();
				Assert::AreEqual(expected, actual, L"Copied list contains different pointer values from original");
			}

			for (int i = 0; i < iterations; i++)
			{
				Foo f(i);
				fooList->PushBack(f);
			}
			auto fooListCopy(*fooList);
			while (!fooList->IsEmpty())
			{
				auto expected = fooList->PopFront();
				auto actual = fooListCopy.PopFront();
				Assert::AreEqual(expected, actual, L"Foo list copied values do not match original");
			}

		}

		TEST_METHOD(TestAssignmentOperator)
		{
			list->PushFront(1);
			list->PushFront(2);
			list->PushFront(3);

			Library::SList<int> newList = *list;

			for (std::uint32_t i = 0; i < list->Size(); i++)
			{
				auto expected = list->PopFront();
				auto result = newList.PopFront();
				Assert::AreEqual(expected, result, L"List values do not match");
			}

			int x = 1;
			int y = 2;
			int z = 3;
			pList->PushFront(&x);
			pList->PushFront(&y);
			pList->PushFront(&z);

			Library::SList<int*> pListCopy;
			pListCopy = *pList;

			for (std::uint32_t i = 0; i < pList->Size(); i++)
			{
				auto expected = pList->PopFront();
				auto actual = pListCopy.PopFront();
				Assert::AreEqual(expected, actual, L"List values do not match");
			}

			Foo f1(1);
			Foo f2(2);
			Foo f3(3);
			fooList->PushFront(f1);
			fooList->PushFront(f2);
			fooList->PushFront(f3);

			Library::SList<Foo> fooListCopy;
			fooListCopy = *fooList;

			for (std::uint32_t i = 0; i < fooList->Size(); i++)
			{
				auto expected = fooList->PopFront();
				auto actual = fooListCopy.PopFront();
				Assert::AreEqual(expected, actual, L"Foo list values do not match");
			}
		}

		TEST_METHOD(TestClear)
		{
			list->PushFront(1);
			list->Clear();

			Assert::AreEqual(0U, list->Size(), L"List Size non-zero after Clear");

			int x = 1;
			pList->PushFront(&x);
			pList->Clear();

			Assert::AreEqual(0U, pList->Size(), L"List Size non-zero after Clear");

			Foo foo(1);
			fooList->PushFront(foo);
			fooList->Clear();

			Assert::AreEqual(0U, fooList->Size(), L"List Size non-zero after Clear");
		}

		TEST_METHOD(TestIteratorBeginEndUnique)
		{
			list->PushFront(1);
			Library::SList<int>::Iterator begin = list->begin();
			auto end = list->end();
			bool comparison = (begin == end);
			Assert::IsFalse(comparison, L"begin and end nodes are identical");

			int x = 1;
			pList->PushFront(&x);
			auto pListBegin = pList->begin();
			auto pListEnd = pList->end();
			comparison = (pListBegin == pListEnd);
			Assert::IsFalse(comparison, L"begin and end nodes are identical");

			Foo foo(1);
			fooList->PushFront(foo);
			auto fooBegin = fooList->begin();
			auto fooEnd = fooList->end();
			comparison = (fooBegin == fooEnd);
			Assert::IsFalse(comparison, L"begin and end nodes are identical");
		}

		TEST_METHOD(TestIteratorDereference)
		{
			list->PushFront(1);
			auto iter = list->begin();
			Assert::AreEqual(1, *iter, L"Dereferenced value does not reflect value in node");

			int x = 1;
			int* xptr = &x;
			pList->PushFront(xptr);
			auto pIter = pList->begin();
			Assert::AreEqual(xptr, *pIter, L"Dereferenced pointer does not reflect value in node");

			Foo foo(1);
			fooList->PushFront(foo);
			auto fooIter = fooList->begin();
			Assert::AreEqual(foo, *fooIter, L"Dereferenced foo does not reflect value in node");
		}

		TEST_METHOD(TestIteratorPreIncrement)
		{
			list->PushFront(2);
			list->PushFront(1);
			auto iter = list->begin();
			Assert::AreEqual(1, *iter, L"Front value not accurate");
			
			++iter;
			Assert::AreEqual(2, *iter, L"Pre increment not pointing to correct node");

			int x = 1;
			int y = 2;
			pList->PushFront(&x);
			pList->PushFront(&y);
			auto pIter = pList->begin();
			Assert::AreEqual(&y, *pIter, L"Front pointer not accurate");
			
			++pIter;
			Assert::AreEqual(&x, *pIter, L"Pre increment not pointing to correct node");

			Foo foo(1);
			Foo bar(2);
			fooList->PushFront(foo);
			fooList->PushFront(bar);
			auto fooIter = fooList->begin();
			Assert::AreEqual(bar, *fooIter, L"Front foo not accurate");
			
			++fooIter;
			Assert::AreEqual(foo, *fooIter, L"Pre increment not pointing to correct node");

			Library::SList<int>::Iterator defaultIter{};
			Assert::ExpectException<std::exception>([&]() { ++defaultIter; }, L"Default constructed iterator should not be incrementable");
		}

		TEST_METHOD(TestIteratorPostIncrement)
		{
			list->PushFront(2);
			list->PushFront(1);
			auto iter = list->begin();
			Assert::AreEqual(1, *iter, L"Front value not accurate");
			
			iter++;
			Assert::AreEqual(2, *iter, L"Post increment not pointing to correct node");

			int x = 1;
			int y = 2;
			pList->PushFront(&x);
			pList->PushFront(&y);
			auto pIter = pList->begin();
			Assert::AreEqual(&y, *pIter, L"Front pointer not accuarate");
			
			pIter++;
			Assert::AreEqual(&x, *pIter, L"Post increment not pointing to correct node");

			Foo foo(1);
			Foo bar(2);
			fooList->PushFront(foo);
			fooList->PushFront(bar);
			auto fooIter = fooList->begin();
			Assert::AreEqual(bar, *fooIter, L"Front foo not accurate");
			
			fooIter++;
			Assert::AreEqual(foo, *fooIter, L"Post increment not pointing to correct node");
		}

		TEST_METHOD(TestIteratorCopyConstructor)
		{
			auto iter = list->begin();
			Library::SList<int>::Iterator iterCopy(iter);
			bool comparison = (iter == iterCopy);
			Assert::IsTrue(comparison, L"Iterator copy not equivalent to original");

			auto pIter = pList->begin();
			Library::SList<int*>::Iterator pIterCopy(pIter);
			comparison = (pIter == pIterCopy);
			Assert::IsTrue(comparison, L"Iterator copy not equivalent to original");

			auto fooIter = fooList->begin();
			Library::SList<Foo>::Iterator fooIterCopy(fooIter);
			comparison = (fooIter == fooIterCopy);
			Assert::IsTrue(comparison, L"Iterator copy not equivalent to original");
		}

		TEST_METHOD(TestIteratorAssignmentOperator)
		{
			auto iter = list->begin();
			Library::SList<int>::Iterator iterCopy;
			iterCopy = iter;
			bool comparison = (iter == iterCopy);
			Assert::IsTrue(comparison, L"Iterator copy not equivalent to original");

			auto pIter = pList->begin();
			Library::SList<int*>::Iterator pIterCopy;
			pIterCopy = pIter;
			comparison = (pIter == pIterCopy);
			Assert::IsTrue(comparison, L"Iterator copy not equivalent to original");

			auto fooIter = fooList->begin();
			Library::SList<Foo>::Iterator fooIterCopy;
			fooIterCopy = fooIter;
			comparison = (fooIter == fooIterCopy);
			Assert::IsTrue(comparison, L"Iterator copy not equivalent to original");
		}

		TEST_METHOD(TestIteratorComparisonOperators)
		{
			// Int tests
			auto iterBegin = list->begin();
			auto iterEnd = list->end();
			bool comparison = (iterBegin == iterEnd);
			Assert::IsTrue(comparison, L"Iterators who share a null parent should be equivalent");
			
			list->PushFront(1);
			iterBegin = list->begin();
			iterEnd = list->end();
			
			comparison = (iterBegin == iterEnd);
			Assert::IsFalse(comparison, L"Iterator begin and end should not be equivalent when not null");
			
			comparison = (iterBegin != iterEnd);
			Assert::IsTrue(comparison, L"Iterator begin and end should not be equivalent when not null");

			// Int pointer tests
			auto pIterBegin = pList->begin();
			auto pIterEnd = pList->end();
			comparison = (pIterBegin == pIterEnd);
			Assert::IsTrue(comparison, L"Iterators who share a null parent should be equivalent");

			int x = 1;
			pList->PushFront(&x);
			pIterBegin = pList->begin();
			pIterEnd = pList->end();

			comparison = (pIterBegin == pIterEnd);
			Assert::IsFalse(comparison, L"Iterator begin and end should not be equivalent when not null");
			
			comparison = (pIterBegin != pIterEnd);
			Assert::IsTrue(comparison, L"Iterator begin and end should not be equivalent when not null");

			// Foo tests
			auto fooIterBegin = fooList->begin();
			auto fooIterEnd = fooList->end();
			comparison = (fooIterBegin == fooIterEnd);
			Assert::IsTrue(comparison, L"Iterators who share a null parent should be equivalent");

			Foo foo(1);
			fooList->PushFront(foo);
			fooIterBegin = fooList->begin();
			fooIterEnd = fooList->end();

			comparison = (fooIterBegin == fooIterEnd);
			Assert::IsFalse(comparison, L"Iterator begin and end should not be equivalent when not null");
			
			comparison = (fooIterBegin != fooIterEnd);
			Assert::IsTrue(comparison, L"Iterator begin and end should not be equivalent when not null");
		}

		TEST_METHOD(TestInsertAfter)
		{
			// Int tests
			list->InsertAfter(1, list->end());
			auto iter = list->begin();
			Assert::AreEqual(1, *iter, L"Front of list not accurate after insert after on empty list");

			list->InsertAfter(2, list->begin());
			iter = list->begin();
			Assert::AreEqual(1, *iter, L"Front of list not accurate after insert after on non-empty list");
			
			++iter;
			Assert::AreEqual(2, *iter, L"Erroneous iterator increment");

			// Int pointer tests
			int x = 1;
			int y = 2;
			pList->InsertAfter(&x, pList->end());
			auto pIter = pList->begin();
			Assert::AreEqual(&x, *pIter, L"Front of list not accurate after insert after on empty list");

			pList->InsertAfter(&y, pList->begin());
			pIter = pList->begin();
			Assert::AreEqual(&x, *pIter, L"Front of list not accurate after insert after on non-empty list");
			
			++pIter;
			Assert::AreEqual(&y, *pIter, L"Erroneous iterator increment");

			// Foo tests
			Foo foo(1);
			Foo bar(2);
			fooList->InsertAfter(foo, fooList->end());
			auto fooIter = fooList->begin();
			Assert::AreEqual(foo, *fooIter, L"Front of list not accurate after insert after on empty list");

			fooList->InsertAfter(bar, fooList->begin());
			fooIter = fooList->begin();
			Assert::AreEqual(foo, *fooIter, L"Front of list not accurate after insert after on non-empty list");
			
			++fooIter;
			Assert::AreEqual(bar, *fooIter, L"Erroneous iterator increment");
		}

		TEST_METHOD(TestRemove)
		{
			for (int i = 0; i < 3; i++)
			{
				list->PushFront(i);
			}
			auto iter = list->begin();
			Assert::AreEqual(2, *iter, L"Front of list not accurate after pushing multiple values");
			list->Remove(0);
			iter = list->begin();
			Assert::AreEqual(2, *iter, L"Front of list not accurate after removing Back value");
			
			++iter;
			Assert::AreEqual(1, *iter, L"Erroneous value after incrementing iterator");

			int x = 1;
			int y = 2;
			int z = 3;
			pList->PushFront(&x);
			pList->PushFront(&y);
			pList->PushFront(&z);
			auto pIter = pList->begin();
			Assert::AreEqual(&z, *pIter, L"Front of list not accurate after pushing multiple values");
			
			pList->Remove(&x);
			pIter = pList->begin();
			Assert::AreEqual(&z, *pIter, L"Front of list not accurate after removing Back value");
			
			++pIter;
			Assert::AreEqual(&y, *pIter, L"Erroneous value after incrementing iterator");

			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			fooList->PushFront(foo);
			fooList->PushFront(bar);
			fooList->PushFront(gar);
			auto fooIter = fooList->begin();
			Assert::AreEqual(gar, *fooIter, L"Front of list not accurate after pushing multiple values");
			
			fooList->Remove(foo);
			fooIter = fooList->begin();
			Assert::AreEqual(gar, *fooIter, L"Front of list not accurate after removing Back value");
			
			++fooIter;
			Assert::AreEqual(bar, *fooIter, L"Erroneous value after incrementing iterator");
		}

		TEST_METHOD(TestIteratorFind)
		{
			list->PushFront(1);
			list->PushFront(2);
			list->PushFront(3);

			auto location = list->Find(2);
			auto iter = list->begin();
			bool compare = (location != iter);
			Assert::IsTrue(compare, L"Find called on middle equivalent with begin");
			
			++iter;
			compare = (location == iter);
			Assert::IsTrue(compare, L"Find called on middle value not equivalent with iterator incremented to same point");
			
			++iter;
			compare = (location != iter);
			Assert::IsTrue(compare, L"Find called on middle value equivalent with end");

			int x = 1;
			int y = 2;
			int z = 3;
			pList->PushFront(&x);
			pList->PushFront(&y);
			pList->PushFront(&z);

			auto pLocation = pList->Find(&y);
			auto pIter = pList->begin();
			bool pCompare = (pLocation != pIter);
			Assert::IsTrue(pCompare, L"Find called on middle equivalent with begin");
			
			++pIter;
			pCompare = (pLocation == pIter);
			Assert::IsTrue(pCompare, L"Find called on middle value not equivalent with iterator incremented to same point");
			
			++pIter;
			pCompare = (pLocation != pIter);
			Assert::IsTrue(pCompare, L"Find called on middle value equivalent with end");

			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			fooList->PushFront(foo);
			fooList->PushFront(bar);
			fooList->PushFront(gar);

			auto fooLocation = fooList->Find(bar);
			auto fooIter = fooList->begin();
			bool fooCompare = (fooLocation != fooIter);
			Assert::IsTrue(fooCompare, L"Find called on middle equivalent with begin");
			
			++fooIter;
			fooCompare = (fooLocation == fooIter);
			Assert::IsTrue(fooCompare, L"Find called on middle value not equivalent with iterator incremented to same point");
			
			++fooIter;
			fooCompare = (fooLocation != fooIter);
			Assert::IsTrue(fooCompare, L"Find called on middle value equivalent with end");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}