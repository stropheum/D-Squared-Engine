#include "pch.h"
#include "XmlParseHelperEntity.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(XmlParseHelperEntity);

    XmlParseHelperEntity::XmlParseHelperEntity() :
        m_state(State::NotParsing), 
        m_previousState(State::NotParsing), 
        m_actionSubType(), 
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

    void XmlParseHelperEntity::Initialize(XmlParseMaster* const xmlParseMaster)
    {
        m_xmlParseMaster = xmlParseMaster;
    }

    IXmlParseHelper* XmlParseHelperEntity::Clone()
    {
        XmlParseHelperEntity* clone = new XmlParseHelperEntity();

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

    bool XmlParseHelperEntity::StartElementHandler(
        XmlParseMaster::SharedData& sharedData, 
        const string& element,
        const HashMap<string, string> attributes)
    {
        // Store off state to revert once the end element handler has been met
        m_previousState = (
            m_state == State::NotParsing ||
            m_state == State::ParsingWorld ||
            m_state == State::ParsingSector ||
            m_state == State::ParsingEntity)
            ? m_state
            : m_previousState;

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
                assert(attributes.Find("Name") != attributes.End());
                pair<string, string> pair = *attributes.Find("Name");
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
            // Only use this to Set state to start grabbing component vectors
        }

        else if (element == "String")
        {
            m_state = State::ParsingString;
            Datum& datum = scope->Append(attributes.Find("Name")->second);
            datum.SetType(DatumType::String);
            datum.Set(attributes.Find("Value")->second);
        }

        else if (element == "World")
        {
            if (m_state != State::NotParsing || m_scopeHasBeenInitialized)
            {
                throw exception("Already parsing while attempting to parse a mWorld");
            }

            m_state = State::ParsingWorld;
            data->m_scope = new World();
            data->m_scope->As<World>()->SetName(attributes.Find("Name")->second);
            m_scopeHasBeenInitialized = true;
        }

        else if (element == "Sector" || !m_scopeHasBeenInitialized)
        {
            assert(data->m_scope->Is(World::TypeIdClass()));
            if (m_state != State::ParsingWorld)
            {
                throw exception("Attempting to parse a mSector when not in a mWorld");
            }

            m_state = State::ParsingSector;

            World* world = data->m_scope->As<World>();
            Sector* sector = world->CreateSector(attributes.Find("Name")->second);
            data->m_scope = sector;
        }

        else if (element == "Entity" || !m_scopeHasBeenInitialized)
        {
            assert(data->m_scope->Is(Sector::TypeIdClass()));
            if (m_state != State::ParsingSector)
            {
                throw exception("Attempting to parse an mEntity when not in a mSector");
            }

            m_state = State::ParsingEntity;
            string className = attributes.Find("ClassName")->second;
            string instanceName = attributes.Find("InstanceName")->second;

            Sector* sector = data->m_scope->As<Sector>();
            Entity* entity = sector->CreateEntity(className, instanceName);

            data->m_scope = entity;
        }

        else if (element == "Action")
        {
            assert(data->m_scope->Is(Entity::TypeIdClass()) || data->m_scope->Is(Action::TypeIdClass()));
            if (m_state != State::ParsingEntity && m_state != State::ParsingAction)
            {
                throw exception("Attempting to parse an mAction when not in an mEntity");
            }

            m_state = State::ParsingAction;
            string className = attributes.Find("ClassName")->second;
            string instanceName = attributes.Find("InstanceName")->second;

            Action* action = nullptr;

            if (data->m_scope->Is(Entity::TypeIdClass()))
            {
                m_previousState = State::ParsingEntity;
                Entity* entity = data->m_scope->As<Entity>();
                action = entity->CreateAction(className, instanceName);

                if (action->Is(ActionListIf::TypeIdClass()))
                {
                    ActionListIf* actionList = action->As<ActionListIf>();
                    assert(actionList != nullptr);
                    string condition = attributes.Find("Condition")->second;
                    actionList->SetCondition(stoi(condition));
                }
            }

            else if (data->m_scope->Is(Action::TypeIdClass()))
            {
                m_previousState = State::ParsingAction;
                Action* parent = data->m_scope->As<Action>();
                if (parent->Is(ActionListIf::TypeIdClass()))
                {
                    if (instanceName == "Then")
                    {
                        action = parent->As<ActionListIf>()->CreateThenAction(className, instanceName);
                    }
                    else if (instanceName == "Else")
                    {
                        action = parent->As<ActionListIf>()->CreateElseAction(className, instanceName);
                    }
                }

                else if (parent->Is(ActionList::TypeIdClass()))
                {
                    action = parent->As<ActionList>()->CreateAction(className, instanceName);
                }
            }

            data->m_scope = action;
        }

        return true;
    }

    bool XmlParseHelperEntity::EndElementHandler(XmlParseMaster::SharedData& sharedData, const string& element)
    {
        SharedDataScope* data = sharedData.As<SharedDataScope>();

        assert(data->Depth() > 0);
        if (data == nullptr) { return false; }

        if (element == "Integer")
        {
            assert(m_state == State::ParsingInteger);
        }

        else if (element == "Float")
        {
            assert(m_state == State::ParsingFloat);
        }

        else if (element == "Vector")
        {
            assert(m_state == State::ParsingVector || m_state == State::ParsingMatrix);
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

            Datum& datum = data->m_scope->Append(m_matrixName);
            datum.SetType(DatumType::Matrix);
            datum.SetFromString(ss.str());

            m_matrixComponentCount = 0;
            assert(m_state == State::ParsingMatrix);
        }

        else if (element == "String")
        {
            assert(m_state == State::ParsingString);
        }

        else if (element == "World")
        {
            m_previousState = State::NotParsing;
            assert(m_state == State::ParsingWorld);
            assert(data->m_scope->GetParent() == nullptr);
        }

        else if (element == "Sector")
        {
            m_previousState = State::ParsingWorld;
            assert(m_state == State::ParsingSector);
            assert(data->m_scope->GetParent() != nullptr);
            data->m_scope = data->m_scope->GetParent();
        }

        else if (element == "Entity")
        {
            m_previousState = State::ParsingSector;
            assert(m_state == State::ParsingEntity);
            assert(data->m_scope->GetParent() != nullptr);
            data->m_scope = data->m_scope->GetParent();
        }

        else if (element == "Action")
        {
            assert(m_state == State::ParsingAction || m_state == State::ParsingEntity);
            assert(data->m_scope->GetParent() != nullptr);
            if (data->m_scope->GetParent()->Is(Action::TypeIdClass()))
            {
                m_previousState = State::ParsingAction;
            }
            else if (data->m_scope->GetParent()->Is(Entity::TypeIdClass()))
            {
                m_previousState = State::ParsingEntity;
            }
            else
            {
                throw exception("Attempting to enter an invalid state after parsing mAction");
            }
            data->m_scope = data->m_scope->GetParent();
        }

        m_state = m_previousState;
        if (data->Depth() == 0) m_state = State::NotParsing;
        return true;
    }

    string XmlParseHelperEntity::ToString() const
    {
        return "Xml Parse Helper Scope";
    }

    bool XmlParseHelperEntity::Equals(const RTTI* rhs) const
    {
        if (this == rhs) { return true; }
        if (rhs == nullptr) { return false; }

        XmlParseHelperEntity* rhsConverted = rhs->As<XmlParseHelperEntity>();
        return (rhsConverted != nullptr) ? operator==(*rhsConverted) : false;
    }

    bool XmlParseHelperEntity::operator==(const XmlParseHelperEntity& rhs) const
    {
        bool matricesEquivalent = true;
        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++)
            {
                if (m_matrixComponents[i][j] != rhs.m_matrixComponents[i][j])
                {
                    matricesEquivalent = false;
                }
            }
        }

        return	m_xmlParseMaster == rhs.m_xmlParseMaster &&
            m_state == rhs.m_state &&
            matricesEquivalent &&
            m_scopeHasBeenInitialized == rhs.m_scopeHasBeenInitialized;
    }
}