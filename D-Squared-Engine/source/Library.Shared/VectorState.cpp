#include "pch.h"
#include "VectorState.h"


using namespace std;

namespace Library
{
    VectorState::VectorState(Datum& context) :
        TypeState(context)
    {}

    bool VectorState::operator==(const Datum& rhs)
    {
        bool result = false;

        if (m_context.m_type == rhs.m_type && m_context.m_size == rhs.m_size)
        {
            result = true;
            for (uint32_t i = 0; i < m_context.m_size; i++)
            {
                if (m_context.m_data.v[i] != rhs.m_data.v[i])
                {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    Datum& VectorState::operator=(const glm::vec4& rhs)
    {
        if (m_context.m_size > 1) { throw exception("Invalid assignment invocation"); }
        if (m_context.m_size == 0) { m_context.SetSize(1); }
        m_context.m_data.v[0] = rhs;
        return m_context;
    }

    void VectorState::SetSize(const uint32_t& size)
    {
        m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(glm::vec4) * size);
        m_context.m_capacity = m_context.m_size = size;
    }

    void VectorState::Reserve(const uint32_t& capacity)
    {
        if (capacity > m_context.m_capacity)
        {
            m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(glm::vec4) * capacity);
            m_context.m_capacity = capacity;
        }
    }

    void VectorState::Clear()
    {
        if (m_context.m_size > 0)
        {
            for (uint32_t i = 0; i < m_context.m_size; i++) m_context.m_data.v[i] = glm::vec4(NULL);
            m_context.m_size = 0;
        }
    }

    void VectorState::SetFromString(const string& value, const uint32_t& index)
    {
        float x;
        float y;
        float z;
        float w;
        sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &x, &y, &z, &w);
        m_context.Set(glm::vec4(x, y, z, w), index);
    }

    void VectorState::SetStorage(const Datum& rhs)
    {
        SetStorage(rhs.m_data.v, rhs.m_size);
    }

    void VectorState::SetStorage(glm::vec4* data, const uint32_t& size)
    {
        assert(m_context.m_type == DatumType::Vector);

        if (m_context.m_capacity > 0) { Clear(); }

        m_context.m_dataIsExternal = true;
        m_context.m_type = DatumType::Vector;
        m_context.m_data.v = data;
        m_context.m_capacity = m_context.m_size = size;
    }

    string VectorState::ToString(const uint32_t& index)
    {
        return glm::to_string(m_context.Get<glm::vec4>(index));
    }
}