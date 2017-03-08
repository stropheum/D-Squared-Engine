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
			myFoo_OG["Internal Integer"] = 10;
			myFoo_OG["Internal Float"] = 10.0f;
			myFoo_OG["Internal Vector"] = glm::vec4(10);
			myFoo_OG["Internal Matrix"] = glm::mat4(10);
			myFoo_OG["Internal String"] = "10";

			Library::AttributedFoo myFoo_CPY(myFoo_OG);
			Assert::IsFalse(myFoo_CPY["Internal Integer"] == myFoo_OG.i);
			Assert::IsFalse(myFoo_CPY["Internal Float"] == myFoo_OG.f);
			Assert::IsFalse(myFoo_CPY["Internal Vector"] == myFoo_OG.v);
			Assert::IsFalse(myFoo_CPY["Internal Matrix"] == myFoo_OG.m);
			Assert::IsFalse(myFoo_CPY["Internal String"] == myFoo_OG.s);

			myFoo_CPY.populate();
			Assert::IsTrue(myFoo_CPY["Internal Integer"] == myFoo_OG.i);
			Assert::IsTrue(myFoo_CPY["Internal Float"] == myFoo_OG.f);
			Assert::IsTrue(myFoo_CPY["Internal Vector"] == myFoo_OG.v);
			Assert::IsTrue(myFoo_CPY["Internal Matrix"] == myFoo_OG.m);
			Assert::IsTrue(myFoo_CPY["Internal String"] == myFoo_OG.s);
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
			myFoo_OG["Internal Integer"] = myInt;
			myFoo_OG["Internal Float"] = myFloat;
			myFoo_OG["Internal Vector"] = myVec;
			myFoo_OG["Internal Matrix"] = myMat;
			myFoo_OG["Internal String"] = myStr;

			Library::AttributedFoo myFoo_CPY(myFoo_OG);
			Assert::IsFalse(myFoo_CPY["Internal Integer"] == myInt);
			Assert::IsFalse(myFoo_CPY["Internal Float"] == myFloat);
			Assert::IsFalse(myFoo_CPY["Internal Vector"] == myVec);
			Assert::IsFalse(myFoo_CPY["Internal Matrix"] == myMat);
			Assert::IsFalse(myFoo_CPY["Internal String"] == myStr);

			myFoo_CPY.populate();
			Assert::IsFalse(myFoo_CPY["Internal Integer"] == myInt);
			Assert::IsFalse(myFoo_CPY["Internal Float"] == myFloat);
			Assert::IsFalse(myFoo_CPY["Internal Vector"] == myVec);
			Assert::IsFalse(myFoo_CPY["Internal Matrix"] == myMat);
			Assert::IsFalse(myFoo_CPY["Internal String"] == myStr);
		}

		TEST_METHOD(TestPopulate)
		{
			Library::AttributedFoo myFoo;
			Assert::IsTrue(myFoo[0] == myFoo["this"]);
			Assert::ExpectException<std::exception>([&] { myFoo[1]; });

			myFoo.populate();
			Assert::IsTrue(myFoo[0] == myFoo["this"]);
			Assert::IsTrue(myFoo["Internal Integer"] == myFoo.i);
			Assert::IsTrue(myFoo["Internal Float"] == myFoo.f);
			Assert::IsTrue(myFoo["Internal Vector"] == myFoo.v);
			Assert::IsTrue(myFoo["Internal Matrix"] == myFoo.m);
			Assert::IsTrue(myFoo["Internal String"] == myFoo.s);

			Assert::ExpectException<std::exception>([&] { myFoo[6]; });
		}

		TEST_METHOD(TestIsPrescribedAttribute)
		{
			Library::AttributedFoo myFoo;
			Assert::IsFalse(myFoo.isPrescribedAttribute("Internal Integer"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("Internal Float"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("Internal Vector"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("Internal Matrix"));
			Assert::IsFalse(myFoo.isPrescribedAttribute("Internal String"));

			myFoo.populate();
			Assert::IsTrue(myFoo.isPrescribedAttribute("Internal Integer"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("Internal Float"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("Internal Vector"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("Internal Matrix"));
			Assert::IsTrue(myFoo.isPrescribedAttribute("Internal String"));
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
			Assert::IsFalse(myFoo.isAttribute("Internal Integer"));
			Assert::IsFalse(myFoo.isAttribute("Internal Float"));
			Assert::IsFalse(myFoo.isAttribute("Internal Vector"));
			Assert::IsFalse(myFoo.isAttribute("Internal Matrix"));
			Assert::IsFalse(myFoo.isAttribute("Internal String"));

			Assert::IsFalse(myFoo.isAttribute("Nonexistent Garbage"));

			myFoo.populate();
			Assert::IsTrue(myFoo.isAttribute("this"));
			Assert::IsTrue(myFoo.isAttribute("Internal Integer"));
			Assert::IsTrue(myFoo.isAttribute("Internal Float"));
			Assert::IsTrue(myFoo.isAttribute("Internal Vector"));
			Assert::IsTrue(myFoo.isAttribute("Internal Matrix"));
			Assert::IsTrue(myFoo.isAttribute("Internal String"));

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