#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(SListTest)
	{
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

		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			// Initialize data needed for every test
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			// Cleanup class level data
		}

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			initializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			finalizeLeakDetection();
		}

		TEST_METHOD(TestPushFront)
		{
			//TODO implement method test	
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestPopFront)
		{
			//TODO implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestPushBack)
		{
			//TODO implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestIsEmpty)
		{
			//TODO implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestFront)
		{
			//TODO implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestBack)
		{
			//TODO implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestSize)
		{
			//TODO implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestCopy)
		{
			//TODO: implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			//TODO: implement method test
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestClear)
		{
			//TODO: implement method test
			Assert::Fail(L"Test not implemented");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}