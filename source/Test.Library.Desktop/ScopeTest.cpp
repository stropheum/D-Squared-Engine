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
			auto& temp = s1.append("Weapons");
			temp = myDatum;
			Library::Datum* result = s1.find("Weapons");
			Assert::IsTrue(*result == myDatum);

			Library::Scope s2;
			Library::Datum myIntDatum(Library::DatumType::Integer);
			myIntDatum = 1337;
			auto& intTemp = s2.append("Coins");
			intTemp = myIntDatum;
			Library::Datum* intResult = s2.find("Coins");
			Assert::IsTrue(*intResult == myIntDatum);
		}

		TEST_METHOD(TestSearch)
		{
			Library::Scope scope1;
			auto& scope2 = scope1.appendScope("Child One");
			auto& scope3 = scope2.appendScope("Child Two");
			Assert::IsTrue(scope3.search("Child One") != nullptr);
			Assert::IsTrue(scope2.search("Child One") != nullptr);
			Assert::IsTrue(scope1.search("Child One") != nullptr);

			auto& datum1 = scope1.append("Eggs");
			datum1 = Library::DatumType::Integer;
			datum1 = 10;

			auto& datum2 = scope2.append("Allies");
			datum2 = Library::DatumType::String;
			datum2 = "Iron Man";

			auto& datum3 = scope3.append("Velocity");
			datum3 = Library::DatumType::Float;
			datum3 = 12.5f;

			Assert::IsTrue(scope1.search("NotInMyDangScope") == nullptr);
			Assert::IsTrue(scope2.search("NotInMyDangScope") == nullptr);
			Assert::IsTrue(scope3.search("NotInMyDangScope") == nullptr);

			Assert::IsTrue(scope1.search("Eggs") != nullptr);
			Assert::IsTrue(scope2.search("Eggs") != nullptr);
			Assert::IsTrue(scope3.search("Eggs") != nullptr);
			Assert::IsTrue(scope1.search("Eggs")[0] == 10);
			Assert::IsTrue(scope2.search("Eggs")[0] == 10);
			Assert::IsTrue(scope3.search("Eggs")[0] == 10);

			Assert::IsTrue(scope1.search("Allies") == nullptr);
			Assert::IsTrue(scope2.search("Allies") != nullptr);
			Assert::IsTrue(scope3.search("Allies") != nullptr);
			Assert::IsTrue(scope2.search("Allies")[0] == "Iron Man");
			Assert::IsTrue(scope3.search("Allies")[0] == "Iron Man");

			Assert::IsTrue(scope1.search("Velocity") == nullptr);
			Assert::IsTrue(scope2.search("Velocity") == nullptr);
			Assert::IsTrue(scope3.search("Velocity") != nullptr);
			Assert::IsTrue(scope3.search("Velocity")[0] == 12.5f);

			Assert::IsTrue(scope1["Eggs"] == 10);
			Assert::IsTrue(scope2["Allies"] == "Iron Man");
			Assert::IsTrue(scope3["Velocity"] == 12.5f);
		}

		TEST_METHOD(TestAppend)
		{
			// TODO: Implement Method
			Assert::Fail(L"Test not implemented");
		}

		TEST_METHOD(TestAppendScope)
		{
			Library::Scope s1;
			auto& scope = s1.appendScope("Scope");
			auto& datum = scope.append("HandBag");
			datum = Library::DatumType::Integer;
			datum = 5;
			Assert::IsTrue(scope.search("HandBag") != nullptr);
			Assert::IsTrue(scope.search("Scope") != nullptr);
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