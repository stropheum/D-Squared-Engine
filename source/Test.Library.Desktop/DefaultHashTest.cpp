#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "HashMap.h"
#include <winnt.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(DefaultHashTest)
	{
	public:

//		// Sets up leak detection logic
//		static void initializeLeakDetection()
//		{
//#if _DEBUG
//			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
//			_CrtMemCheckpoint(&sStartMemState);
//#endif //_Debug
//		}
//
//		// Detects if memory state has been corrupted
//		static void finalizeLeakDetection()
//		{
//#if _DEBUG
//			_CrtMemState endMemState, diffMemState;
//			_CrtMemCheckpoint(&endMemState);
//			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
//			{
//				_CrtMemDumpStatistics(&diffMemState);
//				Assert::Fail(L"Memory Leaks!");
//			}
//#endif //_DEBUG
//		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			LeakDetector::InitializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			LeakDetector::FinalizeLeakDetection();
		}

		TEST_METHOD(TestGenericHash)
		{
			Library::DefaultHash<float> hashFunctor;
			float foo = 5.0f;

			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(&foo);
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < sizeof(float); i++)
			{
				hash += bytes[i];
			}
			
			Assert::AreEqual(hash, hashFunctor(foo), L"Generic hash target not performing same functionality as generic hash");
		}

		TEST_METHOD(TestIntHash)
		{
			Library::DefaultHash<int> intHash;
			Assert::AreEqual(1u, intHash(1), L"Integer hash should be the same value as the integer passed in");
		}

		TEST_METHOD(TestStringHash)
		{
			Library::DefaultHash<std::string> hash;
			std::uint32_t expected = 'h' + 'e' + 'l' + 'l' + 'o';
			Assert::AreEqual(expected, hash("hello"), L"String hash should be sum of its character values");
		}

		TEST_METHOD(TestCharStarHash)
		{
			Library::DefaultHash<char*> hash;
			std::uint32_t expected = 'h' + 'e' + 'l' + 'l' + 'o';
			char* value = "hello";
			Assert::AreEqual(expected, hash(value), L"Char* hash should be sum of its character values");
		}

		TEST_METHOD(TestPointerHash)
		{
			Library::DefaultHash<float*> hashFunctor;
			float* foo = new float(5.0f);

			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(foo);
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < sizeof(float*); i++)
			{
				hash += bytes[i];
			}

			Assert::IsTrue(hash == hashFunctor(foo), L"Generic pointer hash target not performing same functionality as generic hash");
			delete foo;
		}

//	private:
//		static _CrtMemState sStartMemState;
	};

//	_CrtMemState DefaultHashTest::sStartMemState;
}