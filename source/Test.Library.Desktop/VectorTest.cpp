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
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			finalizeLeakDetection();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}