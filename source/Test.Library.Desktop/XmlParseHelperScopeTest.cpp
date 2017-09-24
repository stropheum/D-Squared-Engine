#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "XmlParseMaster.h"
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
			Library::SharedDataScope sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::XmlParseHelperScope helper;
			sharedData.SetXmlParseMaster(&parseMaster);
			parseMaster.AddHelper(helper);
			
			parseMaster.ParseFromFile("Grammar.xml");

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

			Library::Scope& pets = scope["Pets"].Get<Library::Scope>(0);
			Assert::IsTrue(pets["Dog"] == "Dozer");
		}

		TEST_METHOD(TestEqualityOperator)
		{
			std::string xml1 = "										    \
			<Scope Name='Level 1'>											\
				<Matrix Name = 'MyMatrix'>									\
					<Vector X = '1.0'  Y = '2.0'  Z = '3.0'  W = '4.0' />   \
					<Vector X = '5.0'  Y = '6.0'  Z = '7.0'  W = '8.0' />	\
					<Vector X = '9.0'  Y = '10.0' Z = '11.0' W = '12.0' />	\
					<Vector X = '13.0' Y = '14.0' Z = '15.0' W = '16.0' />	\
				</Matrix>													\
			</Scope>														\\";

			std::string xml2 = "										      \
			<Scope Name='Level 1'>											  \
				<Matrix Name = 'MyMatrix'>									  \
					<Vector X = '11.0'  Y = '12.0'  Z = '13.0'  W = '14.0' /> \
					<Vector X = '15.0'  Y = '16.0'  Z = '17.0'  W = '18.0' /> \
					<Vector X = '19.0'  Y = '20.0' Z = '21.0' W = '22.0' />	  \
					<Vector X = '23.0' Y = '24.0' Z = '25.0' W = '26.0' />	  \
				</Matrix>													  \
			</Scope>														  \\";

			Library::SharedDataScope sharedData1, sharedData2;
			Library::XmlParseMaster parseMaster1(&sharedData1);
			Library::XmlParseMaster parseMaster2(&sharedData2);
			Library::XmlParseHelperScope helper1, helper2;
			
			sharedData1.SetXmlParseMaster(&parseMaster1);
			parseMaster1.AddHelper(helper1);

			sharedData2.SetXmlParseMaster(&parseMaster2);
			parseMaster2.AddHelper(helper2);

			parseMaster1.Parse(const_cast<char*>(xml1.c_str()), static_cast<std::uint32_t>(xml1.length()), true);
			parseMaster2.Parse(const_cast<char*>(xml2.c_str()), static_cast<std::uint32_t>(xml1.length()), true);

			Assert::IsFalse(helper1 == helper2);
		}

		TEST_METHOD(TestHelperRTTI)
		{
			Library::SharedDataScope data;
			Library::XmlParseHelperScope helper1, helper2;
			Assert::IsFalse(helper1.Equals(&helper2));
			Assert::IsTrue(helper1 == helper1);
			Assert::IsTrue(helper1 == helper2);

			Library::XmlParseMaster master(&data);
			helper1.Initialize(&master);
			Assert::IsFalse(helper1.Equals(&helper2));

			helper2.Initialize(&master);
			Assert::IsFalse(helper1.Equals(&helper2));

			auto val = helper1.ToString();
			Assert::IsTrue(val == helper2.ToString());
		}

		TEST_METHOD(TestHelperClone)
		{
			Library::XmlParseHelperScope helperOG;
			Library::IXmlParseHelper* helperClone = nullptr;
			Assert::IsFalse(helperOG.Equals(helperClone));

			helperClone = helperOG.Clone();
			Assert::IsFalse(helperOG.Equals(helperClone));

			Library::SharedDataScope sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			sharedData.SetXmlParseMaster(&parseMaster);
			parseMaster.AddHelper(helperOG);

			parseMaster.ParseFromFile("Grammar.xml");

			Assert::IsFalse(helperOG.Equals(helperClone));

			delete helperClone;
		}

		TEST_METHOD(TestDataClone)
		{
			Library::XmlParseHelperScope helper;

			Library::SharedDataScope sharedData;
			Library::XmlParseMaster::SharedData* sharedDataClone = nullptr;
			Assert::IsFalse(sharedData.Equals(sharedDataClone));

			sharedDataClone = sharedData.Clone();
			Assert::IsTrue(sharedData.Equals(sharedDataClone));

			Library::XmlParseMaster parseMaster(&sharedData);
			sharedData.SetXmlParseMaster(&parseMaster);
			parseMaster.AddHelper(helper);

			parseMaster.ParseFromFile("Grammar.xml");
			Assert::IsFalse(sharedData.Equals(sharedDataClone));

			delete sharedDataClone;
			sharedDataClone = sharedData.Clone();
			Assert::IsTrue(sharedData.Equals(sharedDataClone));
			delete sharedDataClone;
		}

		TEST_METHOD(TestDataRTTI)
		{
			Library::SharedDataScope data1, data2;
			Assert::IsTrue(data1.Equals(&data1) && data2.Equals(&data2));
			Assert::IsTrue(data1.Equals(&data2));
			Assert::IsTrue(data1.ToString() == "Shared Data Scope" &&
				data1.ToString() == data2.ToString());

			Library::XmlParseMaster parseMaster(&data1);
			Library::XmlParseHelperScope helper;
			data1.SetXmlParseMaster(&parseMaster);
			parseMaster.AddHelper(helper);

			parseMaster.ParseFromFile("Grammar.xml");
			Assert::IsFalse(data1.Equals(&data2));

			Library::XmlParseMaster parseMaster2(&data2);
			Library::XmlParseHelperScope helper2;
			data2.SetXmlParseMaster(&parseMaster2);
			parseMaster2.AddHelper(helper2);

			parseMaster2.ParseFromFile("Grammar.xml");
			Assert::IsTrue(data1.Equals(&data2));
			
			Library::Scope& scope1 = *data1.mScope;
			Library::Scope& scope2 = *data2.mScope;
			Assert::IsTrue(scope1["Name"] == "Dale" && scope2["Name"] == "Dale");
		}

	};

}