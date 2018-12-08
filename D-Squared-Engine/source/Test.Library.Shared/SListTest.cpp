#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
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

        TEST_METHOD_INITIALIZE(InitializeMethod)
        {
            LeakDetector::Initialize();

            list = new Library::SList<int>();
            pList = new Library::SList<int*>();
            fooList = new Library::SList<Foo>();
        }

        TEST_METHOD_CLEANUP(CleanupMethod)
        {
            delete(fooList);
            delete(pList);
            delete(list);

            LeakDetector::Finalize();
        }

        TEST_METHOD(TestPushFront_Integer)
        {
            const int iterations = 100;

            for (int i = 0; i < iterations; i++)
            {
                list->PushFront(i);
            }

            for (int i = iterations - 1; i >= 0; i--)
            {
                Assert::AreEqual(i, list->PopFront(),
                    L"Integer list values not equal");
            }
        }

        TEST_METHOD(TestPushFront_Pointer)
        {
            const int iterations = 100;

            int values[iterations];
            for (int i = 0; i < iterations; i++)
            {
                values[i] = i;
                pList->PushBack(&values[i]);
            }
            for (int i = 0; i < iterations; i++)
            {
                Assert::AreEqual(i, *pList->PopFront(),
                    L"Pointer list values not equal");
            }
        }

        TEST_METHOD(TestPushFront_Foo)
        {
            const int iterations = 100;

            for (int i = 0; i < iterations; i++)
            {
                Foo foo(i);
                fooList->PushBack(foo);
            }
            for (int i = 0; i < iterations; i++)
            {
                Foo foo(i);
                Assert::AreEqual(foo, fooList->PopFront(),
                    L"Foo list values not equal");
            }
        }

        TEST_METHOD(TestPushBack_Integer)
        {
            const auto iterations = 100;

            for (int i = 0; i < iterations; i++)
            {
                list->PushBack(i);
            }

            for (int i = 0; i < iterations; i++)
            {
                Assert::AreEqual(i, list->PopFront(),
                    L"Integer list values not equal");
            }
        }

        TEST_METHOD(TestPushBack_Pointer)
        {
            const auto iterations = 100;

            int values[iterations];
            for (int i = 0; i < iterations; i++)
            {
                values[i] = i;
                pList->PushBack(&values[i]);
            }
            for (int i = 0; i < iterations; i++)
            {
                Assert::AreEqual(i, *pList->PopFront(),
                    L"Pointer list values not equal");
            }
        }

        TEST_METHOD(TestPushBack_Foo)
        {
            const auto iterations = 100;

            for (int i = 0; i < iterations; i++)
            {
                Foo foo(i);
                fooList->PushBack(foo);
            }
            for (int i = 0; i < iterations; i++)
            {
                Foo foo(i);
                Assert::AreEqual(foo, fooList->PopFront(),
                    L"Foo list values not equal");
            }
        }

        TEST_METHOD(TestIsEmptyAfterPop_Integer)
        {
            Assert::IsTrue(list->IsEmpty(),
                L"Integer list is not empty on initialization");

            list->PushFront(1);
            list->PopFront();
            Assert::IsTrue(list->IsEmpty(),
                L"Integer list is not empty after popping last value");

            Assert::IsTrue(pList->IsEmpty(),
                L"Pointer list is not empty on initialization");
        }

        TEST_METHOD(TestIsEmptyAfterPop_Pointer)
        {
            int x = 1;
            pList->PushFront(&x);
            pList->PopFront();
            Assert::IsTrue(pList->IsEmpty(),
                L"Pointer list is not empty after popping last value");
        }

        TEST_METHOD(TestIsEmptyAfterPop_Foo)
        {
            Foo foo(1);
            fooList->PushFront(foo);
            fooList->PopFront();
            Assert::IsTrue(fooList->IsEmpty(), L"Foo list is not empty after popping last value");
        }

        TEST_METHOD(TestFront_Integer)
        {
            list->PushFront(1);
            Assert::AreEqual(1, list->Front(),
                L"First item pushed is not equal to Front value");

            list->PushBack(2);
            Assert::AreEqual(1, list->Front(),
                L"Front item changed after push Back called");

            list->PopFront();
            Assert::AreEqual(2, list->Front(),
                L"Front item incorrect after calling pop Front");

            list->Front() = 5;
            Assert::AreEqual(5, list->Front(),
                L"Error attempting to change list.Front()");
        }

        TEST_METHOD(TestFront_Pointer)
        {
            int x = 1;
            int y = 2;
            int z = 3;
            pList->PushFront(&x);
            Assert::AreEqual(&x, pList->Front(),
                L"Conflicting addresses on Front after push Front");
            Assert::AreEqual(1, *pList->Front(),
                L"Conflicting values on Front after push Front");

            pList->PushBack(&y);
            Assert::AreEqual(&x, pList->Front(),
                L"Conflicting addresses on Front after push Back");
            Assert::AreEqual(1, *pList->Front(),
                L"Conflicting values on Front after push Back");

            pList->Front() = &z;
            Assert::AreEqual(&z, pList->Front(),
                L"Conflicting addresses on Front after changing Front directly");
            Assert::AreEqual(3, *pList->Front(),
                L"Conflicting values on Front after changing Front directly");
        }

        TEST_METHOD(TestFront_Foo)
        {
            Foo f1(1);
            Foo f2(2);
            Foo f3(3);
            fooList->PushFront(f1);
            Assert::AreEqual(f1, fooList->Front(),
                L"Front of Foo list does not match value pushed");
            fooList->PushBack(f2);
            Assert::AreEqual(f1, fooList->Front(),
                L"Front of Foo list changed after push Back");
            fooList->Front() = f3;
            Assert::AreEqual(f3, fooList->Front(),
                L"Error changing Front of Foo list directly");
        }

        TEST_METHOD(TestBack_Integer)
        {
            list->PushFront(1);
            Assert::AreEqual(1, list->Back(),
                L"Conflicting Back values after push Front");

            list->PushBack(2);
            Assert::AreEqual(2, list->Back(),
                L"Conflicting Back values after push Back");

            list->Back() = 5;
            Assert::AreEqual(5, list->Back(),
                L"Error attempting to change list.Back()");
        }

        TEST_METHOD(TestBack_Pointer)
        {
            int x = 1;
            int y = 2;
            int z = 3;

            pList->PushFront(&x);
            Assert::AreEqual(&x, pList->Back(),
                L"Conflicting Back values after push Front");
            Assert::AreEqual(x, *pList->Back(),
                L"Value changed after pushing address to list");

            pList->PushBack(&y);
            Assert::AreEqual(&y, pList->Back(),
                L"Conflicting Back values after push Back");
            Assert::AreEqual(y, *pList->Back(),
                L"Back value changed after pushing Back");

            pList->Back() = &z;
            Assert::AreEqual(&z, pList->Back(),
                L"Back pointer not changed after assigning directly");
            Assert::AreEqual(z, *pList->Back(),
                L"Value corrupted after assigning Back address directly");
        }

        TEST_METHOD(TestBack_Foo)
        {
            Foo f1(1);
            Foo f2(2);
            Foo f3(3);

            fooList->PushFront(f1);
            Assert::AreEqual(f1, fooList->Back(),
                L"Conflicting Back values after push Front Foo list");

            fooList->PushBack(f2);
            Assert::AreEqual(f2, fooList->Back(),
                L"Back of Foo list does not match value pushed to Back");

            fooList->Back() = f3;
            Assert::AreEqual(f3, fooList->Back(),
                L"Back value of Foo list not set properly");
        }

        TEST_METHOD(TestSize_Integer)
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
        }

        TEST_METHOD(TestSize_Pointer)
        {
            int x = 1;
            int y = 2;

            Assert::AreEqual(0U, pList->Size(),
                L"List Size not zero on initialization");

            pList->PushFront(&x);
            Assert::AreEqual(1U, pList->Size(),
                L"List Size not accurate after pushing Front");

            pList->PushBack(&y);
            Assert::AreEqual(2U, pList->Size(),
                L"List Size not accurate after pushing Back");

            pList->PopFront();
            Assert::AreEqual(1U, pList->Size(),
                L"List Size not accurate after popping Front");

            pList->PopFront();
            Assert::AreEqual(0U, pList->Size(),
                L"List Size not accurate after popping last value");
        }

        TEST_METHOD(TestSize_Foo)
        {
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

        TEST_METHOD(TestCopy_Integer)
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
                Assert::AreEqual(expected, actual,
                    L"Copied list contains different values from original");
            }
        }

        TEST_METHOD(TestCopy_Pointer)
        {
            const auto iterations = 10;

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
                Assert::AreEqual(expected, actual,
                    L"Copied list contains different pointer values from original");
            }
        }

        TEST_METHOD(TestCopy_Foo)
        {
            const auto iterations = 10;

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
                Assert::AreEqual(expected, actual,
                    L"Foo list copied values do not match original");
            }
        }

        TEST_METHOD(TestAssignmentOperator_Integer)
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
        }

        TEST_METHOD(TestAssignmentOperator_Pointer)
        {
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
        }

        TEST_METHOD(TestAssignmentOperator_Foo)
        {
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
                Assert::AreEqual(expected, actual,
                    L"Foo list values do not match");
            }
        }

        TEST_METHOD(TestClear_Integer)
        {
            list->PushFront(1);
            list->Clear();

            Assert::AreEqual(0U, list->Size(),
                L"List Size non-zero after Clear");
        }

        TEST_METHOD(TestClear_Pointer)
        {
            int x = 1;
            pList->PushFront(&x);
            pList->Clear();

            Assert::AreEqual(0U, pList->Size(),
                L"List Size non-zero after Clear");
        }

        TEST_METHOD(TestClear_Foo)
        {
            Foo foo(1);
            fooList->PushFront(foo);
            fooList->Clear();

            Assert::AreEqual(0U, fooList->Size(),
                L"List Size non-zero after Clear");
        }

        TEST_METHOD(TestIteratorBeginEndUnique_Integer)
        {
            list->PushFront(1);
            Library::SList<int>::Iterator begin = list->begin();
            auto end = list->end();
            Assert::IsFalse(begin == end,
                L"begin and end nodes are identical");
        }

        TEST_METHOD(TestIteratorBeginEndUnique_Pointer)
        {
            int x = 1;
            pList->PushFront(&x);
            auto pListBegin = pList->begin();
            auto pListEnd = pList->end();
            Assert::IsFalse(pListBegin == pListEnd,
                L"begin and end nodes are identical");
        }

        TEST_METHOD(TestIteratorBeginEndUnique_Foo)
        {
            Foo foo(1);
            fooList->PushFront(foo);
            auto fooBegin = fooList->begin();
            auto fooEnd = fooList->end();
            Assert::IsFalse(fooBegin == fooEnd,
                L"begin and end nodes are identical");
        }

        TEST_METHOD(TestIteratorDereference_Integer)
        {
            list->PushFront(1);
            auto iter = list->begin();
            Assert::AreEqual(1, *iter,
                L"Dereferenced value does not reflect value in node");
        }

        TEST_METHOD(TestIteratorDereference_Pointer)
        {
            int x = 1;
            int* xptr = &x;
            pList->PushFront(xptr);
            auto pIter = pList->begin();
            Assert::AreEqual(xptr, *pIter,
                L"Dereferenced pointer does not reflect value in node");
        }

        TEST_METHOD(TestIteratorDereference_Foo)
        {
            Foo foo(1);
            fooList->PushFront(foo);
            auto fooIter = fooList->begin();
            Assert::AreEqual(foo, *fooIter,
                L"Dereferenced foo does not reflect value in node");
        }

        TEST_METHOD(TestIteratorPreIncrement_Integer)
        {
            list->PushFront(2);
            list->PushFront(1);
            auto iter = list->begin();
            Assert::AreEqual(1, *iter,
                L"Front value not accurate");

            ++iter;
            Assert::AreEqual(2, *iter,
                L"Pre increment not pointing to correct node");
        }

        TEST_METHOD(TestIteratorPreIncrement_Pointer)
        {
            int x = 1;
            int y = 2;
            pList->PushFront(&x);
            pList->PushFront(&y);
            auto pIter = pList->begin();
            Assert::AreEqual(&y, *pIter,
                L"Front pointer not accurate");

            ++pIter;
            Assert::AreEqual(&x, *pIter,
                L"Pre increment not pointing to correct node");
        }

        TEST_METHOD(TestIteratorPreIncrement_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            fooList->PushFront(foo);
            fooList->PushFront(bar);
            auto fooIter = fooList->begin();
            Assert::AreEqual(bar, *fooIter,
                L"Front foo not accurate");

            ++fooIter;
            Assert::AreEqual(foo, *fooIter,
                L"Pre increment not pointing to correct node");
        }

        TEST_METHOD(TestIteratorPreIncrement_Default)
        {
            Library::SList<int>::Iterator defaultIter{};
            Assert::ExpectException<std::exception>([&]() { ++defaultIter; },
                L"Default constructed iterator should not be incrementable");
        }

        TEST_METHOD(TestIteratorPostIncrement_Integer)
        {
            list->PushFront(2);
            list->PushFront(1);
            auto iter = list->begin();
            Assert::AreEqual(1, *iter,
                L"Front value not accurate");

            iter++;
            Assert::AreEqual(2, *iter,
                L"Post increment not pointing to correct node");
        }

        TEST_METHOD(TestIteratorPostIncrement_Pointer)
        {
            int x = 1;
            int y = 2;
            pList->PushFront(&x);
            pList->PushFront(&y);
            auto pIter = pList->begin();
            Assert::AreEqual(&y, *pIter,
                L"Front pointer not accuarate");

            pIter++;
            Assert::AreEqual(&x, *pIter,
                L"Post increment not pointing to correct node");
        }

        TEST_METHOD(TestIteratorPostIncrement_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            fooList->PushFront(foo);
            fooList->PushFront(bar);
            auto fooIter = fooList->begin();
            Assert::AreEqual(bar, *fooIter,
                L"Front foo not accurate");

            fooIter++;
            Assert::AreEqual(foo, *fooIter,
                L"Post increment not pointing to correct node");
        }

        TEST_METHOD(TestIteratorCopyConstructor_Integer)
        {
            auto iter = list->begin();
            Library::SList<int>::Iterator iterCopy(iter);
            Assert::IsTrue(iter == iterCopy,
                L"Iterator copy not equivalent to original");
        }

        TEST_METHOD(TestIteratorCopyConstructor_Pointer)
        {
            auto pIter = pList->begin();
            Library::SList<int*>::Iterator pIterCopy(pIter);
            Assert::IsTrue(pIter == pIterCopy,
                L"Iterator copy not equivalent to original");
        }

        TEST_METHOD(TestIteratorCopyConstructor_Foo)
        {
            auto fooIter = fooList->begin();
            Library::SList<Foo>::Iterator fooIterCopy(fooIter);
            Assert::IsTrue(fooIter == fooIterCopy,
                L"Iterator copy not equivalent to original");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_Integer)
        {
            auto iter = list->begin();
            Library::SList<int>::Iterator iterCopy;
            iterCopy = iter;
            Assert::IsTrue(iter == iterCopy,
                L"Iterator copy not equivalent to original");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_Pointer)
        {
            auto pIter = pList->begin();
            Library::SList<int*>::Iterator pIterCopy;
            pIterCopy = pIter;
            Assert::IsTrue(pIter == pIterCopy,
                L"Iterator copy not equivalent to original");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_Foo)
        {
            auto fooIter = fooList->begin();
            Library::SList<Foo>::Iterator fooIterCopy;
            fooIterCopy = fooIter;
            Assert::IsTrue(fooIter == fooIterCopy,
                L"Iterator copy not equivalent to original");
        }

        TEST_METHOD(TestIteratorComparisonOperators_Integer)
        {
            auto iterBegin = list->begin();
            auto iterEnd = list->end();
            Assert::IsTrue(iterBegin == iterEnd,
                L"Iterators who share a null parent should be equivalent");

            list->PushFront(1);
            iterBegin = list->begin();
            iterEnd = list->end();

            Assert::IsFalse(iterBegin == iterEnd,
                L"Iterator begin and end should not be equivalent when not null");

            Assert::IsTrue(iterBegin != iterEnd,
                L"Iterator begin and end should not be equivalent when not null");
        }

        TEST_METHOD(TestIteratorComparisonOperators_Pointer)
        {
            auto pIterBegin = pList->begin();
            auto pIterEnd = pList->end();
            Assert::IsTrue(pIterBegin == pIterEnd,
                L"Iterators who share a null parent should be equivalent");

            int x = 1;
            pList->PushFront(&x);
            pIterBegin = pList->begin();
            pIterEnd = pList->end();

            Assert::IsFalse(pIterBegin == pIterEnd,
                L"Iterator begin and end should not be equivalent when not null");

            Assert::IsTrue(pIterBegin != pIterEnd,
                L"Iterator begin and end should not be equivalent when not null");
        }

        TEST_METHOD(TestIteratorComparisonOperators_Foo)
        {
            auto fooIterBegin = fooList->begin();
            auto fooIterEnd = fooList->end();
            Assert::IsTrue(fooIterBegin == fooIterEnd,
                L"Iterators who share a null parent should be equivalent");

            Foo foo(1);
            fooList->PushFront(foo);
            fooIterBegin = fooList->begin();
            fooIterEnd = fooList->end();

            Assert::IsFalse(fooIterBegin == fooIterEnd,
                L"Iterator begin and end should not be equivalent when not null");

            Assert::IsTrue(fooIterBegin != fooIterEnd,
                L"Iterator begin and end should not be equivalent when not null");
        }

        TEST_METHOD(TestInsertAfter_Integer)
        {
            list->InsertAfter(1, list->end());
            auto iter = list->begin();
            Assert::AreEqual(1, *iter,
                L"Front of list not accurate after insert after on empty list");

            list->InsertAfter(2, list->begin());
            iter = list->begin();
            Assert::AreEqual(1, *iter,
                L"Front of list not accurate after insert after on non-empty list");

            ++iter;
            Assert::AreEqual(2, *iter,
                L"Erroneous iterator increment");
        }

        TEST_METHOD(TestInsertAfter_Pointer)
        {
            int x = 1;
            int y = 2;
            pList->InsertAfter(&x, pList->end());
            auto pIter = pList->begin();
            Assert::AreEqual(&x, *pIter,
                L"Front of list not accurate after insert after on empty list");

            pList->InsertAfter(&y, pList->begin());
            pIter = pList->begin();
            Assert::AreEqual(&x, *pIter,
                L"Front of list not accurate after insert after on non-empty list");

            ++pIter;
            Assert::AreEqual(&y, *pIter,
                L"Erroneous iterator increment");
        }

        TEST_METHOD(TestInsertAfter_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            fooList->InsertAfter(foo, fooList->end());
            auto fooIter = fooList->begin();
            Assert::AreEqual(foo, *fooIter,
                L"Front of list not accurate after insert after on empty list");

            fooList->InsertAfter(bar, fooList->begin());
            fooIter = fooList->begin();
            Assert::AreEqual(foo, *fooIter,
                L"Front of list not accurate after insert after on non-empty list");

            ++fooIter;
            Assert::AreEqual(bar, *fooIter,
                L"Erroneous iterator increment");
        }

        TEST_METHOD(TestRemove_Integer)
        {
            for (int i = 0; i < 3; i++)
            {
                list->PushFront(i);
            }
            auto iter = list->begin();
            Assert::AreEqual(2, *iter,
                L"Front of list not accurate after pushing multiple values");
            list->Remove(0);
            iter = list->begin();
            Assert::AreEqual(2, *iter,
                L"Front of list not accurate after removing Back value");

            ++iter;
            Assert::AreEqual(1, *iter,
                L"Erroneous value after incrementing iterator");
        }

        TEST_METHOD(TestRemove_Pointer)
        {
            int x = 1;
            int y = 2;
            int z = 3;
            pList->PushFront(&x);
            pList->PushFront(&y);
            pList->PushFront(&z);
            auto pIter = pList->begin();
            Assert::AreEqual(&z, *pIter,
                L"Front of list not accurate after pushing multiple values");

            pList->Remove(&x);
            pIter = pList->begin();
            Assert::AreEqual(&z, *pIter,
                L"Front of list not accurate after removing Back value");

            ++pIter;
            Assert::AreEqual(&y, *pIter,
                L"Erroneous value after incrementing iterator");
        }

        TEST_METHOD(TestRemove_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            Foo gar(3);
            fooList->PushFront(foo);
            fooList->PushFront(bar);
            fooList->PushFront(gar);
            auto fooIter = fooList->begin();
            Assert::AreEqual(gar, *fooIter,
                L"Front of list not accurate after pushing multiple values");

            fooList->Remove(foo);
            fooIter = fooList->begin();
            Assert::AreEqual(gar, *fooIter,
                L"Front of list not accurate after removing Back value");

            ++fooIter;
            Assert::AreEqual(bar, *fooIter,
                L"Erroneous value after incrementing iterator");
        }

        TEST_METHOD(TestIteratorFind_Integer)
        {
            list->PushFront(1);
            list->PushFront(2);
            list->PushFront(3);

            auto location = list->Find(2);
            auto iter = list->begin();
            bool compare = (location != iter);
            Assert::IsTrue(compare,
                L"Find called on middle equivalent with begin");

            ++iter;
            compare = (location == iter);
            Assert::IsTrue(compare,
                L"Find called on middle value not equivalent with iterator incremented to same point");

            ++iter;
            compare = (location != iter);
            Assert::IsTrue(compare,
                L"Find called on middle value equivalent with end");
        }

        TEST_METHOD(TestIteratorFind_Pointer)
        {
            int x = 1;
            int y = 2;
            int z = 3;
            pList->PushFront(&x);
            pList->PushFront(&y);
            pList->PushFront(&z);

            auto pLocation = pList->Find(&y);
            auto pIter = pList->begin();
            bool pCompare = (pLocation != pIter);
            Assert::IsTrue(pCompare,
                L"Find called on middle equivalent with begin");

            ++pIter;
            pCompare = (pLocation == pIter);
            Assert::IsTrue(pCompare,
                L"Find called on middle value not equivalent with iterator incremented to same point");

            ++pIter;
            pCompare = (pLocation != pIter);
            Assert::IsTrue(pCompare,
                L"Find called on middle value equivalent with end");
        }

        TEST_METHOD(TestIteratorFind_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            Foo gar(3);
            fooList->PushFront(foo);
            fooList->PushFront(bar);
            fooList->PushFront(gar);

            auto fooLocation = fooList->Find(bar);
            auto fooIter = fooList->begin();
            bool fooCompare = (fooLocation != fooIter);
            Assert::IsTrue(fooCompare,
                L"Find called on middle equivalent with begin");

            ++fooIter;
            fooCompare = (fooLocation == fooIter);
            Assert::IsTrue(fooCompare,
                L"Find called on middle value not equivalent with iterator incremented to same point");

            ++fooIter;
            fooCompare = (fooLocation != fooIter);
            Assert::IsTrue(fooCompare,
                L"Find called on middle value equivalent with end");
        }

    };

}