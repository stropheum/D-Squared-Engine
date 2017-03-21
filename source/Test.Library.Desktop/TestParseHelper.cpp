#include "pch.h"
#include "TestParseHelper.h"
#include <winnt.h>


namespace Library
{
	TestParseHelper::TestParseHelper(Library::XmlParseMaster& xmlParseMaster) :
		IXmlParseHelper(xmlParseMaster)
	{
	}

	TestParseHelper::~TestParseHelper()
	{
	}

	bool TestParseHelper::startElementHandler(const std::string& element, const Library::HashMap<std::string, std::string> attributes)
	{
		// TODO: Implement test start element handler
		UNREFERENCED_PARAMETER(element);
		UNREFERENCED_PARAMETER(attributes);
		return false;
	}

	bool TestParseHelper::endElementHandler(const std::string& element)
	{
		// TODO: Implement test start element handler
		UNREFERENCED_PARAMETER(element);
		return false;
	}

	void TestParseHelper::charDataHandler(const std::string& buffer, const std::uint32_t bufferLength)
	{
		// TODO: Implement test start element handler
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(bufferLength);
	}
}
