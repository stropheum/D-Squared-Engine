#include "pch.h"
#include "StringState.h"


using namespace std;

namespace Library
{
    StringState::StringState(Datum& context) :
        TypeState(context)
    {}

    bool StringState::operator==(const Datum& rhs)
    {
        bool result = false;

        if (m_context.m_type == rhs.m_type && m_context.m_size == rhs.m_size && m_context.m_capacity == rhs.m_capacity)
        {
            result = true;
            for (uint32_t i = 0; i < m_context.m_size; i++)
            {
                if (m_context.m_data.s[i] != rhs.m_data.s[i])
                {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    Datum& StringState::operator=(const string& rhs)
    {
        if (m_context.m_size > 1) { throw exception("Invalid assignment invocation"); }
        if (m_context.m_size == 0) { m_context.SetSize(1); }
        m_context.m_data.s[0] = rhs;
        return m_context;
    }

    void StringState::SetSize(const uint32_t& size)
    {
        if (size < m_context.m_size)
        {
            for (uint32_t i = size; i < m_context.m_size; i++)
            {
                m_context.m_data.s[i].string::~string();
            }
        }

        m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(string) * size);

        if (size > m_context.m_size)
        {	// If our new Size is larger than before, we need to default construct new strings
            for (uint32_t i = m_context.m_size; i < size; i++)
            {	// Use placement new to construct new strings
                new(m_context.m_data.s + i) string("");
            }
        }

        m_context.m_capacity = m_context.m_size = size;
    }

    void StringState::Reserve(const uint32_t& capacity)
    {
        if (capacity > m_context.m_capacity)
        {
            m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(string) * capacity);
            m_context.m_capacity = capacity;
        }
    }

    void StringState::Clear()
    {
        if (m_context.m_size > 0)
        {
            for (uint32_t i = 0; i < m_context.m_size; i++)
            {	// Placement new an empty string onto the array
                m_context.m_data.s[i].string::~string();
            }
            m_context.m_size = 0;
        }
    }

    void StringState::SetFromString(const string& value, const uint32_t& index)
    {   // Strings don't have to be parsed, so they can be passed directly to Set
        m_context.Set(value, index);
    }

    void StringState::SetStorage(const Datum& rhs)
    {
        SetStorage(rhs.m_data.s, rhs.m_size);
    }

    void StringState::SetStorage(string* data, const uint32_t& size)
    {
        assert(m_context.m_type == DatumType::String);

        if (m_context.m_capacity > 0) { Clear(); }

        m_context.m_dataIsExternal = true;
        m_context.m_data.s = data;
        m_context.m_capacity = m_context.m_size = size;
    }

    string StringState::ToString(const uint32_t& index)
    {
        return m_context.Get<string>(index);
    }
}