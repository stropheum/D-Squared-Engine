#include "pch.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"


namespace Library
{
	RTTI_DEFINITIONS(IXmlParseHelper)

	IXmlParseHelper::IXmlParseHelper(XmlParseMaster& xmlParseMaster):
		mXmlParseMaster(xmlParseMaster), mValidElementName("")
	{
		mXmlParseMaster.addHelper(*this);
	}

	IXmlParseHelper::~IXmlParseHelper()
	{
		mXmlParseMaster.removeHelper(*this);
	}

	bool IXmlParseHelper::startElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element, const HashMap<std::string, std::string> attributes)
	{
		UNREFERENCED_PARAMETER(sharedData);
		bool attributesContainsElement = attributes.containsKey(element);

		if (attributesContainsElement)
		{
			// TODO: Handle the element. This should only be done at lower levels though, probably
		}

		return attributesContainsElement;
	}

	bool IXmlParseHelper::endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(element);
		// TODO: Check if this helper can handle the element
		// Check expat documentation for how to implement
		return false;
	}

	void IXmlParseHelper::charDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t bufferLength)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(bufferLength);
		// TODO: Attempt to handle character data
	}

	std::string IXmlParseHelper::ToString() const
	{
		return "IXmlParseHelper";
	}

	bool IXmlParseHelper::Equals(const RTTI* rhs) const
	{
		if (dynamic_cast<const Library::RTTI*>(this) == rhs)
		{
			return true;
		}

		IXmlParseHelper* data = rhs->As<IXmlParseHelper>();
		bool result = false;

		if (data != nullptr)
		{
			result = this == data;
		}

		return result;
	}
}
