#include "pch.h"
#include "TestParseHelper.h"
#include <winnt.h>
#include "TestSharedData.h"


namespace Library
{
	RTTI_DEFINITIONS(TestParseHelper)

	TestParseHelper::TestParseHelper(Library::XmlParseMaster& xmlParseMaster) :
		IXmlParseHelper(xmlParseMaster)
	{
	}

	TestParseHelper::~TestParseHelper()
	{
	}

	void TestParseHelper::initialize()
	{
		// TODO: Initialize the parse helper
	}

	bool TestParseHelper::startElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element, const Library::HashMap<std::string, std::string> attributes)
	{
		TestSharedData* data = dynamic_cast<TestSharedData*>(&sharedData);
		bool castSuccessful = (data != nullptr) && element == "Person";

		if (castSuccessful)
		{
			data->mHealth = std::stoi((*attributes.find("Health")).second);
			return true;
		}
		
		return false;
	}

	bool TestParseHelper::endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element)
	{
		UNREFERENCED_PARAMETER(sharedData);
		// TODO: Implement test start element handler
		UNREFERENCED_PARAMETER(element);
		return false;
	}

	void TestParseHelper::charDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t bufferLength)
	{
		// TODO: Implement test start element handler
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(bufferLength);
	}

	IXmlParseHelper* TestParseHelper::clone()
	{
		return this;
	}
}
