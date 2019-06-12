#include "pch.h"
#include "IntegerState.h"


using namespace std;

namespace Library
{
    IntegerState::IntegerState(Datum& context) :
        TypeState(context)
    {}

    bool IntegerState::operator==(const Datum& rhs)
    {
        bool result = false;

        if (m_context.m_type == rhs.m_type && m_context.m_size == rhs.m_size)
        {
            result = true;
            for (uint32_t i = 0; i < m_context.m_size; i++)
            {
                if (m_context.m_data.i[i] != rhs.m_data.i[i])
                {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    Datum& IntegerState::operator=(const int32_t& rhs)
    {
        if (m_context.m_size > 1) { throw exception("Invalid assignment invocation"); }
        if (m_context.m_size == 0) { m_context.SetSize(1); }
        m_context.m_data.i[0] = rhs;
        return m_context;
    }


    void IntegerState::SetSize(const uint32_t& size)
    {
        m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(int32_t) * size);
        m_context.m_capacity = m_context.m_size = size;
    }

    void IntegerState::Reserve(const uint32_t& capacity)
    {
        if (capacity > m_context.m_capacity)
        {
            m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(int32_t) * capacity);
            m_context.m_capacity = capacity;
        }
    }

    void IntegerState::Clear()
    {
        if (m_context.m_size > 0)
        {
            for (uint32_t i = 0; i < m_context.m_size; i++) m_context.m_data.i[i] = 0;
            m_context.m_size = 0;
        }
    }

    void IntegerState::SetFromString(const string& value, const uint32_t& index)
    {
        int32_t result = stoi(value);
        m_context.Set(result, index);
    }

    void IntegerState::SetStorage(const Datum& rhs)
    {
        SetStorage(rhs.m_data.i, rhs.m_size);
    }

    void IntegerState::SetStorage(int32_t* data, const uint32_t& size)
    {
        assert(m_context.m_type == DatumType::Integer);

        if (m_context.m_capacity > 0) Clear();

        m_context.m_dataIsExternal = true;
        m_context.m_data.i = data;
        m_context.m_capacity = m_context.m_size = size;
    }

    string IntegerState::ToString(const uint32_t& index)
    {
        char value[50];
        sprintf_s(value, "%d", m_context.Get<int32_t>(index));
        return value;
    }
}