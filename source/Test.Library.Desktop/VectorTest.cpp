 #include "pch.h"
#include "CppUnitTest.h"
#include <Vector.h>
#include "Foo.h"
#include "implementation.h"
#include <winnt.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(VectorTest)
	{
	public:
		Library::Vector<int>  intor;
		Library::Vector<int*> pointor;
		Library::Vector<Foo>  footor;

		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
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
#endif //_Debug
		}

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			intor.Clear();
			pointor.Clear();
			footor.Clear();
			initializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			intor.Clear();
			pointor.Clear();
			footor.Clear();
			// Here is the problem. Because these are class-level, even though they
			// Destruct safely and are cleared on method Initialize, on cleanup they can still have mem allocated
			finalizeLeakDetection();
		}

		TEST_METHOD(TestCopyConstructor)
		{
			/// Int vector tests
			Library::Vector<int> copyIntor(intor);
			bool intcompare = intor == copyIntor;
			Assert::IsTrue(intcompare, L"Copied vector not equivalent to original");
			
			intor.PushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsFalse(intcompare, L"Copied vector equivalent after modifying original");
			
			copyIntor.PushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsTrue(intcompare, L"Copied vector not equivalent after pushing identical values");

			Library::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, L"Copied pointer vector not equivalent to original");
			

			/// Pointer vector tests
			int x = 1;
			pointor.PushBack(&x);
			Assert::IsFalse(pointor == copyPointor, L"Copied vector equivalent after modifying original");
			
			copyPointor.PushBack(&x);
			Assert::IsTrue(pointor == copyPointor, L"Copied vector not equivalent after pushing identical values");

			Library::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor, L"Copied Foo vector not equivalent to original");
			

			/// Foo vector tests
			Foo foo(1);
			footor.PushBack(foo);
			Assert::IsFalse(footor == copyFootor, L"Copied Foo vector equivalent after modifying original");
			
			copyFootor.PushBack(foo);
			Assert::IsTrue(footor == copyFootor, L"Copied vector not equivalent after pushing identical values");
		}

		TEST_METHOD(TestComparisonOperator)
		{
			/// Int vector tests
			Assert::IsTrue(intor == intor, L"Vector not equivalent to itself");
			
			Library::Vector<int> copyIntor(intor);
			Assert::IsTrue(intor == copyIntor, L"Copy constructor invocation not equivalent");
			
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, L"Assignment operator copy not equivalent");

			const auto constIntor(intor);
			Assert::IsTrue(intor == constIntor, L"Const copy not equivalent");
			

			/// Pointer vector tests
			Assert::IsTrue(pointor == pointor, L"Vector not equivalent to itself");

			Library::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, L"Copy constructor invocation not equivalent");
			
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, L"Assignment operator copy not equivalent");
			
			const auto constPointor(pointor);
			Assert::IsTrue(pointor == constPointor, L"Const copy not equivalent");


			/// Foo vector tests
			Assert::IsTrue(footor == footor, L"Vector not equivalent to itself");

			Library::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor, L"Copy constructor invocation not equivalent");
			
			copyFootor = footor;
			Assert::IsTrue(footor == copyFootor, L"Assignment operator copy not equivalent");

			const auto constFootor(footor);
			Assert::IsTrue(footor == constFootor, L"Const copy not equivalent");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			/// Int vector tests
			Library::Vector<int> copyIntor;
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, L"Copied vector not equivalent to original");


			/// Pointer vector tests
			Library::Vector<int*> copyPointor;
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, L"Copied pointer vector not equivalent to original");


			/// Foo vector tests
			Library::Vector<Foo> copyFootor;
			copyFootor = footor;
			Assert::IsTrue(footor == copyFootor, L"Copied Foo vector not equivalent to original");
		}

		TEST_METHOD(TestFind)
		{
			/// Int vector tests
			auto iter = intor.Find(0);
			Assert::IsTrue(iter == intor.end(), L"begin and end not equivalent on empty vector");
			Assert::IsTrue(iter == intor.begin(), L"Find on first element not equivalent to Vector.begin()");
			
			intor.PushBack(1);
			iter = intor.Find(1);
			Assert::IsFalse(iter == intor.end(), L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(iter == intor.begin(), L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*iter, 1, L"Find on first item should be equivalent to the first value pushed");
			
			intor.PushBack(100);
			iter = intor.Find(1);
			Assert::IsTrue(iter == intor.begin(), L"Find on first item should not change after pushing a second");
			Assert::IsFalse(iter == intor.end(), L"Find on existing item should not be equivalent to end");
			
			iter = intor.Find(100);
			Assert::IsTrue(++iter == intor.end(), L"Incrementing past final element not equivalent to end");

			const auto constIntor(intor);
			Assert::IsTrue(constIntor.Find(1) == constIntor.begin(), L"Const Find value incorrect");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			auto piter = pointor.Find(&x);
			Assert::IsTrue(piter == pointor.end(), L"begin and end not equivalent on empty vector");
			Assert::IsTrue(piter == pointor.begin(), L"Find on first element not equivalent to Vector.begin()");
			
			pointor.PushBack(&x);
			piter = pointor.Find(&x);
			Assert::IsFalse(piter == pointor.end(), L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(piter == pointor.begin(), L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*piter, &x, L"Find on first item should be equivalent to the first value pushed");
			
			pointor.PushBack(&y);
			piter = pointor.Find(&x);
			Assert::IsTrue(piter == pointor.begin(), L"Find on first item should not change after pushing a second");
			Assert::IsFalse(piter == pointor.end(), L"Find on existing item should not be equivalent to end");
			
			piter = pointor.Find(&y);
			Assert::IsTrue(++piter == pointor.end(), L"Incrementing past final element not equivalent to end");

			const auto constPointor(pointor);
			Assert::IsTrue(constPointor.Find(&x) == constPointor.begin(), L"Const Find value incorrect");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			auto fooiter = footor.Find(foo);
			Assert::IsTrue(fooiter == footor.end(), L"begin and end not equivalent on empty vector");
			Assert::IsTrue(fooiter == footor.begin(), L"Find on first element not equivalent to Vector.begin()");
			
			footor.PushBack(foo);
			fooiter = footor.Find(foo);
			Assert::IsFalse(fooiter == footor.end(), L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(fooiter == footor.begin(), L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*fooiter, foo, L"Find on first item should be equivalent to the first value pushed");
			
			footor.PushBack(bar);
			fooiter = footor.Find(foo);
			Assert::IsTrue(fooiter == footor.begin(), L"Find on first item should not change after pushing a second");
			Assert::IsFalse(fooiter == footor.end(), L"Find on existing item should not be equivalent to end");
			
			fooiter = footor.Find(bar);
			Assert::IsTrue(++fooiter == footor.end(), L"Incrementing past final element not equivalent to end");

			const auto constFootor(footor);
			Assert::IsTrue(constFootor.Find(foo) == constFootor.begin(), L"Const Find value incorrect");
		}

		TEST_METHOD(TestBegin)
		{
			/// Int vector tests
			Assert::IsTrue(intor.begin() == intor.end(), L"begin should be equivalent to end on an empy vector");
			
			intor.PushBack(1);
			Assert::IsTrue(1 == *intor.begin(), L"begin not equivalent with first value pushed");
			Assert::IsFalse(intor.begin() == intor.end());
			
			intor.PushBack(2);
			Assert::IsTrue(1 == *intor.begin(), L"begin value changed after calling push Back on non-empty vector");
			Assert::IsTrue(intor[0] == *intor.begin(), L"First index not equivalent to begin");

			const auto constIntor(intor);
			Assert::IsTrue(*constIntor.begin() == constIntor[0]);


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			Assert::IsTrue(pointor.begin() == pointor.end(), L"begin should be equivalent to end on an empy vector");
			
			pointor.PushBack(&x);
			Assert::IsTrue(&x == *pointor.begin(), L"begin not equivalent with first value pushed");
			Assert::IsFalse(pointor.begin() == pointor.end());
			
			pointor.PushBack(&y);
			Assert::IsTrue(&x == *pointor.begin(), L"begin value changed after calling push Back on non-empty vector");
			Assert::IsTrue(pointor[0] == *pointor.begin(), L"First index not equivalent to begin");

			const auto constPointor(pointor);
			Assert::IsTrue(*constPointor.begin() == constPointor[0]);


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			Assert::IsTrue(footor.begin() == footor.end(), L"begin should be equivalent to end on an empy vector");
			
			footor.PushBack(foo);
			Assert::IsTrue(foo == *footor.begin(), L"begin not equivalent with first value pushed");
			Assert::IsFalse(footor.begin() == footor.end());
			
			footor.PushBack(bar);
			Assert::IsTrue(foo == *footor.begin(), L"begin value changed after calling push Back on non-empty vector");
			Assert::IsTrue(footor[0] == *footor.begin(), L"First index not equivalent to begin");

			const auto constFootor(footor);
			Assert::IsTrue(*constFootor.begin() == constFootor[0]);
		}

		TEST_METHOD(TestEnd)
		{
			/// Int vector tests
			Assert::IsTrue(intor.begin() == intor.end(), L"end should be equivalent to begin on an empty vector");
			
			Library::Vector<int>::Iterator iter = intor.end();
			Assert::IsTrue(iter == intor.end(), L"Iterator assigned to end should be equivalent to end");
			
			intor.PushBack(1);
			iter = intor.begin();
			Assert::IsFalse(iter == intor.end(), L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++iter == intor.end(), L"Iterator pointing to last element should be equivalent to end after incrementing");

			Assert::IsTrue(pointor.begin() == pointor.end(), L"end should be equivalent to begin on an empty vector");
			
			Library::Vector<int*>::Iterator piter = pointor.end();
			Assert::IsTrue(piter == pointor.end(), L"Iterator assigned to end should be equivalent to end");

			const auto constIntor(intor);
			auto constIter = constIntor.end();
			Assert::IsTrue(constIter == constIntor.end());
			

			/// Pointer vector tests
			int x = 1;
			pointor.PushBack(&x);
			piter = pointor.begin();
			Assert::IsFalse(piter == pointor.end(), L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++piter == pointor.end(), L"Iterator pointing to last element should be equivalent to end after incrementing");

			Assert::IsTrue(footor.begin() == footor.end(), L"end should be equivalent to begin on an empty vector");
			
			Library::Vector<Foo>::Iterator fooiter = footor.end();
			Assert::IsTrue(fooiter == footor.end(), L"Iterator assigned to end should be equivalent to end");
			
			const auto constPointor(pointor);
			auto constPIter = constPointor.end();
			Assert::IsTrue(constPIter == constPointor.end());


			/// Foo vector tests
			Foo foo(1);
			footor.PushBack(foo);
			fooiter = footor.begin();
			Assert::IsFalse(fooiter == footor.end(), L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++fooiter == footor.end(), L"Iterator pointing to last element should be equivalent to end after incrementing");

			const auto constFootor(footor);
			auto constFooIter = constFootor.end();
			Assert::IsTrue(constFooIter == constFootor.end());
		}

		TEST_METHOD(TestFront)
		{
			/// Int vector tests
			auto func = [this] { intor.Front(); };
			Assert::ExpectException<std::exception>(func, L"Front should be equivalent with begin on an empty vector");
			
			intor.PushBack(1);
			Assert::IsTrue(intor.Front() == intor[0], L"Front should be equivalent with first index");
			Assert::IsTrue(intor.Front() == *intor.begin(), L"Front should be equivalent with begin");
			
			intor.Front() = 5;
			Assert::IsTrue(intor.Front() == 5, L"Unable to modify Vector.Front()");

			const Library::Vector<int> constIntVector(intor);
//			auto val = constIntVector.Front();
			Assert::IsTrue(constIntVector.Front() == intor.Front(), L"Front of const copied vector should be equivalent to original");

			/// Pointer vector tests
			auto ptrfunc = [this] { pointor.Front(); };
			Assert::ExpectException<std::exception>(ptrfunc, L"Front should be equivalent with begin on an empty vector");
			
			int x = 1;
			pointor.PushBack(&x);
			Assert::IsTrue(pointor.Front() == pointor[0], L"Front should be equivalent with first index");
			Assert::IsTrue(pointor.Front() == *pointor.begin(), L"Front should be equivalent with begin");
			
			int y = 5;
			pointor.Front() = &y;
			Assert::IsTrue(pointor.Front() == &y, L"Unable to modify Vector.Front()");

			const Library::Vector<int*> constPtrVector(pointor);
			Assert::IsTrue(constPtrVector.Front() == pointor.Front(), L"Front of const copied vector should be equivalent to original");

			/// Foo vector tests
			auto foofunc = [this] { footor.Front(); };
			Assert::ExpectException<std::exception>(foofunc, L"Front should be equivalent with begin on an empty vector");
			
			Foo foo(1);
			footor.PushBack(foo);
			Assert::IsTrue(footor.Front() == footor[0], L"Front should be equivalent with first index");
			Assert::IsTrue(footor.Front() == *footor.begin(), L"Front should be equivalent with begin");
			
			Foo bar(5);
			footor.Front() = bar;
			Assert::IsTrue(footor.Front() == bar, L"Unable to modify Vector.Front()");

			const Library::Vector<Foo> constFooVector(footor);
			Assert::IsTrue(constFooVector.Front() == footor.Front(), L"Front of constant copied vector not equal to original vector's Front");
			Assert::IsTrue(true);
		}

		TEST_METHOD(TestBack)
		{
			/// Int vector tests
			auto func = [this] { intor.Back(); };
			Assert::ExpectException<std::exception>(func, L"Calling Back on an empty vector should throw an exception");
			
			intor.PushBack(1);
			Assert::IsTrue(intor.Back() == intor[0], L"Back should be equivalent to first value pushed onto an empty vector");
			
			intor.PushBack(2);
			Assert::IsTrue(intor.Back() == intor[1], L"Back should b equivalent to last value pushed onto a vector");
			
			intor.Back() = 10;
			Assert::IsTrue(intor.Back() == 10, L"Vector.Back() not modifiable");


			/// Pointer vector tests
			auto ptrfunc = [this] { pointor.Back(); };
			Assert::ExpectException<std::exception>(ptrfunc, L"Calling Back on an empty vector should throw an exception");
			
			int x = 1;
			pointor.PushBack(&x);
			Assert::IsTrue(pointor.Back() == pointor[0], L"Back should be equivalent to first value pushed onto an empty vector");
			
			int y = 2;
			pointor.PushBack(&y);
			Assert::IsTrue(pointor.Back() == pointor[1], L"Back should b equivalent to last value pushed onto a vector");
			
			int z = 10;
			pointor.Back() = &z;
			Assert::IsTrue(pointor.Back() == &z, L"Vector.Back() not modifiable");


			/// Foo vector tests
			auto foofunc = [this] { footor.Back(); };
			Assert::ExpectException<std::exception>(foofunc, L"Calling Back on an empty vector should throw an exception");
			
			Foo foo(1);
			footor.PushBack(foo);
			Assert::IsTrue(footor.Back() == footor[0], L"Back should be equivalent to first value pushed onto an empty vector");
			
			Foo bar(2);
			footor.PushBack(bar);
			Assert::IsTrue(footor.Back() == footor[1], L"Back should b equivalent to last value pushed onto a vector");
			
			Foo gar(10);
			footor.Back() = gar;
			Assert::IsTrue(footor.Back() == gar, L"Vector.Back() not modifiable");
		}

		TEST_METHOD(TestAt)
		{
			/// Int vector tests
			auto func1 = [this] { intor.At(0U); };
			Assert::ExpectException<std::exception>(func1, L"Accessing index of an empty vector should throw an exception");
			
			intor.PushBack(1);
			auto func2 = [this] { intor.At(1U); };
			Assert::ExpectException<std::exception>(func2, L"Accessing out of vector bounds should throw an exception");
			
			intor.PushBack(2);
			Assert::IsTrue(1 == intor.At(0U), L"First element should be equivalent to Vector.At(0) after pushing Back multiple values");
			Assert::IsTrue(2 == intor.At(1U), L"Last element should be equivalent to Vector.At(n-1)");

			const auto constIntor(intor);
			Assert::IsTrue(1 == constIntor.At(0U));
			Assert::IsTrue(2 == constIntor.At(1U));


			/// Pointer vector tests
			auto ptrfunc1 = [this] { pointor.At(0U); };
			Assert::ExpectException<std::exception>(ptrfunc1, L"Accessing index of an empty vector should throw an exception");
			
			int x = 1;
			pointor.PushBack(&x);
			auto ptrfunc2 = [this] { pointor.At(1U); };
			Assert::ExpectException<std::exception>(ptrfunc2, L"Accessing out of vector bounds should throw an exception");
			
			int y = 2;
			pointor.PushBack(&y);
			Assert::IsTrue(&x == pointor.At(0), L"First element should be equivalent to Vector.At(0) after pushing Back multiple values");
			Assert::IsTrue(&y == pointor.At(1), L"Last element should be equivalent to Vector.At(n-1)");

			const auto constPointor(pointor);
			Assert::IsTrue(&x == constPointor.At(0));
			Assert::IsTrue(&y == constPointor.At(1));

			/// Foo vector tests
			auto foofunc1 = [this] { footor.At(0); };
			Assert::ExpectException<std::exception>(foofunc1, L"Accessing index of an empty vector should throw an exception");
			
			Foo foo(1);
			footor.PushBack(foo);
			auto foofunc2 = [this] { footor.At(1); };
			Assert::ExpectException<std::exception>(foofunc2, L"Accessing out of vector bounds should throw an exception");
		
			Foo bar(2);
			footor.PushBack(bar);
			Assert::IsTrue(foo == footor.At(0), L"First element should be equivalent to Vector.At(0) after pushing Back multiple values");
			Assert::IsTrue(bar == footor.At(1), L"Last element should be equivalent to Vector.At(n-1)");

			const auto constFootor(footor);
			Assert::IsTrue(foo == constFootor.At(0));
			Assert::IsTrue(bar == constFootor.At(1));
		}

		TEST_METHOD(TestIndexOperator)
		{
			/// Int vector tests
			auto func1 = [this] { intor[0]; };
			Assert::ExpectException<std::exception>(func1, L"Accessing index of an empty vector should throw an exception");
			
			intor.PushBack(1);
			auto func2 = [this] { intor[1]; };
			Assert::ExpectException<std::exception>(func2, L"Accessing out of vector bounds should throw an exception");
			
			intor.PushBack(2);
			Assert::IsTrue(1 == intor[0], L"First element should be equivalent to Vector[0] after pushing Back multiple values");
			Assert::IsTrue(2 == intor[1], L"Last element should be equivalent to Vector[n-1]");

			const auto constIntor(intor);
			Assert::IsTrue(1 == constIntor[0]);
			Assert::IsTrue(2 == constIntor[1]);


			/// Pointer vector tests
			auto ptrfunc1 = [this] { pointor[0]; };
			Assert::ExpectException<std::exception>(ptrfunc1, L"Accessing index of an empty vector should throw an exception");
			
			int x = 1;
			pointor.PushBack(&x);
			auto ptrfunc2 = [this] { pointor[1]; };
			Assert::ExpectException<std::exception>(ptrfunc2, L"Accessing out of vector bounds should throw an exception");
			
			int y = 2;
			pointor.PushBack(&y);
			Assert::IsTrue(&x == pointor[0], L"First element should be equivalent to Vector[0] after pushing Back multiple values");
			Assert::IsTrue(&y == pointor[1], L"Last element should be equivalent to Vector[n-1]");

			const auto constPointor(pointor);
			Assert::IsTrue(&x == constPointor[0]);
			Assert::IsTrue(&y == constPointor[1]);


			/// Foo vector tests
			auto foofunc1 = [this] { footor[0U]; };
			Assert::ExpectException<std::exception>(foofunc1, L"Accessing index of an empty vector should throw an exception");
			
			Foo foo(1);
			footor.PushBack(foo);
			auto foofunc2 = [this] { footor[1U]; };
			Assert::ExpectException<std::exception>(foofunc2, L"Accessing out of vector bounds should throw an exception");
			
			Foo bar(2);
			footor.PushBack(bar);
			Assert::IsTrue(foo == footor[0], L"First element should be equivalent to Vector[0] after pushing Back multiple values");
			Assert::IsTrue(bar == footor[1], L"Last element should be equivalent to Vector[n-1]");

			const auto constFootor(footor);
			Assert::IsTrue(foo == constFootor[0]);
			Assert::IsTrue(bar == constFootor[1]);
		}

		TEST_METHOD(TestPopBack)
		{
			/// Int vector tests
			auto func1 = [this] { intor.PopBack(); };
			Assert::ExpectException<std::exception>(func1, L"PopBack on empty vector should throw an exception");
			
			intor.PushBack(1);
			intor.PushBack(2);
			intor.PushBack(3);
			intor.PopBack();
			Assert::AreEqual(2U, intor.Size(), L"Vector Size not reducing after valid pop Back");


//			/// Pointer vector tests
			auto ptrfunc1 = [this] { pointor.PopBack(); };
			Assert::ExpectException<std::exception>(ptrfunc1, L"PopBack on empty vector should throw an exception");
			
			int x = 1;
			int y = 2;
			int z = 3;
			pointor.PushBack(&x);
			pointor.PushBack(&y);
			pointor.PushBack(&z);
			pointor.PopBack();
			Assert::AreEqual(2U, pointor.Size(), L"Vector Size not reducing after valid pop Back");


			/// Foo vector tests
			auto foofunc1 = [this] { footor.PopBack(); };
			Assert::ExpectException<std::exception>(foofunc1, L"PopBack on empty vector should throw an exception");
			
			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			footor.PushBack(foo);
			footor.PushBack(bar);
			footor.PushBack(gar);
			footor.PopBack();
			Assert::AreEqual(2U, footor.Size(), L"Vector Size not reducing after valid pop Back");
		}

		TEST_METHOD(TestSize)
		{
			intor.Reserve(10);
			intor.Reserve(10);
			intor.PushBack(1);
			intor.PopBack();
			/// Int vector tests
			Assert::IsTrue(intor.Size() == 0, L"Size not zero on empty vector");
			
			intor.PushBack(1);
			Assert::IsTrue(intor.Size() == 1, L"Size not one after pushing one value");
			
			intor.PopBack();
			Assert::IsTrue(intor.Size() == 0, L"Size not zero after popping last value");
			
			const auto constIntor(intor);
			Assert::IsTrue(constIntor.Size() == 0);


			/// Pointer vector tests
			Assert::IsTrue(pointor.Size() == 0, L"Size not zero on empty vector");

			int x = 1;
			pointor.PushBack(&x);
			Assert::IsTrue(pointor.Size() == 1, L"Size not one after pushing one value");
			
			pointor.PopBack();
			Assert::IsTrue(pointor.Size() == 0, L"Size not zero after popping last value");

			const auto constPointor(pointor);
			Assert::IsTrue(constPointor.Size() == 0);


			/// Foo vector tests
			Assert::IsTrue(footor.Size() == 0, L"Size not zero on empty vector");
			Foo foo(1);
			footor.PushBack(foo);
			Assert::IsTrue(footor.Size() == 1, L"Size not one after pushing one value");
			
			footor.PopBack();
			Assert::IsTrue(footor.Size() == 0, L"Size not zero after popping last value");

			const auto constFootor(footor);
			Assert::IsTrue(constFootor.Size() == 0);
		}

		TEST_METHOD(TestCapacity)
		{
			/// Int vector tests
			Library::Vector<int> newintvector;
			Assert::AreEqual(10U, newintvector.Capacity(), L"New Vector should have a Capacity of 10");
			
			const auto constIntor(newintvector);
			Assert::AreEqual(10U, constIntor.Capacity());

			for (int i = 0; i < 10; i++)
			{
				intor.PushBack(i);
				Assert::AreEqual(10U, intor.Capacity(), L"First ten pushes on a vector should retain the Capacity At 10");
			}
			
			intor.PushBack(99);
			Assert::AreEqual(20U, intor.Capacity(), L"on 11th push, vector Capacity should be 20");
			
			for (int i = 0; i < 11; i++)
			{
				intor.PopBack();
				Assert::AreEqual(10U, newintvector.Capacity(), L"New Vector should have Capacity of 10");
			}
			

			/// Pointer vector tests
			Library::Vector<int> newptrvector;
			Assert::AreEqual(10U, newptrvector.Capacity(), L"New Vector should have a Capacity of 10");
			
			const auto constPointor(newptrvector);
			Assert::AreEqual(10U, constPointor.Capacity());

			int x[11];
			for (int i = 0; i < 10; i++)
			{
				x[i] = i;
				pointor.PushBack(&x[i]);
				Assert::AreEqual(10U, pointor.Capacity(), L"First ten pushes on a vector should retain the Capacity At 10");
			}
			
			x[10] = 99;
			pointor.PushBack(&x[10]);
			Assert::AreEqual(20U, pointor.Capacity(), L"on 11th push, vector Capacity should be 20");

			for (int i = 0; i < 11; i++)
			{
				pointor.PopBack();
				Assert::AreEqual(10U, newptrvector.Capacity(), L"New Vector should have Capacity of 10");
			}


			/// Foo vector tests
			Library::Vector<int> newfoovector;
			Assert::AreEqual(10U, newfoovector.Capacity(), L"New Vector should have a Capacity of 10");
			
			const auto constFootor(newfoovector);
			Assert::AreEqual(10U, constFootor.Capacity());

			Foo foo[11];
			for (int i = 0; i < 10; i++)
			{
				foo[i] = Foo(i);
				footor.PushBack(foo[i]);
				Assert::AreEqual(10U, footor.Capacity(), L"First ten pushes on a vector should retain the Capacity At 10");
			}
			
			foo[10] = Foo(99);
			footor.PushBack(foo[10]);
			Assert::AreEqual(20U, footor.Capacity(), L"on 11th push, vector Capacity should be 20");
			
			for (int i = 0; i < 11; i++)
			{
				footor.PopBack();
				Assert::AreEqual(10U, newfoovector.Capacity(), L"New Vector should have Capacity of 10");
			}
		}

		TEST_METHOD(TestIsEmpty)
		{
			/// Int vector tests
			const auto constIntor1(intor);
			Assert::IsTrue(intor.IsEmpty(), L"Cleared vector should be empty");
			Assert::IsTrue(constIntor1.IsEmpty());
			
			intor.PushBack(1);
			const auto constIntor2(intor);
			Assert::IsFalse(intor.IsEmpty(), L"Non-empty vector should not be empty");
			Assert::IsFalse(constIntor2.IsEmpty());
			
			intor.PopBack();
			const auto constIntor3(intor);
			Assert::IsTrue(intor.IsEmpty(), L"Vector should be empty after popping last value");
			Assert::IsTrue(constIntor3.IsEmpty());


			/// Pointer vector tests
			const auto constPointor1(pointor);
			Assert::IsTrue(pointor.IsEmpty(), L"Cleared vector should be empty");
			Assert::IsTrue(constPointor1.IsEmpty());
			
			int x = 1;
			pointor.PushBack(&x);
			const auto constPointor2(pointor);
			Assert::IsFalse(pointor.IsEmpty(), L"Non-empty vector should not be empty");
			Assert::IsFalse(constPointor2.IsEmpty());
			
			pointor.PopBack();
			const auto constPointor3(pointor);
			Assert::IsTrue(pointor.IsEmpty(), L"Vector should be empty after popping last value");
			Assert::IsTrue(constPointor3.IsEmpty());


			/// Foo vector tests
			const auto constFootor1(footor);
			Assert::IsTrue(footor.IsEmpty(), L"Cleared vector should be empty");
			Assert::IsTrue(constFootor1.IsEmpty());
			
			Foo foo(1);
			footor.PushBack(foo);
			const auto constFootor2(footor);
			Assert::IsFalse(footor.IsEmpty(), L"Non-empty vector should not be empty");
			Assert::IsFalse(constFootor2.IsEmpty());
			
			footor.PopBack();
			const auto constFootor3(footor);
			Assert::IsTrue(footor.IsEmpty(), L"Vector should be empty after popping last value");
			Assert::IsTrue(constFootor3.IsEmpty());
		}

		TEST_METHOD(TestPushBack)
		{
			/// Int vector tests
			intor.PushBack(1);
			Assert::IsTrue(intor.Back() == 1, L"Value pushed to Back does not match");
			Assert::IsTrue(*intor.begin() == 1, L"First value pushed Back is not equivalent to begin");
			
			intor.PushBack(2);
			Assert::IsTrue(intor.Back() == 2, L"Second value pushed Back is not equivalent to begin");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			pointor.PushBack(&x);
			Assert::IsTrue(pointor.Back() == &x, L"Value pushed to Back does not match");
			Assert::IsTrue(*pointor.begin() == &x, L"First value pushed Back is not equivalent to begin");
			
			pointor.PushBack(&y);
			Assert::IsTrue(pointor.Back() == &y, L"Second value pushed Back is not equivalent to begin");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			footor.PushBack(foo);
			Assert::IsTrue(footor.Back() == foo, L"Value pushed to Back does not match");
			Assert::IsTrue(*footor.begin() == foo, L"First value pushed Back is not equivalent to begin");
			
			footor.PushBack(bar);
			Assert::IsTrue(footor.Back() == bar, L"Second value pushed Back is not equivalent to begin");
		}

		TEST_METHOD(TestReserve)
		{
			/// Int vector tests
			Assert::IsTrue(intor.Capacity() == 0, L"Vector Capacity should be zero on Clear");
			
			intor.Reserve(100);
			Assert::IsTrue(intor.Capacity() == 100, L"Vector Capacity not reserving specified value");
			Assert::IsTrue(intor.Size() == 0, L"Reserve changing vector Size erroneously");
			
			intor.Reserve(10);
			Assert::IsTrue(intor.Capacity() == 10, L"Capacity not changing on Reserve when shrinking");
			
			for (int i = 0; i < 10; i++)
			{
				intor.PushBack(i);
			}
			intor.Reserve(5);
			Assert::IsTrue(intor.Capacity() == 10, L"Reserving smaller than current Size should shrink to fit");


			/// Pointer vector tests
			Assert::IsTrue(pointor.Capacity() == 0, L"Vector Capacity should be zero on Clear");
			
			pointor.Reserve(100);
			Assert::IsTrue(pointor.Capacity() == 100, L"Vector Capacity not reserving specified value");
			Assert::IsTrue(pointor.Size() == 0, L"Reserve changing vector Size erroneously");
			
			pointor.Reserve(10);
			Assert::IsTrue(pointor.Capacity() == 10, L"Capacity not changing on Reserve when shrinking");
			
			int x[10];
			for (int i = 0; i < 10; i++)
			{
				x[i] = i;
				pointor.PushBack(&x[i]);
			}
			Assert::IsTrue(intor.Capacity() == 10, L"Reserving smaller than current Size should shrink to fit");


			/// Foo vector tests
			Assert::IsTrue(footor.Capacity() == 0, L"Vector Capacity should be zero on Clear");
			
			footor.Reserve(100);
			Assert::IsTrue(footor.Capacity() == 100, L"Vector Capacity not reserving specified value");
			Assert::IsTrue(footor.Size() == 0, L"Reserve changing vector Size erroneously");
			
			footor.Reserve(10);
			Assert::IsTrue(footor.Capacity() == 10, L"Capacity not changing on Reserve when shrinking");
			
			Foo foo(1);
			for (int i = 0; i < 10; i++)
			{
				footor.PushBack(foo);
			}
			Assert::IsTrue(footor.Capacity() == 10, L"Reserving smaller than current Size should shrink to fit");
		}

		TEST_METHOD(TestClear)
		{
			/// Int vector tests
			intor.PushBack(1);
			Assert::IsTrue(intor.Size() == 1, L"Size incorrect after pushing first value");
			
			intor.Clear();
			Assert::IsTrue(intor.Size() == 0, L"Size not zero after Clear");
			Assert::IsTrue(intor.Capacity() == 0, L"Capacity not zero after Clear");


			/// Pointer vector tests
			int x = 1;
			pointor.PushBack(&x);
			Assert::IsTrue(pointor.Size() == 1, L"Size incorrect after pushing first value");
			
			pointor.Clear();
			Assert::IsTrue(pointor.Size() == 0, L"Size not zero after Clear");
			Assert::IsTrue(pointor.Capacity() == 0, L"Capacity not zero after Clear");


			/// Foo vector tests
			Foo foo(1);
			footor.PushBack(foo);
			Assert::IsTrue(footor.Size() == 1, L"Size incorrect after pushing first value");
			
			footor.Clear();
			Assert::IsTrue(footor.Size() == 0, L"Size not zero after Clear");
			Assert::IsTrue(footor.Capacity() == 0, L"Capacity not zero after Clear");
		}

		TEST_METHOD(TestRemove)
		{
			/// Int vector tests
			intor.PushBack(1);
			intor.Remove(1);
			Assert::IsTrue(intor.Size() == 0, L"Size not reducing after removing a value");
			
			intor.PushBack(2);
			intor.Remove(1);
			Assert::IsTrue(intor.Size() == 1, L"Size changing after removing a nonexistent value");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			pointor.PushBack(&x);
			pointor.Remove(&x);
			Assert::IsTrue(pointor.Size() == 0, L"Size not reducing after removing a value");

			pointor.PushBack(&y);
			pointor.Remove(&x);
			Assert::IsTrue(pointor.Size() == 1, L"Size changing after removing a nonexistent value");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			footor.PushBack(foo);
			footor.Remove(foo);
			Assert::IsTrue(footor.Size() == 0, L"Size not reducing after removing a value");

			footor.PushBack(bar);
			footor.Remove(foo);
			Assert::IsTrue(footor.Size() == 1, L"Size changing after removing a nonexistent value");
		}

		TEST_METHOD(TestShrinkToFit)
		{
			/// Int vector tests
			intor.PushBack(1);
			intor.PushBack(2);
			intor.PushBack(3);
			Assert::IsTrue(intor.Capacity() == 10, L"Default Capacity for vector should be 10");
			
			intor.ShrinkToFit();
			Assert::IsTrue(intor.Capacity() == 3, L"Capacity should be 3 after shrinking to fit");
			
			intor.Clear();
			intor.ShrinkToFit();
			Assert::IsTrue(intor.Capacity() == 0, L"Capacity should be 0 after shrinking to fit on empty vector");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			int z = 3;
			pointor.PushBack(&x);
			pointor.PushBack(&y);
			pointor.PushBack(&z);
			Assert::IsTrue(pointor.Capacity() == 10, L"Default Capacity for vector should be 10");
			
			pointor.ShrinkToFit();
			Assert::IsTrue(pointor.Capacity() == 3, L"Capacity should be 3 after shrinking to fit");
			
			pointor.Clear();
			pointor.ShrinkToFit();
			Assert::IsTrue(pointor.Capacity() == 0, L"Capacity should be 3 after shrinking to fit on empty vector");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			footor.PushBack(foo);
			footor.PushBack(bar);
			footor.PushBack(gar);
			Assert::IsTrue(footor.Capacity() == 10, L"Default Capacity for vector should be 10");
			
			footor.ShrinkToFit();
			Assert::IsTrue(footor.Capacity() == 3, L"Capacity should be 3 after shrinking to fit");
			
			footor.Clear();
			footor.ShrinkToFit();
			Assert::IsTrue(footor.Capacity() == 0, L"Capacity should be 3 after shrinking to fit on empty vector");
		}

		TEST_METHOD(TestIteratorComparisonOperator)
		{
			/// int vector tests
			auto iter = intor.begin();
			const auto iterCopy(iter);
			Assert::IsTrue(iter == intor.begin(), L"Iterator should be equivalent to the value it was assigned to");
			Assert::IsTrue(iter == intor.end(), L"Iterator should be equivalent to end when assigned to begin on an empty vector");
			Assert::IsTrue(iterCopy == intor.begin());
			Assert::IsTrue(iterCopy == intor.end());
			
			intor.PushBack(1);
			iter = intor.begin();
			const auto secondIterCopy(iter);
			Assert::IsFalse(iter == intor.end(), L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Assert::IsFalse(secondIterCopy == intor.end());

			Library::Vector<int> newintvector;
			auto newiter = newintvector.begin();
			const auto newIterCopy(newiter);
			Assert::IsFalse(iter == newiter, L"Iterators with different owners should not be equivalent");
			Assert::IsTrue(newIterCopy == newiter);


			/// pointer vector tests
			auto piter = pointor.begin();
			const auto piterCopy(piter);
			Assert::IsTrue(piter == pointor.begin(), L"Iterator should be equivalent to the value it was assigned to");
			Assert::IsTrue(piter == pointor.end(), L"Iterator should be equivalent to end when assigned to begin on an empty vector");
			Assert::IsTrue(piterCopy == pointor.begin());
			Assert::IsTrue(piterCopy == pointor.end());

			int x = 1;
			pointor.PushBack(&x);
			piter = pointor.begin();
			const auto piterSecondCopy(piter);
			Assert::IsFalse(piter == pointor.end(), L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Assert::IsFalse(piterSecondCopy == pointor.end());

			Library::Vector<int*> newptrvector;
			auto newpiter = newptrvector.begin();
			const auto newpiterCopy(newpiter);
			Assert::IsFalse(piter == newpiter, L"Iterators with different owners should not be equivalent");
			Assert::IsTrue(newpiterCopy == newpiter);


			/// foo vector tests
			auto fooiter = footor.begin();
			const auto fooiterCopy(fooiter);
			Assert::IsTrue(fooiter == footor.begin(), L"Iterator should be equivalent to the value it was assigned to");
			Assert::IsTrue(fooiter == footor.end(), L"Iterator should be equivalent to end when assigned to begin on an empty vector");
			Assert::IsTrue(fooiterCopy == footor.begin());
			Assert::IsTrue(fooiterCopy == footor.end());

			Foo foo(1);
			footor.PushBack(foo);
			fooiter = footor.begin();
			const auto fooiterSecondCopy(fooiter);
			Assert::IsFalse(fooiter == footor.end(), L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Assert::IsFalse(fooiterSecondCopy == footor.end());

			Library::Vector<Foo> newfoovector;
			auto newfooiter = newfoovector.begin();
			const auto newfooiterCopy(newfooiter);
			Assert::IsFalse(fooiter == newfooiter, L"Iterators with different owners should not be equivalent");
			Assert::IsTrue(newfooiterCopy == newfooiter);
		}

		TEST_METHOD(TestIteratorIncrement)
		{
			/// int vector tests
			intor.PushBack(1);
			auto iter = intor.begin();
			Assert::IsFalse(iter == intor.end(), L"Iterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++iter == intor.end(), L"Incrementing an iterator on a Size of one vector should be equivalent to end");
			

			/// pointer vector tests
			int x = 1;
			pointor.PushBack(&x);
			auto piter = pointor.begin();
			Assert::IsFalse(piter == pointor.end(), L"piterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++piter == pointor.end(), L"Incrementing an piterator on a Size of one vector should be equivalent to end");


			/// foo vector tests
			Foo foo(1);
			footor.PushBack(foo);
			auto fooiter = footor.begin();
			Assert::IsFalse(fooiter == footor.end(), L"fooiterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++fooiter == footor.end(), L"Incrementing an fooiterator on a Size of one vector should be equivalent to end");
		}

		TEST_METHOD(TestIteratorDereference)
		{
			/// Int vector tests
			auto iter = intor.begin();
			auto func1 = [&] { *iter; };
			Assert::ExpectException<std::exception>(func1, L"Dereferencing begin on an empty vector should throw an exception");
			
			intor.PushBack(1);
			iter = intor.begin();
			Assert::IsTrue(*iter == 1, L"Dereferencing an iterator At begin should be equivalent to the first value pushed");
			
			const auto constIntVector(intor);
			Assert::IsTrue(*constIntVector.begin() == *intor.begin(), L"Const copy begin not equivalent to original");

			++iter;
			Assert::ExpectException<std::exception>(func1, L"Dereferencing end of a vector should throw an exception");


			/// Pointer vector tests
			auto piter = pointor.begin();
			auto func2 = [&] { *piter; };
			Assert::ExpectException<std::exception>(func2, L"Dereferencing begin on an empty vector should throw an exception");
			
			int x = 1;
			pointor.PushBack(&x);
			piter = pointor.begin();
			Assert::IsTrue(*piter == &x, L"Dereferencing an piterator At begin should be equivalent to the first value pushed");

			const auto constPtrVector(pointor);
			Assert::IsTrue(*constPtrVector.begin() == *pointor.begin(), L"Const copy begin not equivalent to original");
			
			++piter;
			Assert::ExpectException<std::exception>(func2, L"Dereferencing end of a vector should throw an exception");


			/// Foo vector tests
			auto fooiter = footor.begin();
			auto func3 = [&] { *fooiter; };
			Assert::ExpectException<std::exception>(func3, L"Dereferencing begin on an empty vector should throw an exception");
			
			Foo foo(1);
			footor.PushBack(foo);
			fooiter = footor.begin();
			Assert::IsTrue(*fooiter == foo, L"Dereferencing an fooiterator At begin should be equivalent to the first value pushed");
			
			const auto constFooVector(footor);
			Assert::IsTrue(*constFooVector.begin() == *footor.begin(), L"Const copy begin not equivalent to original");

			++fooiter;
			Assert::ExpectException<std::exception>(func3, L"Dereferencing end of a vector should throw an exception");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}