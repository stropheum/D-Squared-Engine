 #include "pch.h"
#include "CppUnitTest.h"
#include <Vector.h>
#include "Foo.h"
#include "implementation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(VectorTest)
	{
	public:
		Vector::Vector<int>  intor;
		Vector::Vector<int*> pointor;
		Vector::Vector<Foo>  footor;

		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _Debug
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
		}

		/// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#if _Debug
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
			intor.clear();
			pointor.clear();
			footor.clear();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			finalizeLeakDetection();
		}

		TEST_METHOD(TestCopyConstructor)
		{
			/// Int vector tests
			Vector::Vector<int> copyIntor(intor);
			bool intcompare = intor == copyIntor;
			Assert::IsTrue(intcompare, L"Copied vector not equivalent to original");
			
			intor.pushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsFalse(intcompare, L"Copied vector equivalent after modifying original");
			
			copyIntor.pushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsTrue(intcompare, L"Copied vector not equivalent after pushing identical values");

			Vector::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, L"Copied pointer vector not equivalent to original");
			

			/// Pointer vector tests
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsFalse(pointor == copyPointor, L"Copied vector equivalent after modifying original");
			
			copyPointor.pushBack(&x);
			Assert::IsTrue(pointor == copyPointor, L"Copied vector not equivalent after pushing identical values");

			Vector::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor, L"Copied Foo vector not equivalent to original");
			

			/// Foo vector tests
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsFalse(footor == copyFootor, L"Copied Foo vector equivalent after modifying original");
			
			copyFootor.pushBack(foo);
			Assert::IsTrue(footor == copyFootor, L"Copied vector not equivalent after pushing identical values");
		}

		TEST_METHOD(TestComparisonOperator)
		{
			/// Int vector tests
			Assert::IsTrue(intor == intor, L"Vector not equivalent to itself");
			
			Vector::Vector<int> copyIntor(intor);
			Assert::IsTrue(intor == copyIntor, L"Copy constructor invocation not equivalent");
			
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, L"Assignment operator copy not equivalent");

			const auto constIntor(intor);
			Assert::IsTrue(intor == constIntor, L"Const copy not equivalent");
			

			/// Pointer vector tests
			Assert::IsTrue(pointor == pointor, L"Vector not equivalent to itself");

			Vector::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, L"Copy constructor invocation not equivalent");
			
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, L"Assignment operator copy not equivalent");
			
			const auto constPointor(pointor);
			Assert::IsTrue(pointor == constPointor, L"Const copy not equivalent");


			/// Foo vector tests
			Assert::IsTrue(footor == footor, L"Vector not equivalent to itself");

			Vector::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor, L"Copy constructor invocation not equivalent");
			
			copyFootor = footor;
			Assert::IsTrue(footor == copyFootor, L"Assignment operator copy not equivalent");

			const auto constFootor(footor);
			Assert::IsTrue(footor == constFootor, L"Const copy not equivalent");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			/// Int vector tests
			Vector::Vector<int> copyIntor;
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, L"Copied vector not equivalent to original");


			/// Pointer vector tests
			Vector::Vector<int*> copyPointor;
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, L"Copied pointer vector not equivalent to original");


			/// Foo vector tests
			Vector::Vector<Foo> copyFootor;
			copyFootor = footor;
			Assert::IsTrue(footor == copyFootor, L"Copied Foo vector not equivalent to original");
		}

		TEST_METHOD(TestFind)
		{
			/// Int vector tests
			auto iter = intor.find(0);
			Assert::IsTrue(iter == intor.end(), L"Begin and end not equivalent on empty vector");
			Assert::IsTrue(iter == intor.begin(), L"Find on first element not equivalent to Vector.begin()");
			
			intor.pushBack(1);
			iter = intor.find(1);
			Assert::IsFalse(iter == intor.end(), L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(iter == intor.begin(), L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*iter, 1, L"Find on first item should be equivalent to the first value pushed");
			
			intor.pushBack(100);
			iter = intor.find(1);
			Assert::IsTrue(iter == intor.begin(), L"Find on first item should not change after pushing a second");
			Assert::IsFalse(iter == intor.end(), L"Find on existing item should not be equivalent to end");
			
			iter = intor.find(100);
			Assert::IsTrue(++iter == intor.end(), L"Incrementing past final element not equivalent to end");

			const auto constIntor(intor);
			Assert::IsTrue(constIntor.find(1) == constIntor.begin(), L"Const find value incorrect");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			auto piter = pointor.find(&x);
			Assert::IsTrue(piter == pointor.end(), L"Begin and end not equivalent on empty vector");
			Assert::IsTrue(piter == pointor.begin(), L"Find on first element not equivalent to Vector.begin()");
			
			pointor.pushBack(&x);
			piter = pointor.find(&x);
			Assert::IsFalse(piter == pointor.end(), L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(piter == pointor.begin(), L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*piter, &x, L"Find on first item should be equivalent to the first value pushed");
			
			pointor.pushBack(&y);
			piter = pointor.find(&x);
			Assert::IsTrue(piter == pointor.begin(), L"Find on first item should not change after pushing a second");
			Assert::IsFalse(piter == pointor.end(), L"Find on existing item should not be equivalent to end");
			
			piter = pointor.find(&y);
			Assert::IsTrue(++piter == pointor.end(), L"Incrementing past final element not equivalent to end");

			const auto constPointor(pointor);
			Assert::IsTrue(constPointor.find(&x) == constPointor.begin(), L"Const find value incorrect");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			auto fooiter = footor.find(foo);
			Assert::IsTrue(fooiter == footor.end(), L"Begin and end not equivalent on empty vector");
			Assert::IsTrue(fooiter == footor.begin(), L"Find on first element not equivalent to Vector.begin()");
			
			footor.pushBack(foo);
			fooiter = footor.find(foo);
			Assert::IsFalse(fooiter == footor.end(), L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(fooiter == footor.begin(), L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*fooiter, foo, L"Find on first item should be equivalent to the first value pushed");
			
			footor.pushBack(bar);
			fooiter = footor.find(foo);
			Assert::IsTrue(fooiter == footor.begin(), L"Find on first item should not change after pushing a second");
			Assert::IsFalse(fooiter == footor.end(), L"Find on existing item should not be equivalent to end");
			
			fooiter = footor.find(bar);
			Assert::IsTrue(++fooiter == footor.end(), L"Incrementing past final element not equivalent to end");

			const auto constFootor(footor);
			Assert::IsTrue(constFootor.find(foo) == constFootor.begin(), L"Const find value incorrect");
		}

		TEST_METHOD(TestBegin)
		{
			/// Int vector tests
			Assert::IsTrue(intor.begin() == intor.end(), L"Begin should be equivalent to end on an empy vector");
			
			intor.pushBack(1);
			Assert::IsTrue(1 == *intor.begin(), L"Begin not equivalent with first value pushed");
			Assert::IsFalse(intor.begin() == intor.end());
			
			intor.pushBack(2);
			Assert::IsTrue(1 == *intor.begin(), L"Begin value changed after calling push back on non-empty vector");
			Assert::IsTrue(intor[0] == *intor.begin(), L"First index not equivalent to begin");

			const auto constIntor(intor);
			Assert::IsTrue(*constIntor.begin() == constIntor[0]);


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			Assert::IsTrue(pointor.begin() == pointor.end(), L"Begin should be equivalent to end on an empy vector");
			
			pointor.pushBack(&x);
			Assert::IsTrue(&x == *pointor.begin(), L"Begin not equivalent with first value pushed");
			Assert::IsFalse(pointor.begin() == pointor.end());
			
			pointor.pushBack(&y);
			Assert::IsTrue(&x == *pointor.begin(), L"Begin value changed after calling push back on non-empty vector");
			Assert::IsTrue(pointor[0] == *pointor.begin(), L"First index not equivalent to begin");

			const auto constPointor(pointor);
			Assert::IsTrue(*constPointor.begin() == constPointor[0]);


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			Assert::IsTrue(footor.begin() == footor.end(), L"Begin should be equivalent to end on an empy vector");
			
			footor.pushBack(foo);
			Assert::IsTrue(foo == *footor.begin(), L"Begin not equivalent with first value pushed");
			Assert::IsFalse(footor.begin() == footor.end());
			
			footor.pushBack(bar);
			Assert::IsTrue(foo == *footor.begin(), L"Begin value changed after calling push back on non-empty vector");
			Assert::IsTrue(footor[0] == *footor.begin(), L"First index not equivalent to begin");

			const auto constFootor(footor);
			Assert::IsTrue(*constFootor.begin() == constFootor[0]);
		}

		TEST_METHOD(TestEnd)
		{
			/// Int vector tests
			Assert::IsTrue(intor.begin() == intor.end(), L"End should be equivalent to begin on an empty vector");
			
			Vector::Vector<int>::Iterator iter = intor.end();
			Assert::IsTrue(iter == intor.end(), L"Iterator assigned to end should be equivalent to end");
			
			intor.pushBack(1);
			iter = intor.begin();
			Assert::IsFalse(iter == intor.end(), L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++iter == intor.end(), L"Iterator pointing to last element should be equivalent to end after incrementing");

			Assert::IsTrue(pointor.begin() == pointor.end(), L"End should be equivalent to begin on an empty vector");
			
			Vector::Vector<int*>::Iterator piter = pointor.end();
			Assert::IsTrue(piter == pointor.end(), L"Iterator assigned to end should be equivalent to end");

			const auto constIntor(intor);
			auto constIter = constIntor.end();
			Assert::IsTrue(constIter == constIntor.end());
			

			/// Pointer vector tests
			int x = 1;
			pointor.pushBack(&x);
			piter = pointor.begin();
			Assert::IsFalse(piter == pointor.end(), L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++piter == pointor.end(), L"Iterator pointing to last element should be equivalent to end after incrementing");

			Assert::IsTrue(footor.begin() == footor.end(), L"End should be equivalent to begin on an empty vector");
			
			Vector::Vector<Foo>::Iterator fooiter = footor.end();
			Assert::IsTrue(fooiter == footor.end(), L"Iterator assigned to end should be equivalent to end");
			
			const auto constPointor(pointor);
			auto constPIter = constPointor.end();
			Assert::IsTrue(constPIter == constPointor.end());


			/// Foo vector tests
			Foo foo(1);
			footor.pushBack(foo);
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
			auto func = [this] { intor.front(); };
			Assert::ExpectException<std::exception>(func, L"Front should be equivalent with begin on an empty vector");
			
			intor.pushBack(1);
			Assert::IsTrue(intor.front() == intor[0], L"Front should be equivalent with first index");
			Assert::IsTrue(intor.front() == *intor.begin(), L"Front should be equivalent with begin");
			
			intor.front() = 5;
			Assert::IsTrue(intor.front() == 5, L"Unable to modify Vector.front()");

			const Vector::Vector<int> constIntVector(intor);
//			auto val = constIntVector.front();
			Assert::IsTrue(constIntVector.front() == intor.front(), L"Front of const copied vector should be equivalent to original");

			/// Pointer vector tests
			auto ptrfunc = [this] { pointor.front(); };
			Assert::ExpectException<std::exception>(ptrfunc, L"Front should be equivalent with begin on an empty vector");
			
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.front() == pointor[0], L"Front should be equivalent with first index");
			Assert::IsTrue(pointor.front() == *pointor.begin(), L"Front should be equivalent with begin");
			
			int y = 5;
			pointor.front() = &y;
			Assert::IsTrue(pointor.front() == &y, L"Unable to modify Vector.front()");

			const Vector::Vector<int*> constPtrVector(pointor);
			Assert::IsTrue(constPtrVector.front() == pointor.front(), L"Front of const copied vector should be equivalent to original");

			/// Foo vector tests
			auto foofunc = [this] { footor.front(); };
			Assert::ExpectException<std::exception>(foofunc, L"Front should be equivalent with begin on an empty vector");
			
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.front() == footor[0], L"Front should be equivalent with first index");
			Assert::IsTrue(footor.front() == *footor.begin(), L"Front should be equivalent with begin");
			
			Foo bar(5);
			footor.front() = bar;
			Assert::IsTrue(footor.front() == bar, L"Unable to modify Vector.front()");

			const Vector::Vector<Foo> constFooVector(footor);
			Assert::IsTrue(constFooVector.front() == footor.front(), L"Front of constant copied vector not equal to original vector's front");
			Assert::IsTrue(true);
		}

		TEST_METHOD(TestBack)
		{
			/// Int vector tests
			auto func = [this] { intor.back(); };
			Assert::ExpectException<std::exception>(func, L"Calling back on an empty vector should throw an exception");
			
			intor.pushBack(1);
			Assert::IsTrue(intor.back() == intor[0], L"Back should be equivalent to first value pushed onto an empty vector");
			
			intor.pushBack(2);
			Assert::IsTrue(intor.back() == intor[1], L"Back should b equivalent to last value pushed onto a vector");
			
			intor.back() = 10;
			Assert::IsTrue(intor.back() == 10, L"Vector.back() not modifiable");


			/// Pointer vector tests
			auto ptrfunc = [this] { pointor.back(); };
			Assert::ExpectException<std::exception>(ptrfunc, L"Calling back on an empty vector should throw an exception");
			
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.back() == pointor[0], L"Back should be equivalent to first value pushed onto an empty vector");
			
			int y = 2;
			pointor.pushBack(&y);
			Assert::IsTrue(pointor.back() == pointor[1], L"Back should b equivalent to last value pushed onto a vector");
			
			int z = 10;
			pointor.back() = &z;
			Assert::IsTrue(pointor.back() == &z, L"Vector.back() not modifiable");


			/// Foo vector tests
			auto foofunc = [this] { footor.back(); };
			Assert::ExpectException<std::exception>(foofunc, L"Calling back on an empty vector should throw an exception");
			
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.back() == footor[0], L"Back should be equivalent to first value pushed onto an empty vector");
			
			Foo bar(2);
			footor.pushBack(bar);
			Assert::IsTrue(footor.back() == footor[1], L"Back should b equivalent to last value pushed onto a vector");
			
			Foo gar(10);
			footor.back() = gar;
			Assert::IsTrue(footor.back() == gar, L"Vector.back() not modifiable");
		}

		TEST_METHOD(TestAt)
		{
			/// Int vector tests
			auto func1 = [this] { intor.at(0); };
			Assert::ExpectException<std::exception>(func1, L"Accessing index of an empty vector should throw an exception");
			
			intor.pushBack(1);
			auto func2 = [this] { intor.at(1); };
			Assert::ExpectException<std::exception>(func2, L"Accessing out of vector bounds should throw an exception");

			auto func3 = [this] { intor.at(-1); };
			Assert::ExpectException<std::exception>(func3, L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(1u == intor.at(0), L"First element added should be equivalent to Vector.at(0)");
			
			intor.pushBack(2);
			Assert::IsTrue(1 == intor.at(0), L"First element should be equivalent to Vector.at(0) after pushing back multiple values");
			Assert::IsTrue(2 == intor.at(1), L"Last element should be equivalent to Vector.at(n-1)");

			const auto constIntor(intor);
			Assert::IsTrue(1 == constIntor.at(0));
			Assert::IsTrue(2 == constIntor.at(1));


			/// Pointer vector tests
			auto ptrfunc1 = [this] { pointor.at(0); };
			Assert::ExpectException<std::exception>(ptrfunc1, L"Accessing index of an empty vector should throw an exception");
			
			int x = 1;
			pointor.pushBack(&x);
			auto ptrfunc2 = [this] { pointor.at(1); };
			Assert::ExpectException<std::exception>(ptrfunc2, L"Accessing out of vector bounds should throw an exception");
			
			auto ptrfunc3 = [this] { pointor.at(-1); };
			Assert::ExpectException<std::exception>(ptrfunc3, L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(&x == pointor.at(0), L"First element added should be equivalent to Vector.at(0)");
			
			int y = 2;
			pointor.pushBack(&y);
			Assert::IsTrue(&x == pointor.at(0), L"First element should be equivalent to Vector.at(0) after pushing back multiple values");
			Assert::IsTrue(&y == pointor.at(1), L"Last element should be equivalent to Vector.at(n-1)");

			const auto constPointor(pointor);
			Assert::IsTrue(&x == constPointor.at(0));
			Assert::IsTrue(&y == constPointor.at(1));

			/// Foo vector tests
			auto foofunc1 = [this] { footor.at(0); };
			Assert::ExpectException<std::exception>(foofunc1, L"Accessing index of an empty vector should throw an exception");
			
			Foo foo(1);
			footor.pushBack(foo);
			auto foofunc2 = [this] { footor.at(1); };
			Assert::ExpectException<std::exception>(foofunc2, L"Accessing out of vector bounds should throw an exception");
			
			auto foofunc3 = [this] { footor.at(-1); };
			Assert::ExpectException<std::exception>(foofunc3, L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(foo == footor.at(0), L"First element added should be equivalent to Vector.at(0)");
			
			Foo bar(2);
			footor.pushBack(bar);
			Assert::IsTrue(foo == footor.at(0), L"First element should be equivalent to Vector.at(0) after pushing back multiple values");
			Assert::IsTrue(bar == footor.at(1), L"Last element should be equivalent to Vector.at(n-1)");

			const auto constFootor(footor);
			Assert::IsTrue(foo == constFootor.at(0));
			Assert::IsTrue(bar == constFootor.at(1));
		}

		TEST_METHOD(TestIndexOperator)
		{
			/// Int vector tests
			auto func1 = [this] { intor[0]; };
			Assert::ExpectException<std::exception>(func1, L"Accessing index of an empty vector should throw an exception");
			
			intor.pushBack(1);
			auto func2 = [this] { intor[1]; };
			Assert::ExpectException<std::exception>(func2, L"Accessing out of vector bounds should throw an exception");
			
			auto func3 = [this] { intor[-1]; };
			Assert::ExpectException<std::exception>(func3, L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(1 == intor[0], L"First element added should be equivalent to Vector[0]");
			
			intor.pushBack(2);
			Assert::IsTrue(1 == intor[0], L"First element should be equivalent to Vector[0] after pushing back multiple values");
			Assert::IsTrue(2 == intor[1], L"Last element should be equivalent to Vector[n-1]");

			const auto constIntor(intor);
			Assert::IsTrue(1 == constIntor[0]);
			Assert::IsTrue(2 == constIntor[1]);


			/// Pointer vector tests
			auto ptrfunc1 = [this] { pointor[0]; };
			Assert::ExpectException<std::exception>(ptrfunc1, L"Accessing index of an empty vector should throw an exception");
			
			int x = 1;
			pointor.pushBack(&x);
			auto ptrfunc2 = [this] { pointor[1]; };
			Assert::ExpectException<std::exception>(ptrfunc2, L"Accessing out of vector bounds should throw an exception");
			
			auto ptrfunc3 = [this] { pointor[-1]; };
			Assert::ExpectException<std::exception>(ptrfunc3, L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(&x == pointor[0], L"First element added should be equivalent to Vector[0]");
			
			int y = 2;
			pointor.pushBack(&y);
			Assert::IsTrue(&x == pointor[0], L"First element should be equivalent to Vector[0] after pushing back multiple values");
			Assert::IsTrue(&y == pointor[1], L"Last element should be equivalent to Vector[n-1]");

			const auto constPointor(pointor);
			Assert::IsTrue(&x == constPointor[0]);
			Assert::IsTrue(&y == constPointor[1]);


			/// Foo vector tests
			auto foofunc1 = [this] { footor[0U]; };
			Assert::ExpectException<std::exception>(foofunc1, L"Accessing index of an empty vector should throw an exception");
			
			Foo foo(1);
			footor.pushBack(foo);
			auto foofunc2 = [this] { footor[1U]; };
			Assert::ExpectException<std::exception>(foofunc2, L"Accessing out of vector bounds should throw an exception");
			
			auto foofunc3 = [this] { footor[-1]; };
			Assert::ExpectException<std::exception>(foofunc3, L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(foo == footor[0], L"First element added should be equivalent to Vector[0]");
			
			Foo bar(2);
			footor.pushBack(bar);
			Assert::IsTrue(foo == footor[0], L"First element should be equivalent to Vector[0] after pushing back multiple values");
			Assert::IsTrue(bar == footor[1], L"Last element should be equivalent to Vector[n-1]");

			const auto constFootor(footor);
			Assert::IsTrue(foo == constFootor[0]);
			Assert::IsTrue(bar == constFootor[1]);
		}

		TEST_METHOD(TestPopBack)
		{
			/// Int vector tests
			auto func1 = [this] { intor.popBack(); };
			Assert::ExpectException<std::exception>(func1, L"PopBack on empty vector should throw an exception");
			
			intor.pushBack(1);
			intor.pushBack(2);
			intor.pushBack(3);
			intor.popBack();
			Assert::AreEqual(2U, intor.size(), L"Vector size not reducing after valid pop back");


			/// Pointer vector tests
			auto ptrfunc1 = [this] { pointor.popBack(); };
			Assert::ExpectException<std::exception>(ptrfunc1, L"PopBack on empty vector should throw an exception");
			
			int x = 1;
			int y = 2;
			int z = 3;
			pointor.pushBack(&x);
			pointor.pushBack(&y);
			pointor.pushBack(&z);
			pointor.popBack();
			Assert::AreEqual(2U, pointor.size(), L"Vector size not reducing after valid pop back");


			/// Foo vector tests
			auto foofunc1 = [this] { footor.popBack(); };
			Assert::ExpectException<std::exception>(foofunc1, L"PopBack on empty vector should throw an exception");
			
			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			footor.pushBack(foo);
			footor.pushBack(bar);
			footor.pushBack(gar);
			footor.popBack();
			Assert::AreEqual(2U, footor.size(), L"Vector size not reducing after valid pop back");
		}

		TEST_METHOD(TestSize)
		{
			/// Int vector tests
			Assert::IsTrue(intor.size() == 0, L"Size not zero on empty vector");
			
			intor.pushBack(1);
			Assert::IsTrue(intor.size() == 1, L"Size not one after pushing one value");
			
			intor.popBack();
			Assert::IsTrue(intor.size() == 0, L"Size not zero after popping last value");
			
			const auto constIntor(intor);
			Assert::IsTrue(constIntor.size() == 0);


			/// Pointer vector tests
			Assert::IsTrue(pointor.size() == 0, L"Size not zero on empty vector");

			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.size() == 1, L"Size not one after pushing one value");
			
			pointor.popBack();
			Assert::IsTrue(pointor.size() == 0, L"Size not zero after popping last value");

			const auto constPointor(pointor);
			Assert::IsTrue(constPointor.size() == 0);


			/// Foo vector tests
			Assert::IsTrue(footor.size() == 0, L"Size not zero on empty vector");
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.size() == 1, L"Size not one after pushing one value");
			
			footor.popBack();
			Assert::IsTrue(footor.size() == 0, L"Size not zero after popping last value");

			const auto constFootor(footor);
			Assert::IsTrue(constFootor.size() == 0);
		}

		TEST_METHOD(TestCapacity)
		{
			/// Int vector tests
			Vector::Vector<int> newintvector;
			Assert::AreEqual(10U, newintvector.capacity(), L"New Vector should have a capacity of 10");
			
			const auto constIntor(newintvector);
			Assert::AreEqual(10U, constIntor.capacity());

			for (int i = 0; i < 10; i++)
			{
				intor.pushBack(i);
				Assert::AreEqual(10U, intor.capacity(), L"First ten pushes on a vector should retain the capacity at 10");
			}
			
			intor.pushBack(99);
			Assert::AreEqual(20U, intor.capacity(), L"on 11th push, vector capacity should be 20");
			
			for (int i = 0; i < 11; i++)
			{
				intor.popBack();
				Assert::AreEqual(10U, newintvector.capacity(), L"New Vector should have capacity of 10");
			}
			

			/// Pointer vector tests
			Vector::Vector<int> newptrvector;
			Assert::AreEqual(10U, newptrvector.capacity(), L"New Vector should have a capacity of 10");
			
			const auto constPointor(newptrvector);
			Assert::AreEqual(10U, constPointor.capacity());

			int x[11];
			for (int i = 0; i < 10; i++)
			{
				x[i] = i;
				pointor.pushBack(&x[i]);
				Assert::AreEqual(10U, pointor.capacity(), L"First ten pushes on a vector should retain the capacity at 10");
			}
			
			x[10] = 99;
			pointor.pushBack(&x[10]);
			Assert::AreEqual(20U, pointor.capacity(), L"on 11th push, vector capacity should be 20");

			for (int i = 0; i < 11; i++)
			{
				pointor.popBack();
				Assert::AreEqual(10U, newptrvector.capacity(), L"New Vector should have capacity of 10");
			}


			/// Foo vector tests
			Vector::Vector<int> newfoovector;
			Assert::AreEqual(10U, newfoovector.capacity(), L"New Vector should have a capacity of 10");
			
			const auto constFootor(newfoovector);
			Assert::AreEqual(10U, constFootor.capacity());

			Foo foo[11];
			for (int i = 0; i < 10; i++)
			{
				foo[i] = Foo(i);
				footor.pushBack(foo[i]);
				Assert::AreEqual(10U, footor.capacity(), L"First ten pushes on a vector should retain the capacity at 10");
			}
			
			foo[10] = Foo(99);
			footor.pushBack(foo[10]);
			Assert::AreEqual(20U, footor.capacity(), L"on 11th push, vector capacity should be 20");
			
			for (int i = 0; i < 11; i++)
			{
				footor.popBack();
				Assert::AreEqual(10U, newfoovector.capacity(), L"New Vector should have capacity of 10");
			}
		}

		TEST_METHOD(TestIsEmpty)
		{
			/// Int vector tests
			const auto constIntor1(intor);
			Assert::IsTrue(intor.isEmpty(), L"Cleared vector should be empty");
			Assert::IsTrue(constIntor1.isEmpty());
			
			intor.pushBack(1);
			const auto constIntor2(intor);
			Assert::IsFalse(intor.isEmpty(), L"Non-empty vector should not be empty");
			Assert::IsFalse(constIntor2.isEmpty());
			
			intor.popBack();
			const auto constIntor3(intor);
			Assert::IsTrue(intor.isEmpty(), L"Vector should be empty after popping last value");
			Assert::IsTrue(constIntor3.isEmpty());


			/// Pointer vector tests
			const auto constPointor1(pointor);
			Assert::IsTrue(pointor.isEmpty(), L"Cleared vector should be empty");
			Assert::IsTrue(constPointor1.isEmpty());
			
			int x = 1;
			pointor.pushBack(&x);
			const auto constPointor2(pointor);
			Assert::IsFalse(pointor.isEmpty(), L"Non-empty vector should not be empty");
			Assert::IsFalse(constPointor2.isEmpty());
			
			pointor.popBack();
			const auto constPointor3(pointor);
			Assert::IsTrue(pointor.isEmpty(), L"Vector should be empty after popping last value");
			Assert::IsTrue(constPointor3.isEmpty());


			/// Foo vector tests
			const auto constFootor1(footor);
			Assert::IsTrue(footor.isEmpty(), L"Cleared vector should be empty");
			Assert::IsTrue(constFootor1.isEmpty());
			
			Foo foo(1);
			footor.pushBack(foo);
			const auto constFootor2(footor);
			Assert::IsFalse(footor.isEmpty(), L"Non-empty vector should not be empty");
			Assert::IsFalse(constFootor2.isEmpty());
			
			footor.popBack();
			const auto constFootor3(footor);
			Assert::IsTrue(footor.isEmpty(), L"Vector should be empty after popping last value");
			Assert::IsTrue(constFootor3.isEmpty());
		}

		TEST_METHOD(TestPushBack)
		{
			/// Int vector tests
			intor.pushBack(1);
			Assert::IsTrue(intor.back() == 1, L"Value pushed to back does not match");
			Assert::IsTrue(*intor.begin() == 1, L"First value pushed back is not equivalent to begin");
			
			intor.pushBack(2);
			Assert::IsTrue(intor.back() == 2, L"Second value pushed back is not equivalent to begin");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.back() == &x, L"Value pushed to back does not match");
			Assert::IsTrue(*pointor.begin() == &x, L"First value pushed back is not equivalent to begin");
			
			pointor.pushBack(&y);
			Assert::IsTrue(pointor.back() == &y, L"Second value pushed back is not equivalent to begin");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			footor.pushBack(foo);
			Assert::IsTrue(footor.back() == foo, L"Value pushed to back does not match");
			Assert::IsTrue(*footor.begin() == foo, L"First value pushed back is not equivalent to begin");
			
			footor.pushBack(bar);
			Assert::IsTrue(footor.back() == bar, L"Second value pushed back is not equivalent to begin");
		}

		TEST_METHOD(TestReserve)
		{
			/// Int vector tests
			Assert::IsTrue(intor.capacity() == 0, L"Vector capacity should be zero on clear");
			
			intor.reserve(100);
			Assert::IsTrue(intor.capacity() == 100, L"Vector capacity not reserving specified value");
			Assert::IsTrue(intor.size() == 0, L"Reserve changing vector size erroneously");
			
			intor.reserve(10);
			Assert::IsTrue(intor.capacity() == 10, L"Capacity not changing on reserve when shrinking");
			
			for (int i = 0; i < 10; i++)
			{
				intor.pushBack(i);
			}
			intor.reserve(5);
			Assert::IsTrue(intor.capacity() == 10, L"Reserving smaller than current size should shrink to fit");


			/// Pointer vector tests
			Assert::IsTrue(pointor.capacity() == 0, L"Vector capacity should be zero on clear");
			
			pointor.reserve(100);
			Assert::IsTrue(pointor.capacity() == 100, L"Vector capacity not reserving specified value");
			Assert::IsTrue(pointor.size() == 0, L"Reserve changing vector size erroneously");
			
			pointor.reserve(10);
			Assert::IsTrue(pointor.capacity() == 10, L"Capacity not changing on reserve when shrinking");
			
			int x[10];
			for (int i = 0; i < 10; i++)
			{
				x[i] = i;
				pointor.pushBack(&x[i]);
			}
			Assert::IsTrue(intor.capacity() == 10, L"Reserving smaller than current size should shrink to fit");


			/// Foo vector tests
			Assert::IsTrue(footor.capacity() == 0, L"Vector capacity should be zero on clear");
			
			footor.reserve(100);
			Assert::IsTrue(footor.capacity() == 100, L"Vector capacity not reserving specified value");
			Assert::IsTrue(footor.size() == 0, L"Reserve changing vector size erroneously");
			
			footor.reserve(10);
			Assert::IsTrue(footor.capacity() == 10, L"Capacity not changing on reserve when shrinking");
			
			Foo foo(1);
			for (int i = 0; i < 10; i++)
			{
				footor.pushBack(foo);
			}
			Assert::IsTrue(footor.capacity() == 10, L"Reserving smaller than current size should shrink to fit");
		}

		TEST_METHOD(TestClear)
		{
			/// Int vector tests
			intor.pushBack(1);
			Assert::IsTrue(intor.size() == 1, L"Size incorrect after pushing first value");
			
			intor.clear();
			Assert::IsTrue(intor.size() == 0, L"Size not zero after clear");
			Assert::IsTrue(intor.capacity() == 0, L"Capacity not zero after clear");


			/// Pointer vector tests
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.size() == 1, L"Size incorrect after pushing first value");
			
			pointor.clear();
			Assert::IsTrue(pointor.size() == 0, L"Size not zero after clear");
			Assert::IsTrue(pointor.capacity() == 0, L"Capacity not zero after clear");


			/// Foo vector tests
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.size() == 1, L"Size incorrect after pushing first value");
			
			footor.clear();
			Assert::IsTrue(footor.size() == 0, L"Size not zero after clear");
			Assert::IsTrue(footor.capacity() == 0, L"Capacity not zero after clear");
		}

		TEST_METHOD(TestRemove)
		{
			/// Int vector tests
			intor.pushBack(1);
			intor.remove(1);
			Assert::IsTrue(intor.size() == 0, L"Size not reducing after removing a value");
			
			intor.pushBack(2);
			intor.remove(1);
			Assert::IsTrue(intor.size() == 1, L"Size changing after removing a nonexistent value");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			pointor.pushBack(&x);
			pointor.remove(&x);
			Assert::IsTrue(pointor.size() == 0, L"Size not reducing after removing a value");

			pointor.pushBack(&y);
			pointor.remove(&x);
			Assert::IsTrue(pointor.size() == 1, L"Size changing after removing a nonexistent value");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			footor.pushBack(foo);
			footor.remove(foo);
			Assert::IsTrue(footor.size() == 0, L"Size not reducing after removing a value");

			footor.pushBack(bar);
			footor.remove(foo);
			Assert::IsTrue(footor.size() == 1, L"Size changing after removing a nonexistent value");
		}

		TEST_METHOD(TestShrinkToFit)
		{
			/// Int vector tests
			intor.pushBack(1);
			intor.pushBack(2);
			intor.pushBack(3);
			Assert::IsTrue(intor.capacity() == 10, L"Default capacity for vector should be 10");
			
			intor.shrinkToFit();
			Assert::IsTrue(intor.capacity() == 3, L"Capacity should be 3 after shrinking to fit");
			
			intor.clear();
			intor.shrinkToFit();
			Assert::IsTrue(intor.capacity() == 0, L"Capacity should be 0 after shrinking to fit on empty vector");


			/// Pointer vector tests
			int x = 1;
			int y = 2;
			int z = 3;
			pointor.pushBack(&x);
			pointor.pushBack(&y);
			pointor.pushBack(&z);
			Assert::IsTrue(pointor.capacity() == 10, L"Default capacity for vector should be 10");
			
			pointor.shrinkToFit();
			Assert::IsTrue(pointor.capacity() == 3, L"Capacity should be 3 after shrinking to fit");
			
			pointor.clear();
			pointor.shrinkToFit();
			Assert::IsTrue(pointor.capacity() == 0, L"Capacity should be 3 after shrinking to fit on empty vector");


			/// Foo vector tests
			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			footor.pushBack(foo);
			footor.pushBack(bar);
			footor.pushBack(gar);
			Assert::IsTrue(footor.capacity() == 10, L"Default capacity for vector should be 10");
			
			footor.shrinkToFit();
			Assert::IsTrue(footor.capacity() == 3, L"Capacity should be 3 after shrinking to fit");
			
			footor.clear();
			footor.shrinkToFit();
			Assert::IsTrue(footor.capacity() == 0, L"Capacity should be 3 after shrinking to fit on empty vector");
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
			
			intor.pushBack(1);
			iter = intor.begin();
			const auto secondIterCopy(iter);
			Assert::IsFalse(iter == intor.end(), L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Assert::IsFalse(secondIterCopy == intor.end());

			Vector::Vector<int> newintvector;
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
			pointor.pushBack(&x);
			piter = pointor.begin();
			const auto piterSecondCopy(piter);
			Assert::IsFalse(piter == pointor.end(), L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Assert::IsFalse(piterSecondCopy == pointor.end());

			Vector::Vector<int*> newptrvector;
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
			footor.pushBack(foo);
			fooiter = footor.begin();
			const auto fooiterSecondCopy(fooiter);
			Assert::IsFalse(fooiter == footor.end(), L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Assert::IsFalse(fooiterSecondCopy == footor.end());

			Vector::Vector<Foo> newfoovector;
			auto newfooiter = newfoovector.begin();
			const auto newfooiterCopy(newfooiter);
			Assert::IsFalse(fooiter == newfooiter, L"Iterators with different owners should not be equivalent");
			Assert::IsTrue(newfooiterCopy == newfooiter);
		}

		TEST_METHOD(TestIteratorIncrement)
		{
			/// int vector tests
			intor.pushBack(1);
			auto iter = intor.begin();
			Assert::IsFalse(iter == intor.end(), L"Iterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++iter == intor.end(), L"Incrementing an iterator on a size of one vector should be equivalent to end");
			

			/// pointer vector tests
			int x = 1;
			pointor.pushBack(&x);
			auto piter = pointor.begin();
			Assert::IsFalse(piter == pointor.end(), L"piterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++piter == pointor.end(), L"Incrementing an piterator on a size of one vector should be equivalent to end");


			/// foo vector tests
			Foo foo(1);
			footor.pushBack(foo);
			auto fooiter = footor.begin();
			Assert::IsFalse(fooiter == footor.end(), L"fooiterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++fooiter == footor.end(), L"Incrementing an fooiterator on a size of one vector should be equivalent to end");
		}

		TEST_METHOD(TestIteratorDereference)
		{
			/// Int vector tests
			auto iter = intor.begin();
			auto func1 = [&] { *iter; };
			Assert::ExpectException<std::exception>(func1, L"Dereferencing begin on an empty vector should throw an exception");
			
			intor.pushBack(1);
			iter = intor.begin();
			Assert::IsTrue(*iter == 1, L"Dereferencing an iterator at begin should be equivalent to the first value pushed");
			
			const auto constIntVector(intor);
			Assert::IsTrue(*constIntVector.begin() == *intor.begin(), L"Const copy begin not equivalent to original");

			++iter;
			Assert::ExpectException<std::exception>(func1, L"Dereferencing end of a vector should throw an exception");


			/// Pointer vector tests
			auto piter = pointor.begin();
			auto func2 = [&] { *piter; };
			Assert::ExpectException<std::exception>(func2, L"Dereferencing begin on an empty vector should throw an exception");
			
			int x = 1;
			pointor.pushBack(&x);
			piter = pointor.begin();
			Assert::IsTrue(*piter == &x, L"Dereferencing an piterator at begin should be equivalent to the first value pushed");

			const auto constPtrVector(pointor);
			Assert::IsTrue(*constPtrVector.begin() == *pointor.begin(), L"Const copy begin not equivalent to original");
			
			++piter;
			Assert::ExpectException<std::exception>(func2, L"Dereferencing end of a vector should throw an exception");


			/// Foo vector tests
			auto fooiter = footor.begin();
			auto func3 = [&] { *fooiter; };
			Assert::ExpectException<std::exception>(func3, L"Dereferencing begin on an empty vector should throw an exception");
			
			Foo foo(1);
			footor.pushBack(foo);
			fooiter = footor.begin();
			Assert::IsTrue(*fooiter == foo, L"Dereferencing an fooiterator at begin should be equivalent to the first value pushed");
			
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