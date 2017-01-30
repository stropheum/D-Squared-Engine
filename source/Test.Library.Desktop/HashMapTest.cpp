#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(TestHashMap)
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

		TEST_METHOD(TestConstruction)
		{
			HashMap::HashMap<char*, int> hm(13);
			char* strings[10];
			strings[0] = "zero";
			strings[1] = "one";
			strings[2] = "two";
			strings[3] = "three";
			strings[4] = "four";
			strings[5] = "five";
			strings[6] = "six";
			strings[7] = "seven";
			strings[8] = "eight";
			strings[9] = "nine";
			for (auto str : strings)
			{
				hm.find(str);
			}

			HashMap::HashMap<Foo, int> foomap();
		}
	};
}