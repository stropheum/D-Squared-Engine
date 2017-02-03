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
//			HashMap::HashMap<char*, char*> hm(13);
//			char* keys[10];
//			keys[0] = "key zero";
//			keys[1] = "key one";
//			keys[2] = "key two";
//			keys[3] = "key three";
//			keys[4] = "key four";
//			keys[5] = "key five";
//			keys[6] = "key six";
//			keys[7] = "key seven";
//			keys[8] = "key eight";
//			keys[9] = "key nine";
//
//			char* strings[10];
//			strings[0] = "value zero";
//			strings[1] = "value one";
//			strings[2] = "value two";
//			strings[3] = "value three";
//			strings[4] = "value four";
//			strings[5] = "value five";
//			strings[6] = "value six";
//			strings[7] = "value seven";
//			strings[8] = "value eight";
//			strings[9] = "value nine";
//
//			for (int i = 0; i < 10; i++)
//			{
////				std::pair<char*, char*> myPair(keys[i], strings[i]);
//				hm.insert(std::pair<char*, char*>(keys[i], strings[i]));
//			}
			
//			for (int i = 0; i < 10; i++)
//			{
//				auto iter = hm.find(keys[i]);
//				if (iter != hm.end())
//				{
//					auto expected = strings[i];
//					auto actual = (*iter).second;
//					Assert::IsTrue(expected == actual);
//				}
//			}

			HashMap::HashMap<int,   int> intMap(13);
			HashMap::HashMap<int*,  int> ptrMap(13);
			HashMap::HashMap<char*, int> charStarMap(13);
			HashMap::HashMap<Foo,  int> fooMap(13);

			intMap.insert(std::pair<int, int>(1, 1));

			int x = 1;
			ptrMap.insert(std::pair<int*, int>(&x, 1));

			char* c = "dicks";
			charStarMap.insert(std::pair<char*, int>(c, 1));

			Foo foo(1);
			fooMap.insert(std::pair<Foo, int>(foo, 1));
		}
	};
}