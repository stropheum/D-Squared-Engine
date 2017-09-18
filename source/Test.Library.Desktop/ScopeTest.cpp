#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "Scope.h"
#include "Datum.h"
#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	TEST_CLASS(ScopeTest)
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
//#endif //_Debug
//		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			LeakDetector::InitializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			LeakDetector::FinalizeLeakDetection();
		}

		TEST_METHOD(TestConstructor)
		{
			Library::Scope s1, s2, s3;
			Assert::IsTrue(s1.GetParent() == nullptr);
			Assert::IsTrue(s1 == s1 && s1 == s2 && s1 == s3, L"Default constructed scopes should be equivalent");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Library::Scope s1, s2;
			s1.Append("I'm a new Datum =D");
			Assert::IsFalse(s1 == s2, L"Scopes with different datums should not be equivalent");

			Library::Scope s3(s1);
			Assert::IsTrue(s1 == s3, L"Scopes with same datum structure should be equivalent");
			Assert::IsFalse(s1 == s2, L"Copied scope equivalent to empty Scope");
		}

		TEST_METHOD(TestAssignment)
		{
			Library::Scope s1, s2, s3;
			Assert::IsTrue(s1 == s2 && s1 == s3);

			s1.Append("Datum? I hardly knew um");
			Assert::IsFalse(s1 == s2 || s1 == s3);
		}

		TEST_METHOD(TestMoveSemantics)
		{
			Library::Scope scope;

			glm::vec4 vector(1, 1, 1, 1);
			glm::mat4 matrix(vector, vector, vector, vector);
			Library::Scope* childScope = new Library::Scope();

			scope["Int"] = 5;
			scope["Float"] = 5.0f;
			scope["String"] = "Five";
			scope["Vector"] = vector;
			scope["Matrix"] = matrix;
			scope["Scope"] = childScope;

			Assert::IsTrue(scope["Int"] == 5);
			Assert::IsTrue(scope["Float"] == 5.0f);
			Assert::IsTrue(scope["String"] == "Five");
			Assert::IsTrue(scope["Vector"] == vector);
			Assert::IsTrue(scope["Matrix"] == matrix);
			Assert::IsTrue(scope["Scope"] == childScope);

			Assert::IsTrue(scope.Find("Int") != nullptr);
			Assert::IsTrue(scope.Find("Float") != nullptr);
			Assert::IsTrue(scope.Find("String") != nullptr);
			Assert::IsTrue(scope.Find("Vector") != nullptr);
			Assert::IsTrue(scope.Find("Matrix") != nullptr);
			Assert::IsTrue(scope.Find("Scope") != nullptr);

			Library::Scope newScope;

			// New scope shouldn't have these keys yet
			Assert::IsTrue(newScope.Find("Int") == nullptr);
			Assert::IsTrue(newScope.Find("Float") == nullptr);
			Assert::IsTrue(newScope.Find("String") == nullptr);
			Assert::IsTrue(newScope.Find("Vector") == nullptr);
			Assert::IsTrue(newScope.Find("Matrix") == nullptr);
			Assert::IsTrue(newScope.Find("Scope") == nullptr);

			newScope = std::move(scope);

			// Old scope shouldn't find our keys anymore
			Assert::IsTrue(scope.Find("Int") == nullptr);
			Assert::IsTrue(scope.Find("Float") == nullptr);
			Assert::IsTrue(scope.Find("String") == nullptr);
			Assert::IsTrue(scope.Find("Vector") == nullptr);
			Assert::IsTrue(scope.Find("Matrix") == nullptr);
			Assert::IsTrue(scope.Find("Scope") == nullptr);

			// New scope should find our keys now
			Assert::IsTrue(newScope.Find("Int") != nullptr);
			Assert::IsTrue(newScope.Find("Float") != nullptr);
			Assert::IsTrue(newScope.Find("String") != nullptr);
			Assert::IsTrue(newScope.Find("Vector") != nullptr);
			Assert::IsTrue(newScope.Find("Matrix") != nullptr);
			Assert::IsTrue(newScope.Find("Scope") != nullptr);

			// New scope should have the values associated with old scope
			Assert::IsTrue(newScope["Int"] == 5);
			Assert::IsTrue(newScope["Float"] == 5.0f);
			Assert::IsTrue(newScope["String"] == "Five");
			Assert::IsTrue(newScope["Vector"] == vector);
			Assert::IsTrue(newScope["Matrix"] == matrix);
			Assert::IsTrue(newScope["Scope"] == childScope);
		}

		TEST_METHOD(TestFind)
		{
			Library::Scope s1;
			Library::Datum myDatum(Library::DatumType::String);
			myDatum = "Bazooka";
			auto& temp = s1.Append("Weapons");
			temp = myDatum;
			Library::Datum* result = s1.Find("Weapons");
			Assert::IsTrue(*result == myDatum);

			Library::Scope s2;
			Library::Datum myIntDatum(Library::DatumType::Integer);
			myIntDatum = 1337;
			auto& intTemp = s2.Append("Coins");
			intTemp = myIntDatum;
			Library::Datum* intResult = s2.Find("Coins");
			Assert::IsTrue(*intResult == myIntDatum);
		}

		TEST_METHOD(TestSearch)
		{
			Library::Scope scope1;
			auto& scope2 = scope1.AppendScope("Child One");
			auto& scope3 = scope2.AppendScope("Child Two");
			Assert::IsTrue(scope3.Search("Child One") != nullptr);
			Assert::IsTrue(scope2.Search("Child One") != nullptr);
			Assert::IsTrue(scope1.Search("Child One") != nullptr);

			auto& datum1 = scope1.Append("Eggs");
			datum1 = Library::DatumType::Integer;
			datum1 = 10;

			auto& datum2 = scope2.Append("Allies");
			datum2 = Library::DatumType::String;
			datum2 = "Iron Man";

			auto& datum3 = scope3.Append("Velocity");
			datum3 = Library::DatumType::Float;
			datum3 = 12.5f;

			Assert::IsTrue(scope1.Search("NotInMyDangScope") == nullptr);
			Assert::IsTrue(scope2.Search("NotInMyDangScope") == nullptr);
			Assert::IsTrue(scope3.Search("NotInMyDangScope") == nullptr);

			Assert::IsTrue(scope1.Search("Eggs") != nullptr);
			Assert::IsTrue(scope2.Search("Eggs") != nullptr);
			Assert::IsTrue(scope3.Search("Eggs") != nullptr);
			Assert::IsTrue(scope1.Search("Eggs")[0] == 10);
			Assert::IsTrue(scope2.Search("Eggs")[0] == 10);
			Assert::IsTrue(scope3.Search("Eggs")[0] == 10);

			Assert::IsTrue(scope1.Search("Allies") == nullptr);
			Assert::IsTrue(scope2.Search("Allies") != nullptr);
			Assert::IsTrue(scope3.Search("Allies") != nullptr);
			Assert::IsTrue(scope2.Search("Allies")[0] == "Iron Man");
			Assert::IsTrue(scope3.Search("Allies")[0] == "Iron Man");

			Assert::IsTrue(scope1.Search("Velocity") == nullptr);
			Assert::IsTrue(scope2.Search("Velocity") == nullptr);
			Assert::IsTrue(scope3.Search("Velocity") != nullptr);
			Assert::IsTrue(scope3.Search("Velocity")[0] == 12.5f);

			Assert::IsTrue(scope1["Eggs"] == 10);
			Assert::IsTrue(scope2["Allies"] == "Iron Man");
			Assert::IsTrue(scope3["Velocity"] == 12.5f);
		}

		TEST_METHOD(TestAppend)
		{
			Library::Scope scope1;
			auto& datum1 = scope1.Append("New Datum");
			Assert::IsTrue(datum1 != nullptr);
			Assert::IsTrue(datum1 == Library::DatumType::Unknown);
			Assert::IsTrue(datum1.ToString() == "Unknown Type");

			auto& datum2 = scope1.Append("Another Datum");
			Assert::IsTrue(datum1 != nullptr);
			Assert::IsTrue(datum2 != nullptr);
			Assert::IsTrue(datum2 == Library::DatumType::Unknown);
		}

		TEST_METHOD(TestAppendScope)
		{
			Library::Scope s1;
			auto& scope = s1.AppendScope("Scope");
			auto& datum = scope.Append("HandBag");
			datum = Library::DatumType::Integer;
			datum = 5;
			Assert::IsTrue(scope.Search("HandBag") != nullptr);
			Assert::IsTrue(scope.Search("Scope") != nullptr);

			s1.AppendScope("New Scope");
			Assert::IsTrue(scope.Search("HandBag") != nullptr);
			Assert::IsTrue(scope.Search("Scope") != nullptr);
		}

		TEST_METHOD(TestAdopt)
		{
			Library::Scope scope1, scope2;
			Library::Scope& childFromScope1 = scope1.AppendScope("Scope one is my daddy");
			Assert::IsTrue(scope1.Search("Scope one is my daddy") != nullptr);
			Assert::IsTrue(scope2.Search("Scope one is my daddy") == nullptr);
			
			scope2.Adopt(childFromScope1, "Scope two is my new daddy");
			Assert::IsTrue(scope1.Find("Scope one is my daddy") == nullptr);
			Assert::IsTrue(scope2.Find("Scope two is my new daddy") != nullptr);
		}

		TEST_METHOD(TestGetParent)
		{
			Library::Scope scope1;
			Assert::IsTrue(scope1.GetParent() == nullptr);
			
			auto& scope2 = scope1.AppendScope("scope 2");
			Assert::IsTrue(scope2.GetParent() == &scope1);
			Assert::IsTrue(scope1.GetParent() == nullptr);

			auto& scope3 = scope2.AppendScope("scope 3");
			Assert::IsTrue(scope3.GetParent() == &scope2);
			Assert::IsTrue(scope2.GetParent() == &scope1);
			Assert::IsTrue(scope1.GetParent() == nullptr);

			auto& scope2Brother = scope1.AppendScope("Scope 2 brother");
			Assert::IsTrue(scope3.GetParent() == &scope2);
			Assert::IsTrue(scope2.GetParent() == &scope1);
			Assert::IsTrue(scope1.GetParent() == nullptr);
			Assert::IsTrue(scope2Brother.GetParent() == &scope1);
		}

		TEST_METHOD(TestIndexOperator)
		{
			Library::Scope scope1;
			scope1["Eggs"] = Library::DatumType::Integer;
			Assert::IsTrue(scope1.Find("Eggs") != nullptr);
			scope1["Eggs"] = 5;
			Assert::IsTrue(scope1["Eggs"] == 5);

			scope1["Sword"] = Library::DatumType::String;
			Assert::IsTrue(scope1.Find("Sword") != nullptr);
			scope1["Sword"] = "Katana";
			Assert::IsTrue(scope1["Sword"] == "Katana");

			Assert::IsTrue(scope1[0] == scope1["Eggs"]);
			Assert::IsTrue(scope1[1] == scope1["Sword"]);
			Assert::ExpectException<std::exception>([&] { scope1[10]; });
		}

		TEST_METHOD(TestEqualityOperator)
		{
			Library::Scope scope1, scope2;
			Assert::IsTrue(scope1 == scope2);
			Assert::IsFalse(scope1 != scope2);
			
			scope1.AppendScope("New child scope");
			Assert::IsFalse(scope1 == scope2);
			Assert::IsTrue(scope1 != scope2);

			scope2.AppendScope("New child scope");
			Assert::IsTrue(scope1 == scope2);
			Assert::IsFalse(scope1 != scope2);

			scope1.Append("Eggs");
			Assert::IsFalse(scope1 == scope2);
			Assert::IsTrue(scope1 != scope2);

			scope2.Append("Eggs");
			Assert::IsTrue(scope1 == scope2);
			Assert::IsFalse(scope1 != scope2);

			scope1["Eggs"] = Library::DatumType::Integer;
			scope2["Eggs"] = Library::DatumType::Integer;
			Assert::IsTrue(scope1 == scope2);
			Assert::IsFalse(scope1 != scope2);
		}

		TEST_METHOD(TestFindName)
		{
			Library::Scope scope1;
			Assert::ExpectException<std::exception>([&] { scope1.FindName(&scope1); });

			auto& scope2 = scope1.AppendScope("Bananas");
			Assert::IsTrue(scope1.FindName(&scope2) == "Bananas");

			auto& scope3 = scope2.AppendScope("Apples");
			Assert::IsTrue(scope2.FindName(&scope3) == "Apples");
			Assert::IsTrue(scope1.FindName(&scope3) != "Apples");
		}

		TEST_METHOD(TestToString)
		{
			Library::Scope scope;
			Assert::IsTrue(scope.ToString() == "Scope");
		}

		TEST_METHOD(TestRTTI)
		{
			Library::Scope scope1, scope2;
			Assert::IsTrue(scope1.Is(scope2.TypeIdClass()));
			Assert::IsTrue(scope1.ToString() == "Scope");
			auto ptr = scope1.QueryInterface(scope1.TypeIdClass());
			Assert::IsTrue(scope1.Equals(ptr));
		}

//		static _CrtMemState sStartMemState;
	};

//	_CrtMemState ScopeTest::sStartMemState;
}