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
		Vector<int>*  intVector;
		Vector<int*>* ptrVector;
		Vector<Foo>*  fooVector;

		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		/// Detects if memory state has been corrupted
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
			intVector = new Vector<int>();
			ptrVector = new Vector<int*>();
			fooVector = new Vector<Foo>();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			delete(intVector);
			delete(ptrVector);
			delete(fooVector);
			finalizeLeakDetection();
		}

		TEST_METHOD(TestSquareBracketOperator)
		{
			intVector->pushBack(1);
			intVector->pushBack(2);
			Assert::AreEqual(1, (*intVector)[0]);
			Assert::AreEqual(2, (*intVector)[1]);

			int x = 1;
			int y = 2;
			ptrVector->pushBack(&x);
			ptrVector->pushBack(&y);
			Assert::AreEqual(&x, ptrVector->at(0));
			Assert::AreEqual(&y, ptrVector->at(1));

			Foo foo(1);
			Foo bar(2);
			fooVector->pushBack(foo);
			fooVector->pushBack(bar);
			Assert::AreEqual(foo, fooVector->at(0));
			Assert::AreEqual(bar, fooVector->at(1));
		}

		TEST_METHOD(TestPushBack)
		{
			intVector->pushBack(12);
			intVector->pushBack(50);
			intVector->pushBack(100);
			Assert::AreEqual(12, (*intVector)[0]);
			Assert::AreEqual(50, (*intVector)[1]);
			Assert::AreEqual(100, (*intVector)[2]);

			int x = 1;
			int y = 2;
			int z = 3;
			ptrVector->pushBack(&x);
			ptrVector->pushBack(&y);
			ptrVector->pushBack(&z);
			Assert::AreEqual(&x, ptrVector->at(0));
			Assert::AreEqual(&y, ptrVector->at(1));
			Assert::AreEqual(&z, ptrVector->at(2));

			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			fooVector->pushBack(foo);
			fooVector->pushBack(bar);
			fooVector->pushBack(gar);
			Assert::AreEqual(foo, fooVector->at(0));
			Assert::AreEqual(bar, fooVector->at(1));
			Assert::AreEqual(gar, fooVector->at(2));
		}

		TEST_METHOD(TestReserve)
		{
			intVector->pushBack(1);
			intVector->pushBack(2);
			intVector->pushBack(3);
			Assert::AreEqual(1, intVector->at(0));
			Assert::AreEqual(2, intVector->at(1));
			Assert::AreEqual(3, intVector->at(2));
			intVector->reserve(20);
			Assert::AreEqual(1, intVector->at(0));
			Assert::AreEqual(2, intVector->at(1));
			Assert::AreEqual(3, intVector->at(2));
			intVector->reserve(30);
			Assert::AreEqual(1, intVector->at(0));
			Assert::AreEqual(2, intVector->at(1));
			Assert::AreEqual(3, intVector->at(2));

			int x = 1;
			int y = 2;
			int z = 3;
			ptrVector->pushBack(&x);
			ptrVector->pushBack(&y);
			ptrVector->pushBack(&z);
			Assert::AreEqual(&x, ptrVector->at(0));
			Assert::AreEqual(&y, ptrVector->at(1));
			Assert::AreEqual(&z, ptrVector->at(2));
			ptrVector->reserve(20);
			Assert::AreEqual(&x, ptrVector->at(0));
			Assert::AreEqual(&y, ptrVector->at(1));
			Assert::AreEqual(&z, ptrVector->at(2));
			ptrVector->reserve(30);
			Assert::AreEqual(&x, ptrVector->at(0));
			Assert::AreEqual(&y, ptrVector->at(1));
			Assert::AreEqual(&z, ptrVector->at(2));

			Foo foo(1);
			Foo bar(2);
			Foo gar(3);
			fooVector->pushBack(foo);
			fooVector->pushBack(bar);
			fooVector->pushBack(gar);
			Assert::AreEqual(foo, fooVector->at(0));
			Assert::AreEqual(bar, fooVector->at(1));
			Assert::AreEqual(gar, fooVector->at(2));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}