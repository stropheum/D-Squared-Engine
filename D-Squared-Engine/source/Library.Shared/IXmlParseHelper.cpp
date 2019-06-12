#include "pch.h"
#include "IXmlParseHelper.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(IXmlParseHelper);

    IXmlParseHelper::IXmlParseHelper(XmlParseMaster* const xmlParseMaster) :
        m_xmlParseMaster(xmlParseMaster), 
        m_validElementName("")
    {
        if (m_xmlParseMaster != nullptr)
        {
            m_xmlParseMaster->AddHelper(*this);
        }
    }

    IXmlParseHelper::~IXmlParseHelper()
    {
        if (m_xmlParseMaster != nullptr)
        {
            m_xmlParseMaster->RemoveHelper(*this);
        }
    }

    void IXmlParseHelper::CharDataHandler(
        XmlParseMaster::SharedData& sharedData,
        const string& buffer, 
        const uint32_t& bufferLength)
    {
        UNREFERENCED_PARAMETER(sharedData);
        UNREFERENCED_PARAMETER(buffer);
        UNREFERENCED_PARAMETER(bufferLength);
    }

    string IXmlParseHelper::ToString() const
    {
        return "IXmlParseHelper";
    }
}