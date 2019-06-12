#include "pch.h"
#include "XmlParseMaster.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(XmlParseMaster::SharedData);

    XmlParseMaster::XmlParseMaster(SharedData* const sharedData) :
        m_xmlParser(XML_ParserCreate(nullptr)), 
        m_activeFileName(""),
        m_sharedData(sharedData), 
        m_depth(0), 
        m_clonedInstance(false), 
        m_helpersAreInitialized(false)
    {
        XML_SetUserData(m_xmlParser, m_sharedData);
        XML_SetElementHandler(m_xmlParser, StartElementHandler, EndElementHandler);
        XML_SetCharacterDataHandler(m_xmlParser, CharDataHandler);
    }

    XmlParseMaster::~XmlParseMaster()
    {
        if (m_clonedInstance)
        {
            delete m_sharedData;

            for (uint32_t i = 0; i < m_helpers.Size(); i++)
            {
                delete m_helpers[i];
            }
            m_helpers.Clear();
        }

        XML_ParserFree(m_xmlParser);
    }

    XmlParseMaster* XmlParseMaster::Clone() const
    {
        XmlParseMaster* newParseMaster = new XmlParseMaster(m_sharedData->Clone());
        newParseMaster->m_clonedInstance = true;
        newParseMaster->m_activeFileName = m_activeFileName;

        for (uint32_t i = 0; i < m_helpers.Size(); i++)
        {
            newParseMaster->m_helpers.PushBack(m_helpers[i]->Clone());
        }

        return newParseMaster;
    }

    void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
    {
        m_helpers.PushBack(&helper);
    }

    void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
    {
        m_helpers.Remove(&helper);
    }

    void XmlParseMaster::Parse(char* const xmlData, const uint32_t& length, const bool endOfFile)
    {
        HandleHelperInitialization();
        XML_Parse(m_xmlParser, xmlData, length, endOfFile);
    }

    void XmlParseMaster::ParseFromFile(const string& fileName)
    {
        HandleHelperInitialization();

        m_activeFileName = fileName;
        ifstream input;
        input.open(fileName, ios::binary);
        input.seekg(0, ios::end);
        int32_t length = static_cast<int32_t>(input.tellg());
        input.seekg(ios::beg);

        char* buffer = new char[length];
        input.read(buffer, length);
        input.close();
        Parse(buffer, length, true);
        delete[] buffer;
    }

    const string& XmlParseMaster::GetFileName() const
    {
        return m_activeFileName;
    }

    void XmlParseMaster::SetSharedData(SharedData* const sharedData)
    {
        m_sharedData = sharedData;
    }

    XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
    {
        return m_sharedData;
    }

    void XmlParseMaster::StartElementHandler(void* userData, const XML_Char* name, const XML_Char** atts)
    {
        SharedData* data = static_cast<SharedData*>(userData);

        HashMap<string, string> attributes;

        for (uint32_t i = 0; atts[i]; i += 2)
        {
            string key = atts[i];
            string value = atts[i + 1];
            attributes[key] = value;
        }

        Vector<IXmlParseHelper*>& helpers = data->GetXmlParseMaster()->m_helpers;

        for (uint32_t i = 0; i < helpers.Size(); i++)
        {
            if (helpers[i]->StartElementHandler(*data, name, attributes))
            {
                break;
            }
        }

        data->IncrementDepth();
    }

    void XmlParseMaster::EndElementHandler(void* userData, const XML_Char* name)
    {
        SharedData* data = static_cast<SharedData*>(userData);
        Vector<IXmlParseHelper*>& helpers = data->GetXmlParseMaster()->m_helpers;

        for (uint32_t i = 0; i < helpers.Size(); i++)
        {
            if (helpers[i]->EndElementHandler(*data, name))
            {
                break;
            }
        }

        data->DecrementDepth();
    }

    void XmlParseMaster::CharDataHandler(void* userData, const XML_Char* s, int len)
    {
        SharedData* data = static_cast<SharedData*>(userData);
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(s);
        UNREFERENCED_PARAMETER(len);
    }

    void XmlParseMaster::HandleHelperInitialization()
    {
        if (!m_helpersAreInitialized)
        {
            for (uint32_t i = 0; i < m_helpers.Size(); i++)
            {	// Initialize all Parse helpers so they reflect the correct Parse master
                m_helpers[i]->Initialize(this);
            }
            m_helpersAreInitialized = true;
        }
    }
}