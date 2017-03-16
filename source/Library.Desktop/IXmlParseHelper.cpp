#include "pch.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"


namespace Library
{
	IXmlParseHelper::IXmlParseHelper(XmlParseMaster& xmlParseMaster):
		mXmlParseMaster(xmlParseMaster)
	{
		mXmlParseMaster.addHelper(*this);
	}

	IXmlParseHelper::~IXmlParseHelper()
	{
		mXmlParseMaster.removeHelper(*this);
	}

	void IXmlParseHelper::initialize()
	{
		// TODO: Implement base level init functionality
	}

	bool IXmlParseHelper::startElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes)
	{
		UNREFERENCED_PARAMETER(element);
		UNREFERENCED_PARAMETER(attributes);
		// TODO: Check if this helper can handle the element
		return false;
	}

	bool IXmlParseHelper::endElementHandler(const std::string& element)
	{
		UNREFERENCED_PARAMETER(element);
		// TODO: Check if this helper can handle the element
		// Check expat documentation for how to implement
		return false;
	}

	void IXmlParseHelper::charDataHandler(const std::string& buffer, const std::uint32_t length)
	{
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(length);
		// TODO: Attempt to handle character data
	}
}
