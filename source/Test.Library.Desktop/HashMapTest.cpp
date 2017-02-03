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

		TEST_METHOD(TestTemplateSpecialization)
		{
			HashMap::HashMap<int, int> intMap(13);
			HashMap::HashMap<int*, int> ptrMap(13);
			HashMap::HashMap<char*, int> charMap(13);
			HashMap::HashMap<std::string, int> stringMap(13);
			HashMap::HashMap<Foo, int> fooMap(13);

			intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.containsKey(1), L"intMap does not contain inserted key");

			int x = 1;
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.containsKey(&x), L"ptrMap does not contain inserted key");

			char* c = "stuff";
			charMap.insert(std::pair<char*, int>(c, 1));
			Assert::IsTrue(charMap.containsKey(c), L"charMap does not contain inserted key");

			std::string s = "thangs";
			stringMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(stringMap.containsKey(s), L"stringMap does not contain inserted key");

			Foo foo(1);
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.containsKey(foo), L"fooMap does not contain inserted key");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestFind)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestInsert)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestRemove)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIndexOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestBegin)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestEnd)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestClear)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestSize)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestContainsKey)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorCopyConstructor)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorAssignmentOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorIncrementOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorDereferenceOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorArrowOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorEqualityOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorNotEqualOperator)
		{
			Assert::Fail(L"Method not implemented");
		}
	};
}