#include "pch.h"
#include "TestSharedData.h"

namespace Library
{
    RTTI_DEFINITIONS(TestSharedData)

        TestSharedData::TestSharedData() :
        SharedData(), m_name(""), m_health(0), m_mana(0)
    {}

    XmlParseMaster::SharedData* TestSharedData::Clone()
    {
        TestSharedData* clone = new TestSharedData();
        clone->m_name = m_name;
        clone->m_health = m_health;
        clone->m_mana = m_mana;
        return clone;
    }

    std::string TestSharedData::ToString() const
    {
        return "Test Shared Data";
    }

    bool TestSharedData::Equals(const Library::RTTI* rhs) const
    {
        if (dynamic_cast<const Library::RTTI*>(this) == rhs)
        {
            return true;
        }

        TestSharedData* data = rhs->As<TestSharedData>();
        bool result = false;

        if (data != nullptr)
        {
            result =
                (m_name == data->m_name) &&
                (m_health == data->m_health) &&
                (m_mana == data->m_mana);
        }

        return result;
    }
}