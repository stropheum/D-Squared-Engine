#include "pch.h"
#include "TestParseHelper.h"
#include <winnt.h>
#include "TestSharedData.h"


namespace Library
{
	RTTI_DEFINITIONS(TestParseHelper)

	TestParseHelper::TestParseHelper(Library::XmlParseMaster* xmlParseMaster) :
		IXmlParseHelper(xmlParseMaster)
	{
	}

	void TestParseHelper::initialize(XmlParseMaster* const xmlParseMaster)
	{
		mXmlParseMaster = xmlParseMaster;
	}

	bool TestParseHelper::startElementHandler(XmlParseMaster::SharedData& sharedData, 
		const std::string& element, const Library::HashMap<std::string, std::string> attributes)
	{
		TestSharedData* data = sharedData.As<TestSharedData>();

		if (data != nullptr && element == "Person")
		{
			data->mName = (*attributes.find("Name")).second;
			data->mHealth = std::stoi((*attributes.find("Health")).second);
			data->mMana = std::stoi((*attributes.find("Mana")).second);
			return true;
		}
		
		return false;
	}

	bool TestParseHelper::endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(element);
		return false;
	}

	void TestParseHelper::charDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t bufferLength)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(bufferLength);
	}

	IXmlParseHelper* TestParseHelper::clone()
	{
		return new TestParseHelper();
	}
}
