#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"
#include "Datum.h"

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
			Library::Scope s1, s2, s3;
			Assert::IsTrue(s1.getParent() == nullptr);
			Assert::IsTrue(s1 == s1 && s1 == s2 && s1 == s3, L"Default constructed scopes should be equivalent");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Library::Scope s1, s2;
			s1.append("I'm a new Datum =D");
			Assert::IsFalse(s1 == s2, L"Scopes with different datums should not be equivalent");

			Library::Scope s3(s1);
			Assert::IsTrue(s1 == s3, L"Scopes with same datum structure should be equivalent");
			Assert::IsFalse(s1 == s2, L"Copied scope equivalent to empty Scope");
		}

		TEST_METHOD(TestAssignment)
		{
			Library::Scope s1, s2, s3;
			Assert::IsTrue(s1 == s2 && s1 == s3);

			s1.append("Datum? I hardly knew um");
			Assert::IsFalse(s1 == s2 || s1 == s3);
		}

		TEST_METHOD(TestFind)
		{
			Library::Scope s1;
			Library::Datum myDatum(Library::DatumType::String);
			myDatum = "Bazooka";
			s1.append("Weapons") = myDatum;
			Assert::IsTrue(s1["Weapons"] == "Bazooka");
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