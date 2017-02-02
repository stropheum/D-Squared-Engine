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
			HashMap::HashMap<char*, char*> hm(13);
			char* keys[10];
			keys[0] = "key zero";
			keys[1] = "key one";
			keys[2] = "key two";
			keys[3] = "key three";
			keys[4] = "key four";
			keys[5] = "key five";
			keys[6] = "key six";
			keys[7] = "key seven";
			keys[8] = "key eight";
			keys[9] = "key nine";

			char* strings[10];
			strings[0] = "value zero";
			strings[1] = "value one";
			strings[2] = "value two";
			strings[3] = "value three";
			strings[4] = "value four";
			strings[5] = "value five";
			strings[6] = "value six";
			strings[7] = "value seven";
			strings[8] = "value eight";
			strings[9] = "value nine";

			for (int i = 0; i < 10; i++)
			{
				std::pair<char*, char*> myPair(keys[i], strings[i]);
				hm.insert(myPair);
			}

//			auto val = hm.find(keys[0]);
			for (std::uint32_t i = 0; i < 10; i++)
			{
				auto val = hm.find(keys[i]);
				auto dref = *val;
				if (true)
				{
//					auto val = 1;
				}
			}
			HashMap::HashMap<char*, char*> newMap;
			std::pair<char*, char*> myPair(keys[0], strings[0]);
			newMap.insert(myPair);
			
			Assert::IsTrue(hm.find("somebullshit") == hm.end());
		}
	};
}