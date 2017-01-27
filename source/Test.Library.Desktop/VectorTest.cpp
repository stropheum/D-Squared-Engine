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
			Vector::Vector<int> copyIntor(intor);
			bool intcompare = intor == copyIntor;
			Assert::IsTrue(intcompare, 
				L"Copied vector not equivalent to original");
			intor.pushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsFalse(intcompare, 
				L"Copied vector equivalent after modifying original");
			copyIntor.pushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsTrue(intcompare, 
				L"Copied vector not equivalent after pushing identical values");

			Vector::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, 
				L"Copied pointer vector not equivalent to original");
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsFalse(pointor == copyPointor, 
				L"Copied vector equivalent after modifying original");
			copyPointor.pushBack(&x);
			Assert::IsTrue(pointor == copyPointor, 
				L"Copied vector not equivalent after pushing identical values");

			Vector::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor, 
				L"Copied Foo vector not equivalent to original");
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsFalse(footor == copyFootor, 
				L"Copied Foo vector equivalent after modifying original");
			copyFootor.pushBack(foo);
			Assert::IsTrue(footor == copyFootor, 
				L"Copied vector not equivalent after pushing identical values");
		}

		TEST_METHOD(TestComparisonOperator)
		{
			Assert::IsTrue(intor == intor, 
				L"Vector not equivalent to itself");
			Vector::Vector<int> copyIntor(intor);
			Assert::IsTrue(intor == copyIntor, 
				L"Copy constructor invocation not equivalent");
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, 
				L"Assignment operator copy not equivalent");

			Assert::IsTrue(pointor == pointor, 
				L"Vector not equivalent to itself");
			Vector::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, 
				L"Copy constructor invocation not equivalent");
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, 
				L"Assignment operator copy not equivalent");

			Assert::IsTrue(footor == footor, 
				L"Vector not equivalent to itself");
			Vector::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor,
				L"Copy constructor invocation not equivalent");
			copyFootor = footor;
			Assert::IsTrue(footor == copyFootor,
				L"Assignment operator copy not equivalent");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			Vector::Vector<int> copyIntor;
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, 
				L"Copied vector not equivalent to original");

			Vector::Vector<int*> copyPointor;
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, 
				L"Copied pointer vector not equivalent to original");

			Vector::Vector<Foo> copyFootor;
			copyFootor =footor;
			Assert::IsTrue(footor == copyFootor,
				L"Copied Foo vector not equivalent to original");
		}

		TEST_METHOD(TestFind)
		{
			auto iter = intor.find(0);
			Assert::IsTrue(iter == intor.end(),
				L"Begin and end not equivalent on empty vector");
			Assert::IsTrue(iter == intor.begin(),
				L"Find on first element not equivalent to Vector.begin()");
			intor.pushBack(1);
			iter = intor.find(1);
			Assert::IsFalse(iter == intor.end(),
				L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(iter == intor.begin(),
				L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*iter, 1,
				L"Find on first item should be equivalent to the first value pushed");
			intor.pushBack(100);
			iter = intor.find(1);
			Assert::IsTrue(iter == intor.begin(),
				L"Find on first item should not change after pushing a second");
			Assert::IsFalse(iter == intor.end(),
				L"Find on existing item should not be equivalent to end");
			iter = intor.find(100);
			Assert::IsTrue(++iter == intor.end(),
				L"Incrementing past final element not equivalent to end");

			int x = 1;
			int y = 2;
			auto piter = pointor.find(&x);
			Assert::IsTrue(piter == pointor.end(),
				L"Begin and end not equivalent on empty vector");
			Assert::IsTrue(piter == pointor.begin(),
				L"Find on first element not equivalent to Vector.begin()");
			pointor.pushBack(&x);
			piter = pointor.find(&x);
			Assert::IsFalse(piter == pointor.end(),
				L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(piter == pointor.begin(),
				L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*piter, &x,
				L"Find on first item should be equivalent to the first value pushed");
			pointor.pushBack(&y);
			piter = pointor.find(&x);
			Assert::IsTrue(piter == pointor.begin(),
				L"Find on first item should not change after pushing a second");
			Assert::IsFalse(piter == pointor.end(),
				L"Find on existing item should not be equivalent to end");
			piter = pointor.find(&y);
			Assert::IsTrue(++piter == pointor.end(),
				L"Incrementing past final element not equivalent to end");

			Foo foo(1);
			Foo bar(2);
			auto fooiter = footor.find(foo);
			Assert::IsTrue(fooiter == footor.end(),
				L"Begin and end not equivalent on empty vector");
			Assert::IsTrue(fooiter == footor.begin(),
				L"Find on first element not equivalent to Vector.begin()");
			footor.pushBack(foo);
			fooiter = footor.find(foo);
			Assert::IsFalse(fooiter == footor.end(),
				L"Find on existing element should not be equivalent to end");
			Assert::IsTrue(fooiter == footor.begin(),
				L"Find on first element should be equivalent to begin");
			Assert::AreEqual(*fooiter, foo,
				L"Find on first item should be equivalent to the first value pushed");
			footor.pushBack(bar);
			fooiter = footor.find(foo);
			Assert::IsTrue(fooiter == footor.begin(),
				L"Find on first item should not change after pushing a second");
			Assert::IsFalse(fooiter == footor.end(),
				L"Find on existing item should not be equivalent to end");
			fooiter = footor.find(bar);
			Assert::IsTrue(++fooiter == footor.end(),
				L"Incrementing past final element not equivalent to end");
		}

		TEST_METHOD(TestBegin)
		{
			Assert::IsTrue(intor.begin() == intor.end(),
				L"Begin should be equivalent to end on an empy vector");
			intor.pushBack(1);
			Assert::IsTrue(1 == *intor.begin(),
				L"Begin not equivalent with first value pushed");
			Assert::IsFalse(intor.begin() == intor.end());
			intor.pushBack(2);
			Assert::IsTrue(1 == *intor.begin(),
				L"Begin value changed after calling push back on non-empty vector");
			Assert::IsTrue(intor[0] == *intor.begin(),
				L"First index not equivalent to begin");

			int x = 1;
			int y = 2;
			Assert::IsTrue(pointor.begin() == pointor.end(),
				L"Begin should be equivalent to end on an empy vector");
			pointor.pushBack(&x);
			Assert::IsTrue(&x == *pointor.begin(),
				L"Begin not equivalent with first value pushed");
			Assert::IsFalse(pointor.begin() == pointor.end());
			pointor.pushBack(&y);
			Assert::IsTrue(&x == *pointor.begin(),
				L"Begin value changed after calling push back on non-empty vector");
			Assert::IsTrue(pointor[0] == *pointor.begin(),
				L"First index not equivalent to begin");

			Foo foo(1);
			Foo bar(2);
			Assert::IsTrue(footor.begin() == footor.end(),
				L"Begin should be equivalent to end on an empy vector");
			footor.pushBack(foo);
			Assert::IsTrue(foo == *footor.begin(),
				L"Begin not equivalent with first value pushed");
			Assert::IsFalse(footor.begin() == footor.end());
			footor.pushBack(bar);
			Assert::IsTrue(foo == *footor.begin(),
				L"Begin value changed after calling push back on non-empty vector");
			Assert::IsTrue(footor[0] == *footor.begin(),
				L"First index not equivalent to begin");
		}

		TEST_METHOD(TestEnd)
		{
			Assert::IsTrue(intor.begin() == intor.end(),
				L"End should be equivalent to begin on an empty vector");
			Vector::Vector<int>::Iterator iter = intor.end();
			Assert::IsTrue(iter == intor.end(),
				L"Iterator assigned to end should be equivalent to end");
			intor.pushBack(1);
			iter = intor.begin();
			Assert::IsFalse(iter == intor.end(),
				L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++iter == intor.end(),
				L"Iterator pointing to last element should be equivalent to end after incrementing");

			Assert::IsTrue(pointor.begin() == pointor.end(),
				L"End should be equivalent to begin on an empty vector");
			Vector::Vector<int*>::Iterator piter = pointor.end();
			Assert::IsTrue(piter == pointor.end(),
				L"Iterator assigned to end should be equivalent to end");
			int x = 1;
			pointor.pushBack(&x);
			piter = pointor.begin();
			Assert::IsFalse(piter == pointor.end(),
				L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++piter == pointor.end(),
				L"Iterator pointing to last element should be equivalent to end after incrementing");

			Assert::IsTrue(footor.begin() == footor.end(),
				L"End should be equivalent to begin on an empty vector");
			Vector::Vector<Foo>::Iterator fooiter = footor.end();
			Assert::IsTrue(fooiter == footor.end(),
				L"Iterator assigned to end should be equivalent to end");
			Foo foo(1);
			footor.pushBack(foo);
			fooiter = footor.begin();
			Assert::IsFalse(fooiter == footor.end(),
				L"Iterator pointing to begin should not be equivalent to end on a non-empty vector");
			Assert::IsTrue(++fooiter == footor.end(),
				L"Iterator pointing to last element should be equivalent to end after incrementing");
		}

		TEST_METHOD(TestFront)
		{
			auto func = [this] { intor.front(); };
			Assert::ExpectException<std::exception>(func,
				L"Front should be equivalent with begin on an empty vector");
			intor.pushBack(1);
			Assert::IsTrue(intor.front() == intor[0],
				L"Front should be equivalent with first index");
			Assert::IsTrue(intor.front() == *intor.begin(),
				L"Front should be equivalent with begin");
			intor.front() = 5;
			Assert::IsTrue(intor.front() == 5,
				L"Unable to modify Vector.front()");

			auto ptrfunc = [this] { pointor.front(); };
			Assert::ExpectException<std::exception>(ptrfunc,
				L"Front should be equivalent with begin on an empty vector");
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.front() == pointor[0],
				L"Front should be equivalent with first index");
			Assert::IsTrue(pointor.front() == *pointor.begin(),
				L"Front should be equivalent with begin");
			int y = 5;
			pointor.front() = &y;
			Assert::IsTrue(pointor.front() == &y,
				L"Unable to modify Vector.front()");

			auto foofunc = [this] { footor.front(); };
			Assert::ExpectException<std::exception>(foofunc,
				L"Front should be equivalent with begin on an empty vector");
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.front() == footor[0],
				L"Front should be equivalent with first index");
			Assert::IsTrue(footor.front() == *footor.begin(),
				L"Front should be equivalent with begin");
			Foo bar(5);
			footor.front() = bar;
			Assert::IsTrue(footor.front() == bar,
				L"Unable to modify Vector.front()");
		}

		TEST_METHOD(TestBack)
		{
			auto func = [this] { intor.back(); };
			Assert::ExpectException<std::exception>(func,
				L"Calling back on an empty vector should throw an exception");
			intor.pushBack(1);
			Assert::IsTrue(intor.back() == intor[0],
				L"Back should be equivalent to first value pushed onto an empty vector");
			intor.pushBack(2);
			Assert::IsTrue(intor.back() == intor[1],
				L"Back should b equivalent to last value pushed onto a vector");
			intor.back() = 10;
			Assert::IsTrue(intor.back() == 10,
				L"Vector.back() not modifiable");

			auto ptrfunc = [this] { pointor.back(); };
			Assert::ExpectException<std::exception>(ptrfunc,
				L"Calling back on an empty vector should throw an exception");
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.back() == pointor[0],
				L"Back should be equivalent to first value pushed onto an empty vector");
			int y = 2;
			pointor.pushBack(&y);
			Assert::IsTrue(pointor.back() == pointor[1],
				L"Back should b equivalent to last value pushed onto a vector");
			int z = 10;
			pointor.back() = &z;
			Assert::IsTrue(pointor.back() == &z,
				L"Vector.back() not modifiable");

			auto foofunc = [this] { footor.back(); };
			Assert::ExpectException<std::exception>(foofunc,
				L"Calling back on an empty vector should throw an exception");
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.back() == footor[0],
				L"Back should be equivalent to first value pushed onto an empty vector");
			Foo bar(2);
			footor.pushBack(bar);
			Assert::IsTrue(footor.back() == footor[1],
				L"Back should b equivalent to last value pushed onto a vector");
			Foo gar(10);
			footor.back() = gar;
			Assert::IsTrue(footor.back() == gar,
				L"Vector.back() not modifiable");
		}

		TEST_METHOD(TestAt)
		{
			auto func1 = [this] { intor.at(0); };
			Assert::ExpectException<std::exception>(func1,
				L"Accessing index of an empty vector should throw an exception");
			intor.pushBack(1);
			auto func2 = [this] { intor.at(1); };
			Assert::ExpectException<std::exception>(func2,
				L"Accessing out of vector bounds should throw an exception");
			auto func3 = [this] { intor.at(-1); };
			Assert::ExpectException<std::exception>(func3,
				L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(1 == intor.at(0),
				L"First element added should be equivalent to Vector.at(0)");
			intor.pushBack(2);
			Assert::IsTrue(1 == intor.at(0),
				L"First element should be equivalent to Vector.at(0) after pushing back multiple values");
			Assert::IsTrue(2 == intor.at(1),
				L"Last element should be equivalent to Vector.at(n-1)");

			auto ptrfunc1 = [this] { pointor.at(0); };
			Assert::ExpectException<std::exception>(ptrfunc1,
				L"Accessing index of an empty vector should throw an exception");
			int x = 1;
			pointor.pushBack(&x);
			auto ptrfunc2 = [this] { pointor.at(1); };
			Assert::ExpectException<std::exception>(ptrfunc2,
				L"Accessing out of vector bounds should throw an exception");
			auto ptrfunc3 = [this] { pointor.at(-1); };
			Assert::ExpectException<std::exception>(ptrfunc3,
				L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(&x == pointor.at(0),
				L"First element added should be equivalent to Vector.at(0)");
			int y = 2;
			pointor.pushBack(&y);
			Assert::IsTrue(&x == pointor.at(0),
				L"First element should be equivalent to Vector.at(0) after pushing back multiple values");
			Assert::IsTrue(&y == pointor.at(1),
				L"Last element should be equivalent to Vector.at(n-1)");

			auto foofunc1 = [this] { footor.at(0); };
			Assert::ExpectException<std::exception>(foofunc1,
				L"Accessing index of an empty vector should throw an exception");
			Foo foo(1);
			footor.pushBack(foo);
			auto foofunc2 = [this] { footor.at(1); };
			Assert::ExpectException<std::exception>(foofunc2,
				L"Accessing out of vector bounds should throw an exception");
			auto foofunc3 = [this] { footor.at(-1); };
			Assert::ExpectException<std::exception>(foofunc3,
				L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(foo == footor.at(0),
				L"First element added should be equivalent to Vector.at(0)");
			Foo bar(2);
			footor.pushBack(bar);
			Assert::IsTrue(foo == footor.at(0),
				L"First element should be equivalent to Vector.at(0) after pushing back multiple values");
			Assert::IsTrue(bar == footor.at(1),
				L"Last element should be equivalent to Vector.at(n-1)");
		}

		TEST_METHOD(TestIndexOperator)
		{
			auto func1 = [this] { intor[0]; };
			Assert::ExpectException<std::exception>(func1,
				L"Accessing index of an empty vector should throw an exception");
			intor.pushBack(1);
			auto func2 = [this] { intor[1]; };
			Assert::ExpectException<std::exception>(func2,
				L"Accessing out of vector bounds should throw an exception");
			auto func3 = [this] { intor[-1]; };
			Assert::ExpectException<std::exception>(func3,
				L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(1 == intor[0],
				L"First element added should be equivalent to Vector[0]");
			intor.pushBack(2);
			Assert::IsTrue(1 == intor[0],
				L"First element should be equivalent to Vector[0] after pushing back multiple values");
			Assert::IsTrue(2 == intor[1],
				L"Last element should be equivalent to Vector[n-1]");

			auto ptrfunc1 = [this] { pointor[0]; };
			Assert::ExpectException<std::exception>(ptrfunc1,
				L"Accessing index of an empty vector should throw an exception");
			int x = 1;
			pointor.pushBack(&x);
			auto ptrfunc2 = [this] { pointor[1]; };
			Assert::ExpectException<std::exception>(ptrfunc2,
				L"Accessing out of vector bounds should throw an exception");
			auto ptrfunc3 = [this] { pointor[-1]; };
			Assert::ExpectException<std::exception>(ptrfunc3,
				L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(&x == pointor[0],
				L"First element added should be equivalent to Vector[0]");
			int y = 2;
			pointor.pushBack(&y);
			Assert::IsTrue(&x == pointor[0],
				L"First element should be equivalent to Vector[0] after pushing back multiple values");
			Assert::IsTrue(&y == pointor[1],
				L"Last element should be equivalent to Vector[n-1]");

			auto foofunc1 = [this] { footor[0]; };
			Assert::ExpectException<std::exception>(foofunc1,
				L"Accessing index of an empty vector should throw an exception");
			Foo foo(1);
			footor.pushBack(foo);
			auto foofunc2 = [this] { footor[1]; };
			Assert::ExpectException<std::exception>(foofunc2,
				L"Accessing out of vector bounds should throw an exception");
			auto foofunc3 = [this] { footor[-1]; };
			Assert::ExpectException<std::exception>(foofunc3,
				L"Accessing a negative index of a vector should throw an exception");
			Assert::IsTrue(foo == footor[0],
				L"First element added should be equivalent to Vector[0]");
			Foo bar(2);
			footor.pushBack(bar);
			Assert::IsTrue(foo == footor[0],
				L"First element should be equivalent to Vector[0] after pushing back multiple values");
			Assert::IsTrue(bar == footor[1],
				L"Last element should be equivalent to Vector[n-1]");
		}

		TEST_METHOD(TestPopBack)
		{
			auto func1 = [this] { intor.popBack(); };
			Assert::ExpectException<std::exception>(func1,
				L"PopBack on empty vector should throw an exception");
			intor.pushBack(1);
			intor.pushBack(2);
			intor.pushBack(3);
			intor.popBack();
			Assert::AreEqual(static_cast<uint32_t>(2), intor.size(),
				L"Vector size not reducing after valid pop back");

			auto ptrfunc1 = [this] { pointor.popBack(); };
			Assert::ExpectException<std::exception>(ptrfunc1,
				L"PopBack on empty vector should throw an exception");
			int x = 1;
			int y = 2;
			int z = 3;
			pointor.pushBack(&x);
			pointor.pushBack(&y);
			pointor.pushBack(&z);
			pointor.popBack();
			Assert::AreEqual(static_cast<uint32_t>(2), pointor.size(),
				L"Vector size not reducing after valid pop back");

			auto foofunc1 = [this] { footor.popBack(); };
			Assert::ExpectException<std::exception>(foofunc1,
				L"PopBack on empty vector should throw an exception");
			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			footor.pushBack(foo);
			footor.pushBack(bar);
			footor.pushBack(gar);
			footor.popBack();
			Assert::AreEqual(static_cast<uint32_t>(2), footor.size(),
				L"Vector size not reducing after valid pop back");
		}

		TEST_METHOD(TestSize)
		{
			Assert::IsTrue(intor.size() == 0,
				L"Size not zero on empty vector");
			intor.pushBack(1);
			Assert::IsTrue(intor.size() == 1,
				L"Size not one after pushing one value");
			intor.popBack();
			Assert::IsTrue(intor.size() == 0,
				L"Size not zero after popping last value");

			Assert::IsTrue(pointor.size() == 0,
				L"Size not zero on empty vector");
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.size() == 1,
				L"Size not one after pushing one value");
			pointor.popBack();
			Assert::IsTrue(pointor.size() == 0,
				L"Size not zero after popping last value");

			Assert::IsTrue(footor.size() == 0,
				L"Size not zero on empty vector");
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.size() == 1,
				L"Size not one after pushing one value");
			footor.popBack();
			Assert::IsTrue(footor.size() == 0,
				L"Size not zero after popping last value");
		}

		TEST_METHOD(TestCapacity)
		{
			Vector::Vector<int> newintvector;
			Assert::AreEqual(static_cast<uint32_t>(10), newintvector.capacity(),
				L"New Vector should have a capacity of 10");
			for (int i = 0; i < 10; i++)
			{
				intor.pushBack(i);
				Assert::AreEqual(static_cast<uint32_t>(10), intor.capacity(),
					L"First ten pushes on a vector should retain the capacity at 10");
			}
			intor.pushBack(99);
			Assert::AreEqual(static_cast<uint32_t>(20), intor.capacity(),
				L"on 11th push, vector capacity should be 20");
			for (int i = 0; i < 11; i++)
			{
				
			}
		}

		TEST_METHOD(TestIsEmpty)
		{
			Assert::IsTrue(intor.isEmpty(),
				L"Cleared vector should be empty");
			intor.pushBack(1);
			Assert::IsFalse(intor.isEmpty(),
				L"Non-empty vector should not be empty");
			intor.popBack();
			Assert::IsTrue(intor.isEmpty(),
				L"Vector should be empty after popping last value");

			Assert::IsTrue(pointor.isEmpty(),
				L"Cleared vector should be empty");
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsFalse(pointor.isEmpty(),
				L"Non-empty vector should not be empty");
			pointor.popBack();
			Assert::IsTrue(pointor.isEmpty(),
				L"Vector should be empty after popping last value");

			Assert::IsTrue(footor.isEmpty(),
				L"Cleared vector should be empty");
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsFalse(footor.isEmpty(),
				L"Non-empty vector should not be empty");
			footor.popBack();
			Assert::IsTrue(footor.isEmpty(),
				L"Vector should be empty after popping last value");
		}

		TEST_METHOD(TestPushBack)
		{
			intor.pushBack(1);
			Assert::IsTrue(intor.back() == 1,
				L"Value pushed to back does not match");
			Assert::IsTrue(*intor.begin() == 1,
				L"First value pushed back is not equivalent to begin");
			intor.pushBack(2);
			Assert::IsTrue(intor.back() == 2,
				L"Second value pushed back is not equivalent to begin");
			
			int x = 1;
			int y = 2;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.back() == &x,
				L"Value pushed to back does not match");
			Assert::IsTrue(*pointor.begin() == &x,
				L"First value pushed back is not equivalent to begin");
			pointor.pushBack(&y);
			Assert::IsTrue(pointor.back() == &y,
				L"Second value pushed back is not equivalent to begin");

			Foo foo(1);
			Foo bar(2);
			footor.pushBack(foo);
			Assert::IsTrue(footor.back() == foo,
				L"Value pushed to back does not match");
			Assert::IsTrue(*footor.begin() == foo,
				L"First value pushed back is not equivalent to begin");
			footor.pushBack(bar);
			Assert::IsTrue(footor.back() == bar,
				L"Second value pushed back is not equivalent to begin");
		}

		TEST_METHOD(TestReserve)
		{
			Assert::IsTrue(intor.capacity() == 0,
				L"Vector capacity should be zero on clear");
			intor.reserve(100);
			Assert::IsTrue(intor.capacity() == 100,
				L"Vector capacity not reserving specified value");
			Assert::IsTrue(intor.size() == 0,
				L"Reserve changing vector size erroneously");
			intor.reserve(10);
			Assert::IsTrue(intor.capacity() == 10,
				L"Capacity not changing on reserve when shrinking");
			for (int i = 0; i < 10; i++)
			{
				intor.pushBack(i);
			}
			intor.reserve(5);
			Assert::IsTrue(intor.capacity() == 10,
				L"Reserving smaller than current size should shrink to fit");

			Assert::IsTrue(pointor.capacity() == 0,
				L"Vector capacity should be zero on clear");
			pointor.reserve(100);
			Assert::IsTrue(pointor.capacity() == 100,
				L"Vector capacity not reserving specified value");
			Assert::IsTrue(pointor.size() == 0,
				L"Reserve changing vector size erroneously");
			pointor.reserve(10);
			Assert::IsTrue(pointor.capacity() == 10,
				L"Capacity not changing on reserve when shrinking");
			int x[10];
			for (int i = 0; i < 10; i++)
			{
				x[i] = i;
				pointor.pushBack(&x[i]);
			}
			Assert::IsTrue(intor.capacity() == 10,
				L"Reserving smaller than current size should shrink to fit");

			Assert::IsTrue(footor.capacity() == 0,
				L"Vector capacity should be zero on clear");
			footor.reserve(100);
			Assert::IsTrue(footor.capacity() == 100,
				L"Vector capacity not reserving specified value");
			Assert::IsTrue(footor.size() == 0,
				L"Reserve changing vector size erroneously");
			footor.reserve(10);
			Assert::IsTrue(footor.capacity() == 10,
				L"Capacity not changing on reserve when shrinking");
			Foo foo(1);
			for (int i = 0; i < 10; i++)
			{
				footor.pushBack(foo);
			}
			Assert::IsTrue(footor.capacity() == 10,
				L"Reserving smaller than current size should shrink to fit");
		}

		TEST_METHOD(TestClear)
		{
			intor.pushBack(1);
			Assert::IsTrue(intor.size() == 1,
				L"Size incorrect after pushing first value");
			intor.clear();
			Assert::IsTrue(intor.size() == 0,
				L"Size not zero after clear");
			Assert::IsTrue(intor.capacity() == 0,
				L"Capacity not zero after clear");

			int x = 1;
			pointor.pushBack(&x);
			Assert::IsTrue(pointor.size() == 1,
				L"Size incorrect after pushing first value");
			pointor.clear();
			Assert::IsTrue(pointor.size() == 0,
				L"Size not zero after clear");
			Assert::IsTrue(pointor.capacity() == 0,
				L"Capacity not zero after clear");

			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsTrue(footor.size() == 1,
				L"Size incorrect after pushing first value");
			footor.clear();
			Assert::IsTrue(footor.size() == 0,
				L"Size not zero after clear");
			Assert::IsTrue(footor.capacity() == 0,
				L"Capacity not zero after clear");
		}

		TEST_METHOD(TestRemove)
		{
			intor.pushBack(1);
			intor.remove(1);
			Assert::IsTrue(intor.size() == 0,
				L"Size not reducing after removing a value");
			intor.pushBack(2);
			intor.remove(1);
			Assert::IsTrue(intor.size() == 1,
				L"Size changing after removing a nonexistent value");
		}

		TEST_METHOD(TestShrinkToFit)
		{
			intor.pushBack(1);
			intor.pushBack(2);
			intor.pushBack(3);
			Assert::IsTrue(intor.capacity() == 10,
				L"Default capacity for vector should be 10");
			intor.shrinkToFit();
			Assert::IsTrue(intor.capacity() == 3,
				L"Capacity should be 3 after shrinking to fit");
			intor.clear();
			intor.shrinkToFit();
			Assert::IsTrue(intor.capacity() == 0,
				L"Capacity should be 3 after shrinking to fit on empty vector");

			int x = 1;
			int y = 2;
			int z = 3;
			pointor.pushBack(&x);
			pointor.pushBack(&y);
			pointor.pushBack(&z);
			Assert::IsTrue(pointor.capacity() == 10,
				L"Default capacity for vector should be 10");
			pointor.shrinkToFit();
			Assert::IsTrue(pointor.capacity() == 3,
				L"Capacity should be 3 after shrinking to fit");
			pointor.clear();
			pointor.shrinkToFit();
			Assert::IsTrue(pointor.capacity() == 0,
				L"Capacity should be 3 after shrinking to fit on empty vector");

			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			footor.pushBack(foo);
			footor.pushBack(bar);
			footor.pushBack(gar);
			Assert::IsTrue(footor.capacity() == 10,
				L"Default capacity for vector should be 10");
			footor.shrinkToFit();
			Assert::IsTrue(footor.capacity() == 3,
				L"Capacity should be 3 after shrinking to fit");
			footor.clear();
			footor.shrinkToFit();
			Assert::IsTrue(footor.capacity() == 0,
				L"Capacity should be 3 after shrinking to fit on empty vector");
		}

		TEST_METHOD(TestIteratorComparisonOperator)
		{
			auto iter = intor.begin();
			Assert::IsTrue(iter == intor.begin(),
				L"Iterator should be equivalent to the value it was assigned to");
			Assert::IsTrue(iter == intor.end(),
				L"Iterator should be equivalent to end when assigned to begin on an empty vector");
			intor.pushBack(1);
			iter = intor.begin();
			Assert::IsFalse(iter == intor.end(),
				L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Vector::Vector<int> newintvector;
			auto newiter = newintvector.begin();
			Assert::IsFalse(iter == newiter,
				L"Iterators with different owners should not be equivalent");

			auto piter = pointor.begin();
			Assert::IsTrue(piter == pointor.begin(),
				L"Iterator should be equivalent to the value it was assigned to");
			Assert::IsTrue(piter == pointor.end(),
				L"Iterator should be equivalent to end when assigned to begin on an empty vector");
			int x = 1;
			pointor.pushBack(&x);
			piter = pointor.begin();
			Assert::IsFalse(piter == pointor.end(),
				L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Vector::Vector<int*> newptrvector;
			auto newpiter = newptrvector.begin();
			Assert::IsFalse(piter == newpiter,
				L"Iterators with different owners should not be equivalent");

			auto fooiter = footor.begin();
			Assert::IsTrue(fooiter == footor.begin(),
				L"Iterator should be equivalent to the value it was assigned to");
			Assert::IsTrue(fooiter == footor.end(),
				L"Iterator should be equivalent to end when assigned to begin on an empty vector");
			Foo foo(1);
			footor.pushBack(foo);
			fooiter = footor.begin();
			Assert::IsFalse(piter == pointor.end(),
				L"Iterator assigned to begin should not be equivalent to end on a non-empty vector");
			Vector::Vector<Foo> newfoovector;
			auto newfooiter = newfoovector.begin();
			Assert::IsFalse(fooiter == newfooiter,
				L"Iterators with different owners should not be equivalent");
		}

		TEST_METHOD(TestIteratorIncrement)
		{
			intor.pushBack(1);
			auto iter = intor.begin();
			Assert::IsFalse(iter == intor.end(),
				L"Iterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++iter == intor.end(),
				L"Incrementing an iterator on a size of one vector should be equivalent to end");
			auto func = [&] { ++iter; };
			Assert::ExpectException<std::exception>(func,
				L"Incrementing past end should throw an exception");

			int x = 1;
			pointor.pushBack(&x);
			auto piter = pointor.begin();
			Assert::IsFalse(piter == pointor.end(),
				L"piterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++piter == pointor.end(),
				L"Incrementing an piterator on a size of one vector should be equivalent to end");
			auto pfunc = [&] { ++piter; };
			Assert::ExpectException<std::exception>(pfunc,
				L"Incrementing past end should throw an exception");

			Foo foo(1);
			footor.pushBack(foo);
			auto fooiter = footor.begin();
			Assert::IsFalse(fooiter == footor.end(),
				L"fooiterator assigned to begin on a non-empty vector should not be equivalent to end");
			Assert::IsTrue(++fooiter == footor.end(),
				L"Incrementing an fooiterator on a size of one vector should be equivalent to end");
			auto foofunc = [&] { ++fooiter; };
			Assert::ExpectException<std::exception>(foofunc,
				L"Incrementing past end should throw an exception");
		}

		TEST_METHOD(TestIteratorDereference)
		{
			auto iter = intor.begin();
			auto func1 = [&] { *iter; };
			Assert::ExpectException<std::exception>(func1,
				L"Dereferencing begin on an empty vector should throw an exception");
			intor.pushBack(1);
			iter = intor.begin();
			Assert::IsTrue(*iter == 1,
				L"Dereferencing an iterator at begin should be equivalent to the first value pushed");
			++iter;
			Assert::ExpectException<std::exception>(func1,
				L"Dereferencing end of a vector should throw an exception");

			auto piter = pointor.begin();
			auto func2 = [&] { *piter; };
			Assert::ExpectException<std::exception>(func2,
				L"Dereferencing begin on an empty vector should throw an exception");
			int x = 1;
			pointor.pushBack(&x);
			piter = pointor.begin();
			Assert::IsTrue(*piter == &x,
				L"Dereferencing an piterator at begin should be equivalent to the first value pushed");
			++piter;
			Assert::ExpectException<std::exception>(func2,
				L"Dereferencing end of a vector should throw an exception");

			auto fooiter = footor.begin();
			auto func3 = [&] { *fooiter; };
			Assert::ExpectException<std::exception>(func3,
				L"Dereferencing begin on an empty vector should throw an exception");
			Foo foo(1);
			footor.pushBack(foo);
			fooiter = footor.begin();
			Assert::IsTrue(*fooiter == foo,
				L"Dereferencing an fooiterator at begin should be equivalent to the first value pushed");
			++fooiter;
			Assert::ExpectException<std::exception>(func3,
				L"Dereferencing end of a vector should throw an exception");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}