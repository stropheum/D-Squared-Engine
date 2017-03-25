#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "TestParseHelper.h"
#include "TestSharedData.h"
#include "XmlParseHelperScope.h"
#include "SharedDataScope.h"
#include "Scope.h"
#include "Datum.h"
#include <glm/detail/type_vec4.hpp>
#include <glm/mat4x4.hpp>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(XmlParseHelperScopeTest)
	{
	public:

		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
		}

		/// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#if _DEBUG
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

		TEST_METHOD(TestParse)
		{
			Library::SharedDataScope sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::XmlParseHelperScope helper;
			sharedData.setXmlParseMaster(&parseMaster);
			parseMaster.addHelper(helper);
			
			parseMaster.parseFromFile("Grammar.xml");

			Library::Scope scope = *sharedData.mScope;
			Assert::IsTrue(scope["Name"] == "Dale");
			Assert::IsTrue(scope["Health"] == 10);
			Assert::IsTrue(scope["Power"] == 57.3f);
			Assert::IsTrue(scope["Position"] == glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			
			glm::mat4 expectedMatrix(
				1.0f,  2.0f,  3.0f,  4.0f,
				5.0f,  6.0f,  7.0f,  8.0f,
				9.0f,  10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			);
			Assert::IsTrue(scope["MyMatrix"] == expectedMatrix);

			Library::Scope& pets = *scope["Pets"].get<Library::Scope*>(0);
			Assert::IsTrue(pets["Dog"] == "Dozer");
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState XmlParseHelperScopeTest::sStartMemState;
}