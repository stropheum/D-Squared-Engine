#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TestLibraryDesktop
{
	TEST_CLASS(LeakDetectionTest)
	{
	public:

		// Sets up leak detection logic
		static void InitializeLeakDetection()
		{
#if _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_DEBUG
		}

		// Detects if memory state has been corrupted
		static void FinalizeLeakDetection()
		{
#if _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif //_DEBUG
		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			InitializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			FinalizeLeakDetection();
		}

		static _CrtMemState sStartMemState;
	};

	_CrtMemState LeakDetectionTest::sStartMemState;
}