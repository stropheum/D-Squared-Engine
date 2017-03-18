#include "pch.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"


namespace Library
{
	IXmlParseHelper::IXmlParseHelper(XmlParseMaster& xmlParseMaster):
		mXmlParseMaster(xmlParseMaster), mValidElementName("")
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
		bool attributesContainsElement = attributes.containsKey(element);

		if (attributesContainsElement)
		{
			// TODO: Handle the element. This should only be done at lower levels though, probably
		}

		return attributesContainsElement;
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
