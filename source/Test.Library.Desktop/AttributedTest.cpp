#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(AttributedTest)
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

		TEST_METHOD(TestMethod1)
		{
			Library::AttributedFoo myFoo;
			myFoo.populate();
//			Assert::IsFalse(myFoo.isAttribute("Nothing"));
//			myFoo.appendAuxiliaryAttribute("Nothing");
//			Assert::IsTrue(myFoo.isAttribute("Nothing"));
		}
	};
}