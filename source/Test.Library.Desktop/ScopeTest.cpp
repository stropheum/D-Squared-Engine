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
			Library::Scope scope1;
			auto& datum1 = scope1.append("New Datum");
			Assert::IsTrue(datum1 != nullptr);
			Assert::IsTrue(datum1 == Library::DatumType::Unknown);
			Assert::IsTrue(datum1.toString() == "Unknown Type");

			auto& datum2 = scope1.append("Another Datum");
			Assert::IsTrue(datum1 != nullptr);
			Assert::IsTrue(datum2 != nullptr);
			Assert::IsTrue(datum2 == Library::DatumType::Unknown);
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
			Library::Scope scope1, scope2;
			Library::Scope& childFromScope1 = scope1.appendScope("Scope one is my daddy");
			Assert::IsTrue(scope1.search("Scope one is my daddy") != nullptr);
			Assert::IsTrue(scope2.search("Scope one is my daddy") == nullptr);
			
			scope2.adopt(childFromScope1, "Scope two is my new daddy");
			Assert::IsTrue(scope1.find("Scope one is my daddy")->size() == 0);
			Assert::IsTrue(scope2.find("Scope two is my new daddy") != nullptr);
		}

		TEST_METHOD(TestGetParent)
		{
			Library::Scope scope1;
			Assert::IsTrue(scope1.getParent() == nullptr);
			
			auto& scope2 = scope1.appendScope("scope 2");
			Assert::IsTrue(scope2.getParent() == &scope1);
			Assert::IsTrue(scope1.getParent() == nullptr);

			auto& scope3 = scope2.appendScope("scope 3");
			Assert::IsTrue(scope3.getParent() == &scope2);
			Assert::IsTrue(scope2.getParent() == &scope1);
			Assert::IsTrue(scope1.getParent() == nullptr);

			auto& scope2Brother = scope1.appendScope("Scope 2 brother");
			Assert::IsTrue(scope3.getParent() == &scope2);
			Assert::IsTrue(scope2.getParent() == &scope1);
			Assert::IsTrue(scope1.getParent() == nullptr);
			Assert::IsTrue(scope2Brother.getParent() == &scope1);
		}

		TEST_METHOD(TestIndexOperator)
		{
			Library::Scope scope1;
			scope1["Eggs"] = Library::DatumType::Integer;
			Assert::IsTrue(scope1.find("Eggs") != nullptr);
			scope1["Eggs"] = 5;
			Assert::IsTrue(scope1["Eggs"] == 5);

			scope1["Sword"] = Library::DatumType::String;
			Assert::IsTrue(scope1.find("Sword") != nullptr);
			scope1["Sword"] = "Katana";
			Assert::IsTrue(scope1["Sword"] == "Katana");
		}

		TEST_METHOD(TestEqualityOperator)
		{
			Library::Scope scope1, scope2;
			Assert::IsTrue(scope1 == scope2);
			
			scope1.appendScope("New child scope");
			Assert::IsFalse(scope1 == scope2);

			scope2.appendScope("New child scope");
			Assert::IsTrue(scope1 == scope2);

			scope1.append("Eggs");
			Assert::IsFalse(scope1 == scope2);

			scope2.append("Eggs");
			Assert::IsTrue(scope1 == scope2);

			scope1["Eggs"] = Library::DatumType::Integer;
			scope2["Eggs"] = Library::DatumType::Integer;
			Assert::IsTrue(scope1 == scope2);
		}

		TEST_METHOD(TestFindName)
		{
			Library::Scope scope1;
			Assert::ExpectException<std::exception>([&] { scope1.findName(&scope1); });

			auto& scope2 = scope1.appendScope("Bananas");
			Assert::IsTrue(scope1.findName(&scope2) == "Bananas");

			auto& scope3 = scope2.appendScope("Apples");
			Assert::IsTrue(scope2.findName(&scope3) == "Apples");
			Assert::IsTrue(scope1.findName(&scope3) != "Apples");
		}

		TEST_METHOD(TestRTTI)
		{
			Library::Scope scope1, scope2;
			Assert::IsTrue(scope1.Is(scope2.TypeIdClass()));
			Assert::IsTrue(scope1.ToString() == "Scope");
			auto ptr = scope1.QueryInterface(scope1.TypeIdClass());
			Assert::IsTrue(scope1.Equals(ptr));
		}
	};
}