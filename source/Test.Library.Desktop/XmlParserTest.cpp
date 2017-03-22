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

		TEST_METHOD(TestParse)
		{
			Library::TestSharedData sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::TestParseHelper helper(&parseMaster);
			sharedData.setXmlParseMaster(&parseMaster);
			parseMaster.addHelper(helper);
			char* xml = "<Person Name='Dale' Health='100' Mana='80' />";
			parseMaster.parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
		}

		TEST_METHOD(TestParseFromFile)
		{
			Library::TestSharedData sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::TestParseHelper helper(&parseMaster);
			sharedData.setXmlParseMaster(&parseMaster);

			parseMaster.addHelper(helper);
			parseMaster.parseFromFile("input.xml");
			Assert::AreEqual(sharedData.mName, static_cast<std::string>("Dale"), L"Name not accurately parsed");
			Assert::AreEqual(sharedData.mHealth, 100, L"Health not accurately parsed");
			Assert::AreEqual(sharedData.mMana, 80, L"Mana value not accurately parsed");
			Assert::AreEqual(sharedData.depth(), 0u, L"Depth not zero at end of parsing");
		}

		TEST_METHOD(TestClone)
		{
			Library::TestSharedData sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::TestParseHelper helper(&parseMaster);
			sharedData.setXmlParseMaster(&parseMaster);

			Library::XmlParseMaster* clone = parseMaster.clone();
			UNREFERENCED_PARAMETER(clone);
			Library::TestSharedData* data = clone->getSharedData()->As<Library::TestSharedData>();
			Assert::AreEqual(data->mName, sharedData.mName);

			delete clone;
		}

		TEST_METHOD(TestRTTI)
		{
			Library::IXmlParseHelper* baseHelper = new Library::TestParseHelper();
			Assert::AreEqual(std::string("IXmlParseHelper"), baseHelper->ToString(), L"ToString yielding improper value");
			
			Library::IXmlParseHelper* baseHelper2 = baseHelper;
			Assert::IsTrue(baseHelper->Equals(baseHelper2));

			Library::IXmlParseHelper* baseHelper3 = new Library::TestParseHelper();
			Assert::IsFalse(baseHelper->Equals(baseHelper3));

			delete baseHelper;
			delete baseHelper3;
			

			Library::TestParseHelper derivedHelper;
			Assert::AreEqual(std::string("IXmlParseHelper"), derivedHelper.ToString(), L"ToString yielding improper value");
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState XmlParserTest::sStartMemState;
}