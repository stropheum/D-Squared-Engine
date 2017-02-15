#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(ScopeTest)
	{
	public:

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

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			initializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			finalizeLeakDetection();
		}

		TEST_METHOD(TestConstructor)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestMoveConstructor)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestAssignment)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestMoveAssignment)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestFind)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestSearch)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestAppend)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestAppendScope)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestAdopt)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestGetParent)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestIndexOperator)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestEqualityOperator)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestFindName)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}
	};
}