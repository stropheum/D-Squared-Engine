#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "TestParseHelper.h"
#include "TestSharedData.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(XmlParserTest)
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

		TEST_METHOD(TestStub)
		{
			Library::TestSharedData* sharedData = new Library::TestSharedData();
			sharedData->clone();
			Library::XmlParseMaster parseMaster(sharedData);
			const char* xmlData = "<Enemy Body='Hot'>";
			parseMaster.parse(xmlData, static_cast<std::uint32_t>(strlen(xmlData)), true);

			delete(sharedData);
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState XmlParserTest::sStartMemState;
}