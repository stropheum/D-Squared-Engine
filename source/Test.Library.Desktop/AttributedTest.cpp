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
			Library::AttributedFoo myFoo;
			Assert::IsTrue(myFoo["this"] == &myFoo);
		}

		TEST_METHOD(TestCopySemantics)
		{
			Library::AttributedFoo myFoo_OG;
			myFoo_OG.populate();
			myFoo_OG["External Integer"] = 10;
			myFoo_OG["External Float"] = 10.0f;
			myFoo_OG["External Vector"] = glm::vec4(10);
			myFoo_OG["External Matrix"] = glm::mat4(10);
			myFoo_OG["External String"] = "10";

			Library::AttributedFoo myFoo_CPY(myFoo_OG);
			Assert::IsFalse(myFoo_CPY["External Integer"] == myFoo_OG.i);
			Assert::IsFalse(myFoo_CPY["External Float"] == myFoo_OG.f);
			Assert::IsFalse(myFoo_CPY["External Vector"] == myFoo_OG.v);
			Assert::IsFalse(myFoo_CPY["External Matrix"] == myFoo_OG.m);
			Assert::IsFalse(myFoo_CPY["External String"] == myFoo_OG.s);

			myFoo_CPY.populate();
			Assert::IsTrue(myFoo_CPY["External Integer"] == myFoo_OG.i);
			Assert::IsTrue(myFoo_CPY["External Float"] == myFoo_OG.f);
			Assert::IsTrue(myFoo_CPY["External Vector"] == myFoo_OG.v);
			Assert::IsTrue(myFoo_CPY["External Matrix"] == myFoo_OG.m);
			Assert::IsTrue(myFoo_CPY["External String"] == myFoo_OG.s);
		}

		TEST_METHOD(TestMoveSemantics)
		{
			std::int32_t myInt = 10;
			float myFloat = 10.0f;
			glm::vec4 myVec(10);
			glm::mat4 myMat(10);
			std::string myStr("10");

			Library::AttributedFoo myFoo_OG;
			myFoo_OG.populate();
			myFoo_OG["External Integer"] = myInt;
			myFoo_OG["External Float"] = myFloat;
			myFoo_OG["External Vector"] = myVec;
			myFoo_OG["External Matrix"] = myMat;
			myFoo_OG["External String"] = myStr;

			Library::AttributedFoo myFoo_CPY(myFoo_OG);
			Assert::IsFalse(myFoo_CPY["External Integer"] == myInt);
			Assert::IsFalse(myFoo_CPY["External Float"] == myFloat);
			Assert::IsFalse(myFoo_CPY["External Vector"] == myVec);
			Assert::IsFalse(myFoo_CPY["External Matrix"] == myMat);
			Assert::IsFalse(myFoo_CPY["External String"] == myStr);

			myFoo_CPY.populate();
			Assert::IsFalse(myFoo_CPY["External Integer"] == myInt);
			Assert::IsFalse(myFoo_CPY["External Float"] == myFloat);
			Assert::IsFalse(myFoo_CPY["External Vector"] == myVec);
			Assert::IsFalse(myFoo_CPY["External Matrix"] == myMat);
			Assert::IsFalse(myFoo_CPY["External String"] == myStr);
		}

		TEST_METHOD(TestPopulate)
		{
			Library::AttributedFoo myFoo;
			Assert::IsTrue(myFoo[0] == myFoo["this"]);
			Assert::ExpectException<std::exception>([&] { myFoo[1]; });

			myFoo.populate();
			Assert::IsTrue(myFoo[0] == myFoo["this"]);
			Assert::IsTrue(myFoo["External Integer"] == myFoo.i);
			Assert::IsTrue(myFoo["External Float"] == myFoo.f);
			Assert::IsTrue(myFoo["External Vector"] == myFoo.v);
			Assert::IsTrue(myFoo["External Matrix"] == myFoo.m);
			Assert::IsTrue(myFoo["External String"] == myFoo.s);

			Assert::ExpectException<std::exception>([&] { myFoo[6]; });
		}

		TEST_METHOD(TestIsPrescribedAttribute)
		{
			Library::AttributedFoo myFoo;
			Assert::IsFalse(myFoo.isPrescribedAttribute("External Integer"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("External Float"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("External Vector"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("External Matrix"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("External String"));

			myFoo.populate();
			Assert::IsTrue(myFoo.isPrescribedAttribute("External Integer"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External Float"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External Vector"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External Matrix"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("External String"));
		}

		TEST_METHOD(TestIsAuxiliaryAttribute)
		{
			Library::AttributedFoo myFoo;
			myFoo.populate();
			Assert::IsFalse(myFoo.isAttribute("Nothing"));
			myFoo.appendAuxiliaryAttribute("Nothing");
			Assert::IsTrue(myFoo.isAttribute("Nothing"));
			Assert::IsTrue(myFoo.isAuxiliaryAttribute("Nothing"));
		}

		TEST_METHOD(TestIsAttribute)
		{
			Library::AttributedFoo myFoo;
			Assert::IsTrue(myFoo.isAttribute("this"));
			Assert::IsFalse(myFoo.isAttribute("External Integer"));
			Assert::IsFalse(myFoo.isAttribute("External Float"));
			Assert::IsFalse(myFoo.isAttribute("External Vector"));
			Assert::IsFalse(myFoo.isAttribute("External Matrix"));
			Assert::IsFalse(myFoo.isAttribute("External String"));

			Assert::IsFalse(myFoo.isAttribute("Nonexistent Garbage"));

			myFoo.populate();
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
	};
}