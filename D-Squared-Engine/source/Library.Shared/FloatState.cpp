#include "pch.h"
#include "FloatState.h"


using namespace std;

namespace Library
{
    FloatState::FloatState(Datum& context) :
        TypeState(context)
    {}

    bool FloatState::operator==(const Datum& rhs)
    {
        bool result = false;

        if (m_context.m_type == rhs.m_type && m_context.m_size == rhs.m_size)
        {
            result = true;
            for (uint32_t i = 0; i < m_context.m_size; i++)
            {
                if (m_context.m_data.f[i] != rhs.m_data.f[i])
                {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    Datum& FloatState::operator=(const float& rhs)
    {
        if (m_context.m_size > 1) { throw exception("Invalid assignment invocation"); }
        if (m_context.m_size == 0) { m_context.SetSize(1); }
        m_context.m_data.f[0] = rhs;
        return m_context;
    }

    void FloatState::SetSize(const uint32_t& size)
    {
        m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(float) * size);
        m_context.m_capacity = m_context.m_size = size;
    }

    void FloatState::Reserve(const uint32_t& capacity)
    {
        if (capacity > m_context.m_capacity)
        {
            m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(float) * capacity);
            m_context.m_capacity = capacity;
        }
    }

    void FloatState::Clear()
    {
        if (m_context.m_size > 0)
        {
            for (uint32_t i = 0; i < m_context.m_size; i++) m_context.m_data.f[i] = NULL;
            m_context.m_size = 0;
        }
    }

    void FloatState::SetFromString(const string& value, const uint32_t& index)
    {
        float result;
        sscanf_s(value.c_str(), "%f", &result);
        m_context.Set(result, index);
    }

    void FloatState::SetStorage(const Datum& rhs)
    {
        SetStorage(rhs.m_data.f, rhs.m_size);
    }

    void FloatState::SetStorage(float* data, const uint32_t& size)
    {
        assert(m_context.m_type == DatumType::Float);

        if (m_context.m_capacity > 0)
        {
            Clear();
        }

        m_context.m_dataIsExternal = true;
        m_context.m_data.f = data;
        m_context.m_capacity = m_context.m_size = size;
    }

    string FloatState::ToString(const uint32_t& index)
    {
        char value[50];
        sprintf_s(value, "%f", m_context.Get<float>(index));
        return value;
    }
}