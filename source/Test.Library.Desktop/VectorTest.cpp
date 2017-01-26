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
			Assert::IsTrue(intcompare, L"Copied vector not equivalent to original");
			intor.pushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsFalse(intcompare, L"Copied vector equivalent after modifying original");
			copyIntor.pushBack(1);
			intcompare = intor == copyIntor;
			Assert::IsTrue(intcompare, L"Copied vector not equivalent after pushing identical values");

			Vector::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, L"Copied pointer vector not equivalent to original");
			int x = 1;
			pointor.pushBack(&x);
			Assert::IsFalse(pointor == copyPointor, L"Copied vector equivalent after modifying original");
			copyPointor.pushBack(&x);
			Assert::IsTrue(pointor == copyPointor, L"Copied vector not equivalent after pushing identical values");

			Vector::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor, L"Copied Foo vector not equivalent to original");
			Foo foo(1);
			footor.pushBack(foo);
			Assert::IsFalse(footor == copyFootor, L"Copied Foo vector equivalent after modifying original");
			copyFootor.pushBack(foo);
			Assert::IsTrue(footor == copyFootor, L"Copied vector not equivalent after pushing identical values");
		}

		TEST_METHOD(TestComparisonOperator)
		{
			Assert::IsTrue(intor == intor, L"Vector not equivalent to itself");
			Vector::Vector<int> copyIntor(intor);
			Assert::IsTrue(intor == copyIntor, L"Copy constructor invocation not equivalent");
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, L"Assignment operator copy not equivalent");

			Assert::IsTrue(pointor == pointor, L"Vector not equivalent to itself");
			Vector::Vector<int*> copyPointor(pointor);
			Assert::IsTrue(pointor == copyPointor, L"Copy constructor invocation not equivalent");
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, L"Assignment operator copy not equivalent");

			Assert::IsTrue(footor == footor, L"Vector not equivalent to itself");
			Vector::Vector<Foo> copyFootor(footor);
			Assert::IsTrue(footor == copyFootor, L"Copy constructor invocation not equivalent");
			copyFootor = footor;
			Assert::IsTrue(footor == copyFootor, L"Assignment operator copy not equivalent");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			Vector::Vector<int> copyIntor;
			copyIntor = intor;
			Assert::IsTrue(intor == copyIntor, L"Copied vector not equivalent to original");

			Vector::Vector<int*> copyPointor;
			copyPointor = pointor;
			Assert::IsTrue(pointor == copyPointor, L"Copied pointer vector not equivalent to original");

			Vector::Vector<Foo> copyFootor;
			copyFootor =footor;
			Assert::IsTrue(footor == copyFootor, L"Copied Foo vector not equivalent to original");
		}

//		TEST_METHOD(TestFind)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestBegin)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestEnd)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestFront)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestBack)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestAt)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestIndexOperator)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestPopBack)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestSize)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestCapacity)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestIsEmpty)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestPushBack)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestReserve)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestClear)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestRemove)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestShrinkToFit)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestIteratorComparisonOperator)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestIteratorIncrement)
//		{
//			Assert::Fail(L"Test not implemented");
//		}
//
//		TEST_METHOD(TestIteratorDereference)
//		{
//			Assert::Fail(L"Test not implemented");
//		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}