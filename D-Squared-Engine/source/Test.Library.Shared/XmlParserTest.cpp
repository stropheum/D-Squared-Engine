#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "XmlParseMaster.h"
#include "TestParseHelper.h"
#include "TestSharedData.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
    TEST_CLASS(XmlParserTest)
    {

    public:

        TEST_METHOD_INITIALIZE(InitializeMethod)
        {
            LeakDetector::Initialize();
        }

        TEST_METHOD_CLEANUP(CleanupMethod)
        {
            LeakDetector::Finalize();
        }

        TEST_METHOD(TestParse)
        {
            Library::TestSharedData sharedData;
            Library::XmlParseMaster parseMaster(&sharedData);
            Library::TestParseHelper helper(&parseMaster);
            sharedData.SetXmlParseMaster(&parseMaster);
            parseMaster.AddHelper(helper);
            char* xml = "<Person Name='Dale' Health='100' Mana='80' />";
            parseMaster.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
        }

        TEST_METHOD(TestParseFromFile)
        {
            Library::TestSharedData sharedData;
            Library::XmlParseMaster parseMaster(&sharedData);
            Library::TestParseHelper helper(&parseMaster);
            sharedData.SetXmlParseMaster(&parseMaster);

            parseMaster.AddHelper(helper);
            parseMaster.ParseFromFile("input.xml");
            Assert::AreEqual(static_cast<std::string>("Dale"), sharedData.m_name, L"Name not accurately parsed");
            Assert::AreEqual(sharedData.m_health, 100, L"Health not accurately parsed");
            Assert::AreEqual(sharedData.m_mana, 80, L"Mana value not accurately parsed");
            Assert::AreEqual(sharedData.Depth(), 0u, L"Depth not zero at end of parsing");
        }

        TEST_METHOD(TestClone)
        {
            Library::TestSharedData sharedData;
            Library::XmlParseMaster parseMaster(&sharedData);
            Library::TestParseHelper helper(&parseMaster);
            sharedData.SetXmlParseMaster(&parseMaster);

            Library::XmlParseMaster* clone = parseMaster.Clone();
            UNREFERENCED_PARAMETER(clone);
            Library::TestSharedData* data = clone->GetSharedData()->As<Library::TestSharedData>();
            Assert::AreEqual(data->m_name, sharedData.m_name);

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

    };

}