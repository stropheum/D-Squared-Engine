#include "pch.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"


namespace Library
{
	RTTI_DEFINITIONS(IXmlParseHelper)

	IXmlParseHelper::IXmlParseHelper(XmlParseMaster* const xmlParseMaster):
		mXmlParseMaster(xmlParseMaster), mValidElementName("")
	{
		if (mXmlParseMaster != nullptr)
		{
			mXmlParseMaster->AddHelper(*this);
		}
	}

	IXmlParseHelper::~IXmlParseHelper()
	{
		if (mXmlParseMaster != nullptr)
		{
			mXmlParseMaster->RemoveHelper(*this);
		}
	}

	void IXmlParseHelper::CharDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t& bufferLength)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(bufferLength);
	}

	std::string IXmlParseHelper::ToString() const
	{
		return "IXmlParseHelper";
	}
}
