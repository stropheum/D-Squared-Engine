#include "pch.h"
#include "XmlParseHelperScope.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(XmlParseHelperScope);

    XmlParseHelperScope::XmlParseHelperScope() :
        m_state(State::NotParsing), 
        m_matrixName(""), 
        m_matrixComponentCount(0), 
        m_scopeHasBeenInitialized(false)
    {
        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++)
            {
                m_matrixComponents[i][j] = "";
            }
        }
    }

    void XmlParseHelperScope::Initialize(XmlParseMaster* const xmlParseMaster)
    {
        m_xmlParseMaster = xmlParseMaster;
    }

    IXmlParseHelper* XmlParseHelperScope::Clone()
    {
        XmlParseHelperScope* clone = new XmlParseHelperScope();

        clone->m_state = m_state;
        clone->m_matrixComponentCount = m_matrixComponentCount;
        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++)
            {
                clone->m_matrixComponents[i][j] = m_matrixComponents[i][j];
            }
        }

        return clone;
    }

    bool XmlParseHelperScope::StartElementHandler(
        XmlParseMaster::SharedData& sharedData, 
        const string& element,
        const HashMap<string, string> attributes)
    {
        SharedDataScope* data = sharedData.As<SharedDataScope>();
        if (data == nullptr) { return false; }
        Scope* scope = data->m_scope;

        if (element == "Integer")
        {
            m_state = State::ParsingInteger;
            Datum& datum = scope->Append(attributes.Find("Name")->second);
            datum.SetType(DatumType::Integer);
            datum.SetFromString(attributes.Find("Value")->second);
        }
        else if (element == "Float")
        {
            m_state = State::ParsingFloat;
            Datum& datum = scope->Append(attributes.Find("Name")->second);
            datum.SetType(DatumType::Float);
            datum.SetFromString(attributes.Find("Value")->second);
        }
        else if (element == "Vector")
        {
            m_state = (m_state == State::ParsingMatrix) ? State::ParsingMatrix : State::ParsingVector;

            string x = attributes.Find("X")->second;
            string y = attributes.Find("Y")->second;
            string z = attributes.Find("Z")->second;
            string w = attributes.Find("W")->second;

            if (m_state == State::ParsingVector)
            {
                Datum& datum = scope->Append(attributes.Find("Name")->second);
                datum.SetType(DatumType::Vector);

                stringstream ss;
                ss << "vec4(" << x << ", " << y << ", " << z << ", " << w << ")";
                datum.SetFromString(ss.str());
            }
            else if (m_state == State::ParsingMatrix)
            {
                m_matrixComponents[m_matrixComponentCount][0] = x;
                m_matrixComponents[m_matrixComponentCount][1] = y;
                m_matrixComponents[m_matrixComponentCount][2] = z;
                m_matrixComponents[m_matrixComponentCount][3] = w;

                m_matrixComponentCount++;
                assert(m_matrixComponentCount <= 4);
            }
        }
        else if (element == "Matrix")
        {
            m_state = State::ParsingMatrix;
            m_matrixName = attributes.Find("Name")->second;
            scope->Append(m_matrixName);
        }
        else if (element == "String")
        {
            m_state = State::ParsingString;
            Datum& datum = scope->Append(attributes.Find("Name")->second);
            datum.SetType(DatumType::String);
            datum.Set(attributes.Find("Value")->second);
        }
        else if (element == "Scope")
        {
            m_state = State::ParsingScope;

            if (!m_scopeHasBeenInitialized)
            {
                data->m_scope = new Scope();
                m_scopeHasBeenInitialized = true;
            }
            else
            {
                Scope& newScope = scope->AppendScope(attributes.Find("Name")->second);
                data->m_scope = &newScope; // Scope becomes the newly appended scope until we're done adding to it
            }
        }

        return true;
    }

    bool XmlParseHelperScope::EndElementHandler(XmlParseMaster::SharedData& sharedData, const string& element)
    {
        SharedDataScope* data = sharedData.As<SharedDataScope>();

        assert(data->Depth() > 0);
        if (data == nullptr) { return false; }

        if (element == "Integer")
        {
            assert(m_state == State::ParsingInteger);
            m_state = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
        }

        else if (element == "Float")
        {
            assert(m_state == State::ParsingFloat);
            m_state = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
        }

        else if (element == "Vector")
        {
            assert(m_state == State::ParsingVector || m_state == State::ParsingMatrix);
            if (data->Depth() > 0)
            {
                if (m_state != State::ParsingMatrix)
                {
                    m_state = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
                }
            }
        }

        else if (element == "Matrix")
        {
            assert(m_matrixComponentCount == 4);
            stringstream ss;

            // String format: mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))
            ss << "mat4x4(";
            for (uint32_t i = 0; i < 4; i++)
            {
                ss << "(";
                for (uint32_t j = 0; j < 4; j++)
                {
                    ss << m_matrixComponents[i][j];
                    if (j < 3)
                    {	// Append commas in the first three elements of the row
                        ss << ",";
                    }
                }
                ss << ")";
                if (i < 3)
                {	// Append commas in the first three rows of the matrix
                    ss << ",";
                }
            }
            ss << ")";

            // We added this on the start element handler, so finding should always work
            assert(data->m_scope->Find(m_matrixName) != nullptr);
            Datum& datum = *data->m_scope->Find(m_matrixName);
            datum.SetType(DatumType::Matrix);
            datum.SetFromString(ss.str());

            m_matrixComponentCount = 0;
            assert(m_state == State::ParsingMatrix);
            m_state = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
        }

        else if (element == "String")
        {
            assert(m_state == State::ParsingString);
            m_state = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
        }

        else if (element == "Scope")
        {	// We're done At this level, so jump up one
            if (data->Depth() > 1)
            {
                data->m_scope = data->m_scope->GetParent();
            }

            assert(m_state == State::ParsingScope);
            m_state = (data->Depth() > 1) ? State::ParsingScope : State::NotParsing;
        }

        if (data->Depth() == 0) m_state = State::NotParsing;
        return true;
    }

    bool XmlParseHelperScope::operator==(const XmlParseHelperScope& rhs) const
    {
        bool matricesEquivalent = true;

        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++)
            {
                if (m_matrixComponents[i][j] != rhs.m_matrixComponents[i][j])
                {
                    matricesEquivalent = false;
                    break;
                }
            }

            if (!matricesEquivalent)
            {
                break;
            }
        }

        return	m_xmlParseMaster == rhs.m_xmlParseMaster &&
            m_state == rhs.m_state &&
            matricesEquivalent &&
            m_scopeHasBeenInitialized == rhs.m_scopeHasBeenInitialized;
    }
}