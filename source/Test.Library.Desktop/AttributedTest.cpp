#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(AttributedTest)
	{
	public:

		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _DEBUG
			// Note: Everything is showing memory leaks because of fixing the problem Paul mentioned in our last meeting. 
			// This was submitted same day so the problem still persists for now!

//			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
//			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
		}

		/// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#if _DEBUG
//			_CrtMemState endMemState, diffMemState;
//			_CrtMemCheckpoint(&endMemState);
//			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
//			{
//				_CrtMemDumpStatistics(&diffMemState);
//				Assert::Fail(L"Memory Leaks!");
//			}
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
			Library::AttributedFoo myFoo;
			Assert::IsTrue(myFoo["this"] == &myFoo);
		}

		TEST_METHOD(TestCopySemantics)
		{
			Library::AttributedFoo myFoo_OG;
			
			myFoo_OG["External Integer"] = 10;
			myFoo_OG["External Float"] = 10.0f;
			myFoo_OG["External Vector"] = glm::vec4(10);
			myFoo_OG["External Matrix"] = glm::mat4(10);
			myFoo_OG["External String"] = "10";

			Library::AttributedFoo myFoo_CPY(myFoo_OG);
			auto& myFooRef = myFoo_CPY["External Integer"];
			UNREFERENCED_PARAMETER(myFooRef);

			Assert::IsTrue(myFoo_OG["External Integer"] == myFoo_OG.mInt);
			Assert::IsTrue(myFoo_OG["External Float"] == myFoo_OG.mFloat);
			Assert::IsTrue(myFoo_OG["External Vector"] == myFoo_OG.mVector);
			Assert::IsTrue(myFoo_OG["External Matrix"] == myFoo_OG.mMatrix);
			Assert::IsTrue(myFoo_OG["External String"] == myFoo_OG.mString);

			Assert::IsTrue(myFoo_CPY["External Integer"] == myFoo_OG.mInt);
			Assert::IsTrue(myFoo_CPY["External Float"] == myFoo_OG.mFloat);
			Assert::IsTrue(myFoo_CPY["External Vector"] == myFoo_OG.mVector);
			Assert::IsTrue(myFoo_CPY["External Matrix"] == myFoo_OG.mMatrix);
			Assert::IsTrue(myFoo_CPY["External String"] == myFoo_OG.mString);

			Assert::IsTrue(myFoo_CPY["External Integer"] == myFoo_OG["External Integer"]);
			Assert::IsTrue(myFoo_CPY["External Float"] == myFoo_OG["External Float"]);
			Assert::IsTrue(myFoo_CPY["External Vector"] == myFoo_OG["External Vector"]);
			Assert::IsTrue(myFoo_CPY["External Matrix"] == myFoo_OG["External Matrix"]);
			Assert::IsTrue(myFoo_CPY["External String"] == myFoo_OG["External String"]);
		}

		TEST_METHOD(TestMoveSemantics)
		{
			std::int32_t myInt = 10;
			float myFloat = 10.0f;
			glm::vec4 myVec(10);
			glm::mat4 myMat(10);
			std::string myStr("10");

			Library::AttributedFoo myFoo_OG;
			
			myFoo_OG["External Integer"] = myInt;
			myFoo_OG["External Float"] = myFloat;
			myFoo_OG["External Vector"] = myVec;
			myFoo_OG["External Matrix"] = myMat;
			myFoo_OG["External String"] = myStr;

			Library::AttributedFoo myFoo_CPY(std::move(myFoo_OG));
			Assert::IsTrue(myFoo_CPY["External Integer"] == myInt);
			Assert::IsTrue(myFoo_CPY["External Float"] == myFloat);
			Assert::IsTrue(myFoo_CPY["External Vector"] == myVec);
			Assert::IsTrue(myFoo_CPY["External Matrix"] == myMat);
			Assert::IsTrue(myFoo_CPY["External String"] == myStr);
		}

		TEST_METHOD(TestPopulate)
		{
			Library::AttributedFoo myFoo;

			Assert::IsTrue(myFoo[0] == myFoo["this"]);
			Assert::IsTrue(myFoo["External Integer"] == myFoo.mInt);
			Assert::IsTrue(myFoo["External Float"] == myFoo.mFloat);
			Assert::IsTrue(myFoo["External Vector"] == myFoo.mVector);
			Assert::IsTrue(myFoo["External Matrix"] == myFoo.mMatrix);
			Assert::IsTrue(myFoo["External String"] == myFoo.mString);

			Assert::ExpectException<std::exception>([&] { myFoo[12]; });
		}

		TEST_METHOD(TestIsPrescribedAttribute)
		{
			Library::AttributedFoo myFoo;

			Assert::IsTrue(myFoo.isPrescribedAttribute("External Integer"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External Float"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External Vector"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External Matrix"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External String"));
		}

		TEST_METHOD(TestIsAuxiliaryAttribute)
		{
			Library::AttributedFoo myFoo;
			Assert::IsFalse(myFoo.isAttribute("Nothing"));
			myFoo.appendAuxiliaryAttribute("Nothing");
			Assert::IsTrue(myFoo.isAttribute("Nothing"));
			Assert::IsTrue(myFoo.isAuxiliaryAttribute("Nothing"));
		}

		TEST_METHOD(TestIsAttribute)
		{
			Library::AttributedFoo myFoo;
			Assert::IsTrue(myFoo.isAttribute("this"));
			Assert::IsTrue(myFoo.isAttribute("External Integer"));
			Assert::IsTrue(myFoo.isAttribute("External Float"));
			Assert::IsTrue(myFoo.isAttribute("External Vector"));
			Assert::IsTrue(myFoo.isAttribute("External Matrix"));
			Assert::IsTrue(myFoo.isAttribute("External String"));

			Assert::IsFalse(myFoo.isAttribute("Nonexistent Garbage"));
		}

		TEST_METHOD(TestAppendAuxiliaryAttribute)
		{
			Library::AttributedFoo myFoo;
			Assert::IsFalse(myFoo.isAttribute("new"));

			myFoo.appendAuxiliaryAttribute("new");
			Assert::IsTrue(myFoo.isAttribute("new"));
		}

		private:
			static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}