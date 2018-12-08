#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include <Vector.h>
#include "Foo.h"
#include "implementation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
    TEST_CLASS(VectorTest)
    {

    public:

        Library::Vector<int>  intor;
        Library::Vector<int*> pointor;
        Library::Vector<Foo>  footor;

        TEST_METHOD_INITIALIZE(InitializeMethod)
        {
            intor.Clear();
            pointor.Clear();
            footor.Clear();

            LeakDetector::Initialize();
        }

        TEST_METHOD_CLEANUP(CleanupMethod)
        {
            intor.Clear();
            pointor.Clear();
            footor.Clear();

            LeakDetector::Finalize();
        }

        TEST_METHOD(TestCopyConstructor_Integer)
        {
            Library::Vector<int> copyIntor(intor);
            bool intcompare = intor == copyIntor;
            Assert::IsTrue(intcompare,
                L"Copied vector not equivalent to original");

            intor.PushBack(1);
            intcompare = intor == copyIntor;
            Assert::IsFalse(intcompare,
                L"Copied vector equivalent after modifying original");

            copyIntor.PushBack(1);
            intcompare = intor == copyIntor;
            Assert::IsTrue(intcompare,
                L"Copied vector not equivalent after pushing identical values");
        }

        TEST_METHOD(TestCopyConstructor_Pointer)
        {
            Library::Vector<int*> copyPointor(pointor);
            Assert::IsTrue(pointor == copyPointor,
                L"Copied pointer vector not equivalent to original");

            int x = 1;
            pointor.PushBack(&x);
            Assert::IsFalse(pointor == copyPointor,
                L"Copied vector equivalent after modifying original");

            copyPointor.PushBack(&x);
            Assert::IsTrue(pointor == copyPointor,
                L"Copied vector not equivalent after pushing identical values");
        }

        TEST_METHOD(TestCopyConstructor_foo)
        {
            Library::Vector<Foo> copyFootor(footor);
            Assert::IsTrue(footor == copyFootor,
                L"Copied Foo vector not equivalent to original");

            Foo foo(1);
            footor.PushBack(foo);
            Assert::IsFalse(footor == copyFootor,
                L"Copied Foo vector equivalent after modifying original");

            copyFootor.PushBack(foo);
            Assert::IsTrue(footor == copyFootor,
                L"Copied vector not equivalent after pushing identical values");

        }

        TEST_METHOD(TestComparisonOperator_Integer)
        {
            Assert::IsTrue(intor == intor,
                L"Vector not equivalent to itself");

            Library::Vector<int> copyIntor(intor);
            Assert::IsTrue(intor == copyIntor,
                L"Copy constructor invocation not equivalent");

            copyIntor = intor;
            Assert::IsTrue(intor == copyIntor,
                L"Assignment operator copy not equivalent");

            const auto constIntor(intor);
            Assert::IsTrue(intor == constIntor,
                L"Const copy not equivalent");

            Library::Vector<int> wrongIntVector;
            for (int i = 0; i < 100; i++)
            {
                intor.PushBack(100 - i);
                wrongIntVector.PushBack(i);
            }
            Assert::IsFalse(intor == wrongIntVector);
        }

        TEST_METHOD(TestComparisonOperator_Pointer)
        {
            Assert::IsTrue(pointor == pointor,
                L"Vector not equivalent to itself");

            Library::Vector<int*> copyPointor(pointor);
            Assert::IsTrue(pointor == copyPointor,
                L"Copy constructor invocation not equivalent");

            copyPointor = pointor;
            Assert::IsTrue(pointor == copyPointor,
                L"Assignment operator copy not equivalent");

            const auto constPointor(pointor);
            Assert::IsTrue(pointor == constPointor,
                L"Const copy not equivalent");

            int right = 5;
            int wrong = 10;
            Library::Vector<int*> wrongPtrVector;
            for (int i = 0; i < 100; i++)
            {
                pointor.PushBack(&right);
                wrongPtrVector.PushBack(&wrong);
            }
            Assert::IsFalse(pointor == wrongPtrVector);
        }

        TEST_METHOD(TestComparisonOperator_Foo)
        {
            Assert::IsTrue(footor == footor,
                L"Vector not equivalent to itself");

            Library::Vector<Foo> copyFootor(footor);
            Assert::IsTrue(footor == copyFootor,
                L"Copy constructor invocation not equivalent");

            copyFootor = footor;
            Assert::IsTrue(footor == copyFootor,
                L"Assignment operator copy not equivalent");

            const auto constFootor(footor);
            Assert::IsTrue(footor == constFootor,
                L"Const copy not equivalent");

            Foo rightFoo(5);
            Foo wrongFoo(10);
            Library::Vector<Foo> wrongFooVector;
            for (int i = 0; i < 100; i++)
            {
                footor.PushBack(rightFoo);
                wrongFooVector.PushBack(wrongFoo);
            }
            Assert::IsFalse(footor == wrongFooVector);
        }

        TEST_METHOD(TestAssignmentOperator_Integer)
        {
            Library::Vector<int> copyIntor = intor;
            Assert::IsTrue(intor == copyIntor,
                L"Copied vector not equivalent to original");
        }

        TEST_METHOD(TestAssignmentOperator_Pointer)
        {
            Library::Vector<int*> copyPointor = pointor;
            Assert::IsTrue(pointor == copyPointor,
                L"Copied pointer vector not equivalent to original");
        }

        TEST_METHOD(TestAssignmentOperator_Foo)
        {
            Library::Vector<Foo> copyFootor = footor;
            Assert::IsTrue(footor == copyFootor,
                L"Copied Foo vector not equivalent to original");
        }

        TEST_METHOD(TestMoveSemantics_Integer)
        {
            Library::Vector<int> intVector;
            for (int i = 0; i < 10; i++)
            {
                intVector.PushBack(i);
            }

            Assert::AreEqual(10u, intVector.Size());

            Library::Vector<int> newIntVector = std::move(intVector);
            Assert::AreEqual(10u, newIntVector.Size());
            Assert::AreEqual(0u, intVector.Size());

            for (int i = 0; i < 10; i++)
            {
                Assert::AreEqual(i, newIntVector[i]);
            }
        }

        TEST_METHOD(TestMoveSemantics_Float)
        {
            Library::Vector<float> floatVector;
            for (int i = 0; i < 10; i++)
            {
                floatVector.PushBack(static_cast<float>(i));
            }

            Assert::AreEqual(10u, floatVector.Size());

            Library::Vector<float> newFloatVector = std::move(floatVector);
            Assert::AreEqual(10u, newFloatVector.Size());
            Assert::AreEqual(0u, floatVector.Size());

            for (int i = 0; i < 10; i++)
            {
                Assert::AreEqual(static_cast<float>(i), newFloatVector[i]);
            }
        }

        TEST_METHOD(TestMoveSemantics_Pointer)
        {
            int ints[10];
            for (int i = 0; i < 10; i++)
            {
                ints[i] = i;
            }

            Library::Vector<int*> ptrVector;
            for (int i = 0; i < 10; i++)
            {
                ptrVector.PushBack(&ints[i]);
            }

            Assert::AreEqual(10u, ptrVector.Size());

            Library::Vector<int*> newPtrVector = std::move(ptrVector);
            Assert::AreEqual(10u, newPtrVector.Size());
            Assert::AreEqual(0u, ptrVector.Size());

            for (int i = 0; i < 10; i++)
            {
                Assert::AreEqual(i, *newPtrVector[i]);
            }
        }

        TEST_METHOD(TestMoveSemantics_Foo)
        {
            Library::Vector<Foo> fooVector;
            for (int i = 0; i < 10; i++)
            {
                fooVector.PushBack(Foo(i));
            }

            Assert::AreEqual(10u, fooVector.Size());

            Library::Vector<Foo> newFooVector = std::move(fooVector);
            Assert::AreEqual(10u, newFooVector.Size());
            Assert::AreEqual(0u, fooVector.Size());

            for (int i = 0; i < 10; i++)
            {
                Assert::AreEqual(Foo(i), newFooVector[i]);
            }
        }

        TEST_METHOD(TestFind_Integer)
        {
            auto iter = intor.Find(0);
            Assert::IsTrue(iter == intor.end(),
                L"begin and end not equivalent on empty vector");
            Assert::IsTrue(iter == intor.begin(),
                L"Find on first element not equivalent to Vector.begin()");

            intor.PushBack(1);
            iter = intor.Find(1);
            Assert::IsFalse(iter == intor.end(),
                L"Find on existing element should not be equivalent to end");
            Assert::IsTrue(iter == intor.begin(),
                L"Find on first element should be equivalent to begin");
            Assert::AreEqual(*iter, 1,
                L"Find on first item should be equivalent to the first value pushed");

            intor.PushBack(100);
            iter = intor.Find(1);
            Assert::IsTrue(iter == intor.begin(),
                L"Find on first item should not change after pushing a second");
            Assert::IsFalse(iter == intor.end(),
                L"Find on existing item should not be equivalent to end");

            iter = intor.Find(100);
            Assert::IsTrue(++iter == intor.end(),
                L"Incrementing past final element not equivalent to end");

            const auto constIntor(intor);
            Assert::IsTrue(constIntor.Find(1) == constIntor.begin(),
                L"Const Find value incorrect");
        }

        TEST_METHOD(TestFind_Pointer)
        {
            int x = 1;
            int y = 2;
            auto piter = pointor.Find(&x);
            Assert::IsTrue(piter == pointor.end(),
                L"begin and end not equivalent on empty vector");
            Assert::IsTrue(piter == pointor.begin(),
                L"Find on first element not equivalent to Vector.begin()");

            pointor.PushBack(&x);
            piter = pointor.Find(&x);
            Assert::IsFalse(piter == pointor.end(),
                L"Find on existing element should not be equivalent to end");
            Assert::IsTrue(piter == pointor.begin(),
                L"Find on first element should be equivalent to begin");
            Assert::AreEqual(*piter, &x,
                L"Find on first item should be equivalent to the first value pushed");

            pointor.PushBack(&y);
            piter = pointor.Find(&x);
            Assert::IsTrue(piter == pointor.begin(),
                L"Find on first item should not change after pushing a second");
            Assert::IsFalse(piter == pointor.end(),
                L"Find on existing item should not be equivalent to end");

            piter = pointor.Find(&y);
            Assert::IsTrue(++piter == pointor.end(),
                L"Incrementing past final element not equivalent to end");

            const auto constPointor(pointor);
            Assert::IsTrue(constPointor.Find(&x) == constPointor.begin(),
                L"Const Find value incorrect");
        }

        TEST_METHOD(TestFind_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            auto fooiter = footor.Find(foo);
            Assert::IsTrue(fooiter == footor.end(),
                L"begin and end not equivalent on empty vector");
            Assert::IsTrue(fooiter == footor.begin(),
                L"Find on first element not equivalent to Vector.begin()");

            footor.PushBack(foo);
            fooiter = footor.Find(foo);
            Assert::IsFalse(fooiter == footor.end(),
                L"Find on existing element should not be equivalent to end");
            Assert::IsTrue(fooiter == footor.begin(),
                L"Find on first element should be equivalent to begin");
            Assert::AreEqual(*fooiter, foo,
                L"Find on first item should be equivalent to the first value pushed");

            footor.PushBack(bar);
            fooiter = footor.Find(foo);
            Assert::IsTrue(fooiter == footor.begin(),
                L"Find on first item should not change after pushing a second");
            Assert::IsFalse(fooiter == footor.end(),
                L"Find on existing item should not be equivalent to end");

            fooiter = footor.Find(bar);
            Assert::IsTrue(++fooiter == footor.end(),
                L"Incrementing past final element not equivalent to end");

            const auto constFootor(footor);
            Assert::IsTrue(constFootor.Find(foo) == constFootor.begin(),
                L"Const Find value incorrect");
        }

        TEST_METHOD(TestBegin_Integer)
        {
            Assert::IsTrue(intor.begin() == intor.end(),
                L"begin should be equivalent to end on an empy vector");

            intor.PushBack(1);
            Assert::IsTrue(1 == *intor.begin(),
                L"begin not equivalent with first value pushed");
            Assert::IsFalse(intor.begin() == intor.end());

            intor.PushBack(2);
            Assert::IsTrue(1 == *intor.begin(),
                L"begin value changed after calling push Back on non-empty vector");
            Assert::IsTrue(intor[0] == *intor.begin(),
                L"First index not equivalent to begin");

            const auto constIntor(intor);
            Assert::IsTrue(*constIntor.begin() == constIntor[0]);
        }

        TEST_METHOD(TestBegin_Pointer)
        {
            int x = 1;
            int y = 2;
            Assert::IsTrue(pointor.begin() == pointor.end(),
                L"begin should be equivalent to end on an empy vector");

            pointor.PushBack(&x);
            Assert::IsTrue(&x == *pointor.begin(),
                L"begin not equivalent with first value pushed");
            Assert::IsFalse(pointor.begin() == pointor.end());

            pointor.PushBack(&y);
            Assert::IsTrue(&x == *pointor.begin(),
                L"begin value changed after calling push Back on non-empty vector");
            Assert::IsTrue(pointor[0] == *pointor.begin(),
                L"First index not equivalent to begin");

            const auto constPointor(pointor);
            Assert::IsTrue(*constPointor.begin() == constPointor[0]);
        }

        TEST_METHOD(TestBegin_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            Assert::IsTrue(footor.begin() == footor.end(),
                L"begin should be equivalent to end on an empy vector");

            footor.PushBack(foo);
            Assert::IsTrue(foo == *footor.begin(),
                L"begin not equivalent with first value pushed");
            Assert::IsFalse(footor.begin() == footor.end());

            footor.PushBack(bar);
            Assert::IsTrue(foo == *footor.begin(),
                L"begin value changed after calling push Back on non-empty vector");
            Assert::IsTrue(footor[0] == *footor.begin(),
                L"First index not equivalent to begin");

            const auto constFootor(footor);
            Assert::IsTrue(*constFootor.begin() == constFootor[0]);
        }

        TEST_METHOD(TestEnd_Integer)
        {
            Assert::IsTrue(intor.begin() == intor.end(),
                L"end should be equivalent to begin on an empty vector");

            Library::Vector<int>::Iterator iter = intor.end();
            Assert::IsTrue(iter == intor.end(),
                L"Iterator assigned to end should be equivalent to end");

            intor.PushBack(1);
            iter = intor.begin();
            Assert::IsFalse(iter == intor.end(),
                L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
            Assert::IsTrue(++iter == intor.end(),
                L"Iterator pointing to last element should be equivalent to end after incrementing");

            Assert::IsTrue(pointor.begin() == pointor.end(),
                L"end should be equivalent to begin on an empty vector");

            const auto constIntor(intor);
            auto constIter = constIntor.end();
            Assert::IsTrue(constIter == constIntor.end());
        }

        TEST_METHOD(TestEnd_Pointer)
        {

            Library::Vector<int*>::Iterator piter = pointor.end();
            Assert::IsTrue(piter == pointor.end(),
                L"Iterator assigned to end should be equivalent to end");

            int x = 1;
            pointor.PushBack(&x);
            piter = pointor.begin();
            Assert::IsFalse(piter == pointor.end(),
                L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
            Assert::IsTrue(++piter == pointor.end(),
                L"Iterator pointing to last element should be equivalent to end after incrementing");

            Assert::IsTrue(footor.begin() == footor.end(),
                L"end should be equivalent to begin on an empty vector");

            const auto constPointor(pointor);
            auto constPIter = constPointor.end();
            Assert::IsTrue(constPIter == constPointor.end());
        }

        TEST_METHOD(TestEnd_Foo)
        {
            Library::Vector<Foo>::Iterator fooiter = footor.end();
            Assert::IsTrue(fooiter == footor.end(),
                L"Iterator assigned to end should be equivalent to end");

            Foo foo(1);
            footor.PushBack(foo);
            fooiter = footor.begin();
            Assert::IsFalse(fooiter == footor.end(),
                L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
            Assert::IsTrue(++fooiter == footor.end(),
                L"Iterator pointing to last element should be equivalent to end after incrementing");

            const auto constFootor(footor);
            auto constFooIter = constFootor.end();
            Assert::IsTrue(constFooIter == constFootor.end());
        }

        TEST_METHOD(TestFront_Integer)
        {
            auto func = [this] { intor.Front(); };
            Assert::ExpectException<std::exception>(func,
                L"Front should be equivalent with begin on an empty vector");

            intor.PushBack(1);
            Assert::IsTrue(intor.Front() == intor[0],
                L"Front should be equivalent with first index");
            Assert::IsTrue(intor.Front() == *intor.begin(),
                L"Front should be equivalent with begin");

            intor.Front() = 5;
            Assert::IsTrue(intor.Front() == 5,
                L"Unable to modify Vector.Front()");

            const Library::Vector<int> constIntVector(intor);
            Assert::IsTrue(constIntVector.Front() == intor.Front(),
                L"Front of const copied vector should be equivalent to original");
        }

        TEST_METHOD(TestFront_Pointer)
        {
            auto ptrfunc = [this] { pointor.Front(); };
            Assert::ExpectException<std::exception>(ptrfunc,
                L"Front should be equivalent with begin on an empty vector");

            int x = 1;
            pointor.PushBack(&x);
            Assert::IsTrue(pointor.Front() == pointor[0],
                L"Front should be equivalent with first index");
            Assert::IsTrue(pointor.Front() == *pointor.begin(),
                L"Front should be equivalent with begin");

            int y = 5;
            pointor.Front() = &y;
            Assert::IsTrue(pointor.Front() == &y,
                L"Unable to modify Vector.Front()");

            const Library::Vector<int*> constPtrVector(pointor);
            Assert::IsTrue(constPtrVector.Front() == pointor.Front(),
                L"Front of const copied vector should be equivalent to original");
        }

        TEST_METHOD(TestFront_Foo)
        {
            auto foofunc = [this] { footor.Front(); };
            Assert::ExpectException<std::exception>(foofunc,
                L"Front should be equivalent with begin on an empty vector");

            Foo foo(1);
            footor.PushBack(foo);
            Assert::IsTrue(footor.Front() == footor[0],
                L"Front should be equivalent with first index");
            Assert::IsTrue(footor.Front() == *footor.begin(),
                L"Front should be equivalent with begin");

            Foo bar(5);
            footor.Front() = bar;
            Assert::IsTrue(footor.Front() == bar,
                L"Unable to modify Vector.Front()");

            const Library::Vector<Foo> constFooVector(footor);
            Assert::IsTrue(constFooVector.Front() == footor.Front(),
                L"Front of constant copied vector not equal to original vector's Front");
            Assert::IsTrue(true);
        }

        TEST_METHOD(TestBack_Integer)
        {
            auto func = [this] { intor.Back(); };
            Assert::ExpectException<std::exception>(func,
                L"Calling Back on an empty vector should throw an exception");

            intor.PushBack(1);
            Assert::IsTrue(intor.Back() == intor[0],
                L"Back should be equivalent to first value pushed onto an empty vector");

            intor.PushBack(2);
            Assert::IsTrue(intor.Back() == intor[1],
                L"Back should b equivalent to last value pushed onto a vector");

            intor.Back() = 10;
            Assert::IsTrue(intor.Back() == 10,
                L"Vector.Back() not modifiable");
        }

        TEST_METHOD(TestBack_Pointer)
        {
            auto ptrfunc = [this] { pointor.Back(); };
            Assert::ExpectException<std::exception>(ptrfunc,
                L"Calling Back on an empty vector should throw an exception");

            int x = 1;
            pointor.PushBack(&x);
            Assert::IsTrue(pointor.Back() == pointor[0],
                L"Back should be equivalent to first value pushed onto an empty vector");

            int y = 2;
            pointor.PushBack(&y);
            Assert::IsTrue(pointor.Back() == pointor[1],
                L"Back should b equivalent to last value pushed onto a vector");

            int z = 10;
            pointor.Back() = &z;
            Assert::IsTrue(pointor.Back() == &z,
                L"Vector.Back() not modifiable");
        }

        TEST_METHOD(TestBack_Foo)
        {
            auto foofunc = [this] { footor.Back(); };
            Assert::ExpectException<std::exception>(foofunc,
                L"Calling Back on an empty vector should throw an exception");

            Foo foo(1);
            footor.PushBack(foo);
            Assert::IsTrue(footor.Back() == footor[0],
                L"Back should be equivalent to first value pushed onto an empty vector");

            Foo bar(2);
            footor.PushBack(bar);
            Assert::IsTrue(footor.Back() == footor[1],
                L"Back should b equivalent to last value pushed onto a vector");

            Foo gar(10);
            footor.Back() = gar;
            Assert::IsTrue(footor.Back() == gar,
                L"Vector.Back() not modifiable");
        }

        TEST_METHOD(TestAt_Integer)
        {
            auto func1 = [this] { intor.At(0U); };
            Assert::ExpectException<std::exception>(func1,
                L"Accessing index of an empty vector should throw an exception");

            intor.PushBack(1);
            auto func2 = [this] { intor.At(1U); };
            Assert::ExpectException<std::exception>(func2,
                L"Accessing out of vector bounds should throw an exception");

            intor.PushBack(2);
            Assert::IsTrue(1 == intor.At(0U),
                L"First element should be equivalent to Vector.At(0) after pushing Back multiple values");
            Assert::IsTrue(2 == intor.At(1U),
                L"Last element should be equivalent to Vector.At(n-1)");

            const auto constIntor(intor);
            Assert::IsTrue(1 == constIntor.At(0U));
            Assert::IsTrue(2 == constIntor.At(1U));
        }

        TEST_METHOD(TestAt_Pointer)
        {
            auto ptrfunc1 = [this] { pointor.At(0U); };
            Assert::ExpectException<std::exception>(ptrfunc1,
                L"Accessing index of an empty vector should throw an exception");

            int x = 1;
            pointor.PushBack(&x);
            auto ptrfunc2 = [this] { pointor.At(1U); };
            Assert::ExpectException<std::exception>(ptrfunc2,
                L"Accessing out of vector bounds should throw an exception");

            int y = 2;
            pointor.PushBack(&y);
            Assert::IsTrue(&x == pointor.At(0),
                L"First element should be equivalent to Vector.At(0) after pushing Back multiple values");
            Assert::IsTrue(&y == pointor.At(1),
                L"Last element should be equivalent to Vector.At(n-1)");

            const auto constPointor(pointor);
            Assert::IsTrue(&x == constPointor.At(0));
            Assert::IsTrue(&y == constPointor.At(1));
        }

        TEST_METHOD(TestAt_Foo)
        {
            auto foofunc1 = [this] { footor.At(0); };
            Assert::ExpectException<std::exception>(foofunc1,
                L"Accessing index of an empty vector should throw an exception");

            Foo foo(1);
            footor.PushBack(foo);
            auto foofunc2 = [this] { footor.At(1); };
            Assert::ExpectException<std::exception>(foofunc2,
                L"Accessing out of vector bounds should throw an exception");

            Foo bar(2);
            footor.PushBack(bar);
            Assert::IsTrue(foo == footor.At(0),
                L"First element should be equivalent to Vector.At(0) after pushing Back multiple values");
            Assert::IsTrue(bar == footor.At(1),
                L"Last element should be equivalent to Vector.At(n-1)");

            const auto constFootor(footor);
            Assert::IsTrue(foo == constFootor.At(0));
            Assert::IsTrue(bar == constFootor.At(1));
        }

        TEST_METHOD(TestIndexOperator_Integer)
        {
            auto func1 = [this] { intor[0]; };
            Assert::ExpectException<std::exception>(func1,
                L"Accessing index of an empty vector should throw an exception");

            intor.PushBack(1);
            auto func2 = [this] { intor[1]; };
            Assert::ExpectException<std::exception>(func2,
                L"Accessing out of vector bounds should throw an exception");

            intor.PushBack(2);
            Assert::IsTrue(1 == intor[0],
                L"First element should be equivalent to Vector[0] after pushing Back multiple values");
            Assert::IsTrue(2 == intor[1],
                L"Last element should be equivalent to Vector[n-1]");

            const auto constIntor(intor);
            Assert::IsTrue(1 == constIntor[0]);
            Assert::IsTrue(2 == constIntor[1]);
        }

        TEST_METHOD(TestIndexOperator_Pointer)
        {
            auto ptrfunc1 = [this] { pointor[0]; };
            Assert::ExpectException<std::exception>(ptrfunc1,
                L"Accessing index of an empty vector should throw an exception");

            int x = 1;
            pointor.PushBack(&x);
            auto ptrfunc2 = [this] { pointor[1]; };
            Assert::ExpectException<std::exception>(ptrfunc2,
                L"Accessing out of vector bounds should throw an exception");

            int y = 2;
            pointor.PushBack(&y);
            Assert::IsTrue(&x == pointor[0],
                L"First element should be equivalent to Vector[0] after pushing Back multiple values");
            Assert::IsTrue(&y == pointor[1],
                L"Last element should be equivalent to Vector[n-1]");

            const auto constPointor(pointor);
            Assert::IsTrue(&x == constPointor[0]);
            Assert::IsTrue(&y == constPointor[1]);
        }

        TEST_METHOD(TestIndexOperator_Foo)
        {
            auto foofunc1 = [this] { footor[0U]; };
            Assert::ExpectException<std::exception>(foofunc1,
                L"Accessing index of an empty vector should throw an exception");

            Foo foo(1);
            footor.PushBack(foo);
            auto foofunc2 = [this] { footor[1U]; };
            Assert::ExpectException<std::exception>(foofunc2,
                L"Accessing out of vector bounds should throw an exception");

            Foo bar(2);
            footor.PushBack(bar);
            Assert::IsTrue(foo == footor[0],
                L"First element should be equivalent to Vector[0] after pushing Back multiple values");
            Assert::IsTrue(bar == footor[1],
                L"Last element should be equivalent to Vector[n-1]");

            const auto constFootor(footor);
            Assert::IsTrue(foo == constFootor[0]);
            Assert::IsTrue(bar == constFootor[1]);
        }

        TEST_METHOD(TestPopBack_Integer)
        {
            auto func1 = [this] { intor.PopBack(); };
            Assert::ExpectException<std::exception>(func1,
                L"PopBack on empty vector should throw an exception");

            intor.PushBack(1);
            intor.PushBack(2);
            intor.PushBack(3);
            intor.PopBack();
            Assert::AreEqual(2U, intor.Size(),
                L"Vector Size not reducing after valid pop Back");
        }

        TEST_METHOD(TestPopBack_Pointer)
        {
            auto ptrfunc1 = [this] { pointor.PopBack(); };
            Assert::ExpectException<std::exception>(ptrfunc1,
                L"PopBack on empty vector should throw an exception");

            int x = 1;
            int y = 2;
            int z = 3;
            pointor.PushBack(&x);
            pointor.PushBack(&y);
            pointor.PushBack(&z);
            pointor.PopBack();
            Assert::AreEqual(2U, pointor.Size(),
                L"Vector Size not reducing after valid pop Back");
        }

        TEST_METHOD(TestPopBack_Foo)
        {
            auto foofunc1 = [this] { footor.PopBack(); };
            Assert::ExpectException<std::exception>(foofunc1,
                L"PopBack on empty vector should throw an exception");

            Foo foo(1);
            Foo bar(2);
            Foo gar(3);
            footor.PushBack(foo);
            footor.PushBack(bar);
            footor.PushBack(gar);
            footor.PopBack();
            Assert::AreEqual(2U, footor.Size(),
                L"Vector Size not reducing after valid pop Back");
        }

        TEST_METHOD(TestSize_Integer)
        {
            intor.Reserve(10);
            intor.Reserve(10);
            intor.PushBack(1);
            intor.PopBack();

            Assert::AreEqual(0u, intor.Size(),
                L"Size not zero on empty vector");

            intor.PushBack(1);
            Assert::AreEqual(1u, intor.Size(),
                L"Size not one after pushing one value");

            intor.PopBack();
            Assert::AreEqual(0u, intor.Size(),
                L"Size not zero after popping last value");

            const auto constIntor(intor);
            Assert::AreEqual(0u, constIntor.Size());
        }

        TEST_METHOD(TestSize_Pointer)
        {
            Assert::IsTrue(pointor.Size() == 0,
                L"Size not zero on empty vector");

            int x = 1;
            pointor.PushBack(&x);
            Assert::AreEqual(1u, pointor.Size(),
                L"Size not one after pushing one value");

            pointor.PopBack();
            Assert::AreEqual(0u, pointor.Size(),
                L"Size not zero after popping last value");

            const auto constPointor(pointor);
            Assert::AreEqual(0u, constPointor.Size());
        }

        TEST_METHOD(TestSize_Foo)
        {
            Assert::AreEqual(0u, footor.Size(),
                L"Size not zero on empty vector");
            Foo foo(1);
            footor.PushBack(foo);
            Assert::AreEqual(1u, footor.Size(),
                L"Size not one after pushing one value");

            footor.PopBack();
            Assert::AreEqual(0u, footor.Size(),
                L"Size not zero after popping last value");

            const auto constFootor(footor);
            Assert::AreEqual(0u, constFootor.Size());
        }

        TEST_METHOD(TestCapacity_Integer)
        {
            Library::Vector<int> newintvector;
            Assert::AreEqual(10u, newintvector.Capacity(),
                L"New Vector should have a Capacity of 10");

            const auto constIntor(newintvector);
            Assert::AreEqual(10u, constIntor.Capacity());

            for (int i = 0; i < 10; i++)
            {
                intor.PushBack(i);
                Assert::AreEqual(10U, intor.Capacity(),
                    L"First ten pushes on a vector should retain the Capacity At 10");
            }

            intor.PushBack(99);
            Assert::AreEqual(20U, intor.Capacity(),
                L"on 11th push, vector Capacity should be 20");

            for (int i = 0; i < 11; i++)
            {
                intor.PopBack();
                Assert::AreEqual(10U, newintvector.Capacity(),
                    L"New Vector should have Capacity of 10");
            }
        }

        TEST_METHOD(TestCapacity_Pointer)
        {
            Library::Vector<int> newptrvector;
            Assert::AreEqual(10U, newptrvector.Capacity(),
                L"New Vector should have a Capacity of 10");

            const auto constPointor(newptrvector);
            Assert::AreEqual(10U, constPointor.Capacity());

            int x[11];
            for (int i = 0; i < 10; i++)
            {
                x[i] = i;
                pointor.PushBack(&x[i]);
                Assert::AreEqual(10U, pointor.Capacity(),
                    L"First ten pushes on a vector should retain the Capacity At 10");
            }

            x[10] = 99;
            pointor.PushBack(&x[10]);
            Assert::AreEqual(20U, pointor.Capacity(),
                L"on 11th push, vector Capacity should be 20");

            for (int i = 0; i < 11; i++)
            {
                pointor.PopBack();
                Assert::AreEqual(10U, newptrvector.Capacity(),
                    L"New Vector should have Capacity of 10");
            }
        }

        TEST_METHOD(TestCapacity_Foo)
        {
            Library::Vector<int> newfoovector;
            Assert::AreEqual(10u, newfoovector.Capacity(),
                L"New Vector should have a Capacity of 10");

            const auto constFootor(newfoovector);
            Assert::AreEqual(10u, constFootor.Capacity());

            Foo foo[11];
            for (int i = 0; i < 10; i++)
            {
                foo[i] = Foo(i);
                footor.PushBack(foo[i]);
                Assert::AreEqual(10u, footor.Capacity(),
                    L"First ten pushes on a vector should retain the Capacity At 10");
            }

            foo[10] = Foo(99);
            footor.PushBack(foo[10]);
            Assert::AreEqual(20u, footor.Capacity(),
                L"on 11th push, vector Capacity should be 20");

            for (int i = 0; i < 11; i++)
            {
                footor.PopBack();
                Assert::AreEqual(10u, newfoovector.Capacity(),
                    L"New Vector should have Capacity of 10");
            }
        }

        TEST_METHOD(TestIsEmpty_Integer)
        {
            const auto constIntor1(intor);
            Assert::IsTrue(intor.IsEmpty(),
                L"Cleared vector should be empty");
            Assert::IsTrue(constIntor1.IsEmpty());

            intor.PushBack(1);
            const auto constIntor2(intor);
            Assert::IsFalse(intor.IsEmpty(),
                L"Non-empty vector should not be empty");
            Assert::IsFalse(constIntor2.IsEmpty());

            intor.PopBack();
            const auto constIntor3(intor);
            Assert::IsTrue(intor.IsEmpty(),
                L"Vector should be empty after popping last value");
            Assert::IsTrue(constIntor3.IsEmpty());
        }

        TEST_METHOD(TestIsEmpty_Pointer)
        {
            const auto constPointor1(pointor);
            Assert::IsTrue(pointor.IsEmpty(),
                L"Cleared vector should be empty");
            Assert::IsTrue(constPointor1.IsEmpty());

            int x = 1;
            pointor.PushBack(&x);
            const auto constPointor2(pointor);
            Assert::IsFalse(pointor.IsEmpty(),
                L"Non-empty vector should not be empty");
            Assert::IsFalse(constPointor2.IsEmpty());

            pointor.PopBack();
            const auto constPointor3(pointor);
            Assert::IsTrue(pointor.IsEmpty(),
                L"Vector should be empty after popping last value");
            Assert::IsTrue(constPointor3.IsEmpty());
        }

        TEST_METHOD(TestIsEmpty_Foo)
        {
            const auto constFootor1(footor);
            Assert::IsTrue(footor.IsEmpty(),
                L"Cleared vector should be empty");
            Assert::IsTrue(constFootor1.IsEmpty());

            Foo foo(1);
            footor.PushBack(foo);
            const auto constFootor2(footor);
            Assert::IsFalse(footor.IsEmpty(),
                L"Non-empty vector should not be empty");
            Assert::IsFalse(constFootor2.IsEmpty());

            footor.PopBack();
            const auto constFootor3(footor);
            Assert::IsTrue(footor.IsEmpty(),
                L"Vector should be empty after popping last value");
            Assert::IsTrue(constFootor3.IsEmpty());
        }

        TEST_METHOD(TestPushBack_Integer)
        {
            intor.PushBack(1);
            Assert::IsTrue(intor.Back() == 1,
                L"Value pushed to Back does not match");
            Assert::IsTrue(*intor.begin() == 1,
                L"First value pushed Back is not equivalent to begin");

            intor.PushBack(2);
            Assert::IsTrue(intor.Back() == 2,
                L"Second value pushed Back is not equivalent to begin");
        }

        TEST_METHOD(TestPushBack_Pointer)
        {
            int x = 1;
            int y = 2;
            pointor.PushBack(&x);
            Assert::IsTrue(pointor.Back() == &x,
                L"Value pushed to Back does not match");
            Assert::IsTrue(*pointor.begin() == &x,
                L"First value pushed Back is not equivalent to begin");

            pointor.PushBack(&y);
            Assert::IsTrue(pointor.Back() == &y,
                L"Second value pushed Back is not equivalent to begin");
        }

        TEST_METHOD(TestPushBack_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            footor.PushBack(foo);
            Assert::IsTrue(footor.Back() == foo,
                L"Value pushed to Back does not match");
            Assert::IsTrue(*footor.begin() == foo,
                L"First value pushed Back is not equivalent to begin");

            footor.PushBack(bar);
            Assert::IsTrue(footor.Back() == bar,
                L"Second value pushed Back is not equivalent to begin");
        }

        TEST_METHOD(TestReserve_Integer)
        {
            Assert::AreEqual(0u, intor.Capacity(),
                L"Vector Capacity should be zero on Clear");

            intor.Reserve(100);
            Assert::AreEqual(100u, intor.Capacity(),
                L"Vector Capacity not reserving specified value");
            Assert::AreEqual(0u, intor.Size(),
                L"Reserve changing vector Size erroneously");

            intor.Reserve(10);
            Assert::AreEqual(10u, intor.Capacity(),
                L"Capacity not changing on Reserve when shrinking");

            for (int i = 0; i < 10; i++)
            {
                intor.PushBack(i);
            }
            intor.Reserve(5);
            Assert::AreEqual(10u, intor.Capacity(),
                L"Reserving smaller than current Size should shrink to fit");
        }

        TEST_METHOD(TestReserve_Pointer)
        {
            Assert::AreEqual(0u, pointor.Capacity(),
                L"Vector Capacity should be zero on Clear");

            pointor.Reserve(100);
            Assert::AreEqual(100u, pointor.Capacity(),
                L"Vector Capacity not reserving specified value");
            Assert::AreEqual(0u, pointor.Size(),
                L"Reserve changing vector Size erroneously");

            pointor.Reserve(10);
            Assert::AreEqual(10u, pointor.Capacity(),
                L"Capacity not changing on Reserve when shrinking");

            int x[10];
            for (int i = 0; i < 10; i++)
            {
                x[i] = i;
                pointor.PushBack(&x[i]);
            }
            Assert::AreEqual(10u, pointor.Capacity(),
                L"Reserving smaller than current Size should shrink to fit");
        }

        TEST_METHOD(TestReserve_Foo)
        {
            Assert::AreEqual(0u, footor.Capacity(),
                L"Vector Capacity should be zero on Clear");

            footor.Reserve(100);
            Assert::AreEqual(100u, footor.Capacity(),
                L"Vector Capacity not reserving specified value");
            Assert::AreEqual(0u, footor.Size(),
                L"Reserve changing vector Size erroneously");

            footor.Reserve(10);
            Assert::AreEqual(10u, footor.Capacity(),
                L"Capacity not changing on Reserve when shrinking");

            Foo foo(1);
            for (int i = 0; i < 10; i++)
            {
                footor.PushBack(foo);
            }
            Assert::AreEqual(10u, footor.Capacity(),
                L"Reserving smaller than current Size should shrink to fit");
        }

        TEST_METHOD(TestClear_Integer)
        {
            intor.PushBack(1);
            Assert::AreEqual(1u, intor.Size(),
                L"Size incorrect after pushing first value");

            intor.Clear();
            Assert::AreEqual(0u, intor.Size(),
                L"Size not zero after Clear");
            Assert::AreEqual(0u, intor.Capacity(),
                L"Capacity not zero after Clear");
        }

        TEST_METHOD(TestClear_Pointer)
        {
            int x = 1;
            pointor.PushBack(&x);
            Assert::AreEqual(1u, pointor.Size(),
                L"Size incorrect after pushing first value");

            pointor.Clear();
            Assert::AreEqual(0u, pointor.Size(),
                L"Size not zero after Clear");
            Assert::AreEqual(0u, pointor.Capacity(),
                L"Capacity not zero after Clear");
        }

        TEST_METHOD(TestClear_Foo)
        {
            Foo foo(1);
            footor.PushBack(foo);
            Assert::AreEqual(1u, footor.Size(),
                L"Size incorrect after pushing first value");

            footor.Clear();
            Assert::AreEqual(0u, footor.Size(),
                L"Size not zero after Clear");
            Assert::AreEqual(0u, footor.Capacity(),
                L"Capacity not zero after Clear");
        }

        TEST_METHOD(TestRemove_Integer)
        {
            intor.PushBack(1);
            intor.Remove(1);
            Assert::AreEqual(0u, intor.Size(),
                L"Size not reducing after removing a value");

            intor.PushBack(2);
            intor.Remove(1);
            Assert::AreEqual(1u, intor.Size(),
                L"Size changing after removing a nonexistent value");
        }

        TEST_METHOD(TestRemove_Pointer)
        {
            int x = 1;
            int y = 2;
            pointor.PushBack(&x);
            pointor.Remove(&x);
            Assert::AreEqual(0u, pointor.Size(),
                L"Size not reducing after removing a value");

            pointor.PushBack(&y);
            pointor.Remove(&x);
            Assert::AreEqual(1u, pointor.Size(),
                L"Size changing after removing a nonexistent value");
        }

        TEST_METHOD(TestRemove_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            footor.PushBack(foo);
            footor.Remove(foo);
            Assert::AreEqual(0u, footor.Size(),
                L"Size not reducing after removing a value");

            footor.PushBack(bar);
            footor.Remove(foo);
            Assert::AreEqual(1u, footor.Size(),
                L"Size changing after removing a nonexistent value");
        }

        TEST_METHOD(TestShrinkToFit_Integer)
        {
            intor.PushBack(1);
            intor.PushBack(2);
            intor.PushBack(3);
            Assert::AreEqual(10u, intor.Capacity(),
                L"Default Capacity for vector should be 10");

            intor.ShrinkToFit();
            Assert::AreEqual(3u, intor.Capacity(),
                L"Capacity should be 3 after shrinking to fit");

            intor.Clear();
            intor.ShrinkToFit();
            Assert::AreEqual(0u, intor.Capacity(),
                L"Capacity should be 0 after shrinking to fit on empty vector");
        }

        TEST_METHOD(TestShrinkToFit_Pointer)
        {
            int x = 1;
            int y = 2;
            int z = 3;
            pointor.PushBack(&x);
            pointor.PushBack(&y);
            pointor.PushBack(&z);
            Assert::AreEqual(10u, pointor.Capacity(),
                L"Default Capacity for vector should be 10");

            pointor.ShrinkToFit();
            Assert::AreEqual(3u, pointor.Capacity(),
                L"Capacity should be 3 after shrinking to fit");

            pointor.Clear();
            pointor.ShrinkToFit();
            Assert::AreEqual(0u, pointor.Capacity(),
                L"Capacity should be 3 after shrinking to fit on empty vector");
        }

        TEST_METHOD(TestShrinkToFit_Foo)
        {
            Foo foo(1);
            Foo bar(2);
            Foo gar(3);
            footor.PushBack(foo);
            footor.PushBack(bar);
            footor.PushBack(gar);
            Assert::AreEqual(10u, footor.Capacity(),
                L"Default Capacity for vector should be 10");

            footor.ShrinkToFit();
            Assert::AreEqual(3u, footor.Capacity(),
                L"Capacity should be 3 after shrinking to fit");

            footor.Clear();
            footor.ShrinkToFit();
            Assert::AreEqual(0u, footor.Capacity(),
                L"Capacity should be 3 after shrinking to fit on empty vector");
        }

        TEST_METHOD(TestIteratorComparisonOperator_Integer)
        {
            auto iter = intor.begin();
            const auto iterCopy(iter);
            Assert::IsTrue(iter == intor.begin(),
                L"Iterator should be equivalent to the value it was assigned to");
            Assert::IsTrue(iter == intor.end(),
                L"Iterator should be equivalent to end when assigned to begin on an empty vector");
            Assert::IsTrue(iterCopy == intor.begin());
            Assert::IsTrue(iterCopy == intor.end());

            intor.PushBack(1);
            iter = intor.begin();
            const auto secondIterCopy(iter);
            Assert::IsFalse(iter == intor.end(),
                L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
            Assert::IsFalse(secondIterCopy == intor.end());

            Library::Vector<int> newintvector;
            auto newiter = newintvector.begin();
            const auto newIterCopy(newiter);
            Assert::IsFalse(iter == newiter,
                L"Iterators with different owners should not be equivalent");
            Assert::IsTrue(newIterCopy == newiter);
        }

        TEST_METHOD(TestIteratorComparisonOperator_Pointer)
        {
            auto piter = pointor.begin();
            const auto piterCopy(piter);
            Assert::IsTrue(piter == pointor.begin(),
                L"Iterator should be equivalent to the value it was assigned to");
            Assert::IsTrue(piter == pointor.end(),
                L"Iterator should be equivalent to end when assigned to begin on an empty vector");
            Assert::IsTrue(piterCopy == pointor.begin());
            Assert::IsTrue(piterCopy == pointor.end());

            int x = 1;
            pointor.PushBack(&x);
            piter = pointor.begin();
            const auto piterSecondCopy(piter);
            Assert::IsFalse(piter == pointor.end(),
                L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
            Assert::IsFalse(piterSecondCopy == pointor.end());

            Library::Vector<int*> newptrvector;
            auto newpiter = newptrvector.begin();
            const auto newpiterCopy(newpiter);
            Assert::IsFalse(piter == newpiter,
                L"Iterators with different owners should not be equivalent");
            Assert::IsTrue(newpiterCopy == newpiter);
        }

        TEST_METHOD(TestIteratorComparisonOperator_Foo)
        {
            auto fooiter = footor.begin();
            const auto fooiterCopy(fooiter);
            Assert::IsTrue(fooiter == footor.begin(),
                L"Iterator should be equivalent to the value it was assigned to");
            Assert::IsTrue(fooiter == footor.end(),
                L"Iterator should be equivalent to end when assigned to begin on an empty vector");
            Assert::IsTrue(fooiterCopy == footor.begin());
            Assert::IsTrue(fooiterCopy == footor.end());

            Foo foo(1);
            footor.PushBack(foo);
            fooiter = footor.begin();
            const auto fooiterSecondCopy(fooiter);
            Assert::IsFalse(fooiter == footor.end(),
                L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
            Assert::IsFalse(fooiterSecondCopy == footor.end());

            Library::Vector<Foo> newfoovector;
            auto newfooiter = newfoovector.begin();
            const auto newfooiterCopy(newfooiter);
            Assert::IsFalse(fooiter == newfooiter,
                L"Iterators with different owners should not be equivalent");
            Assert::IsTrue(newfooiterCopy == newfooiter);
        }

        TEST_METHOD(TestIteratorIncrement_Integer)
        {
            intor.PushBack(1);
            auto iter = intor.begin();
            Assert::IsFalse(iter == intor.end(),
                L"Iterator assigned to begin on a non-empty vector should not be equivalent to end");
            Assert::IsTrue(++iter == intor.end(),
                L"Incrementing an iterator on a Size of one vector should be equivalent to end");
        }

        TEST_METHOD(TestIteratorIncrement_Pointer)
        {
            int x = 1;
            pointor.PushBack(&x);
            auto piter = pointor.begin();
            Assert::IsFalse(piter == pointor.end(),
                L"piterator assigned to begin on a non-empty vector should not be equivalent to end");
            Assert::IsTrue(++piter == pointor.end(),
                L"Incrementing an piterator on a Size of one vector should be equivalent to end");
        }

        TEST_METHOD(TestIteratorIncrement_Foo)
        {
            Foo foo(1);
            footor.PushBack(foo);
            auto fooiter = footor.begin();
            Assert::IsFalse(fooiter == footor.end(),
                L"fooiterator assigned to begin on a non-empty vector should not be equivalent to end");
            Assert::IsTrue(++fooiter == footor.end(),
                L"Incrementing an fooiterator on a Size of one vector should be equivalent to end");
        }

        TEST_METHOD(TestIteratorDereference_Integer)
        {
            auto iter = intor.begin();
            auto func1 = [&] { *iter; };
            Assert::ExpectException<std::exception>(func1,
                L"Dereferencing begin on an empty vector should throw an exception");

            intor.PushBack(1);
            iter = intor.begin();
            Assert::IsTrue(*iter == 1,
                L"Dereferencing an iterator At begin should be equivalent to the first value pushed");

            const auto constIntVector(intor);
            Assert::IsTrue(*constIntVector.begin() == *intor.begin(),
                L"Const copy begin not equivalent to original");

            ++iter;
            Assert::ExpectException<std::exception>(func1,
                L"Dereferencing end of a vector should throw an exception");
        }

        TEST_METHOD(TestIteratorDereference_Pointer)
        {
            auto piter = pointor.begin();
            auto func2 = [&] { *piter; };
            Assert::ExpectException<std::exception>(func2,
                L"Dereferencing begin on an empty vector should throw an exception");

            int x = 1;
            pointor.PushBack(&x);
            piter = pointor.begin();
            Assert::IsTrue(*piter == &x,
                L"Dereferencing an piterator At begin should be equivalent to the first value pushed");

            const auto constPtrVector(pointor);
            Assert::IsTrue(*constPtrVector.begin() == *pointor.begin(),
                L"Const copy begin not equivalent to original");

            ++piter;
            Assert::ExpectException<std::exception>(func2,
                L"Dereferencing end of a vector should throw an exception");
        }

        TEST_METHOD(TestIteratorDereference_Foo)
        {
            auto fooiter = footor.begin();
            auto func3 = [&] { *fooiter; };
            Assert::ExpectException<std::exception>(func3,
                L"Dereferencing begin on an empty vector should throw an exception");

            Foo foo(1);
            footor.PushBack(foo);
            fooiter = footor.begin();
            Assert::IsTrue(*fooiter == foo,
                L"Dereferencing an fooiterator At begin should be equivalent to the first value pushed");

            const auto constFooVector(footor);
            Assert::IsTrue(*constFooVector.begin() == *footor.begin(),
                L"Const copy begin not equivalent to original");

            ++fooiter;
            Assert::ExpectException<std::exception>(func3,
                L"Dereferencing end of a vector should throw an exception");
        }

    };

}