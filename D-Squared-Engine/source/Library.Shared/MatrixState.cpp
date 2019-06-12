#include "pch.h"
#include "MatrixState.h"


using namespace std;

namespace Library
{
    MatrixState::MatrixState(Datum& context) :
        TypeState(context)
    {}

    bool MatrixState::operator==(const Datum& rhs)
    {
        bool result = false;

        if (m_context.m_type == rhs.m_type && m_context.m_size == rhs.m_size)
        {
            result = true;
            for (uint32_t i = 0; i < m_context.m_size; i++)
            {
                if (m_context.m_data.m[i] != rhs.m_data.m[i])
                {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    Datum& MatrixState::operator=(const glm::mat4x4& rhs)
    {
        if (m_context.m_size > 1) { throw exception("Invalid assignment invocation"); }
        if (m_context.m_size == 0) { m_context.SetSize(1); }
        m_context.m_data.m[0] = rhs;
        return m_context;
    }

    void MatrixState::SetSize(const uint32_t& size)
    {
        m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(glm::mat4x4) * size);
        m_context.m_capacity = m_context.m_size = size;
    }

    void MatrixState::Reserve(const uint32_t& capacity)
    {
        if (capacity > m_context.m_capacity)
        {
            m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(glm::mat4x4) * capacity);
            m_context.m_capacity = capacity;
        }
    }

    void MatrixState::Clear()
    {
        if (m_context.m_size > 0)
        {
            for (uint32_t i = 0; i < m_context.m_size; i++) m_context.m_data.m[i] = glm::mat4x4(0);
            m_context.m_size = 0;
        }
    }

    void MatrixState::SetFromString(const string& value, const uint32_t& index)
    {
        float x1, y1, z1, w1;
        float x2, y2, z2, w2;
        float x3, y3, z3, w3;
        float x4, y4, z4, w4;

        sscanf_s(value.c_str(),
            "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
            &x1, &y1, &z1, &w1,
            &x2, &y2, &z2, &w2,
            &x3, &y3, &z3, &w3,
            &x4, &y4, &z4, &w4);

        m_context.Set(glm::mat4x4(
            x1, y1, z1, w1,
            x2, y2, z2, w2,
            x3, y3, z3, w3,
            x4, y4, z4, w4), index);
    }

    void MatrixState::SetStorage(const Datum& rhs)
    {
        SetStorage(rhs.m_data.m, rhs.m_size);
    }

    void MatrixState::SetStorage(glm::mat4x4* data, const uint32_t& size)
    {
        assert(m_context.m_type == DatumType::Matrix);

        if (m_context.m_capacity > 0) Clear();

        m_context.m_dataIsExternal = true;
        m_context.m_data.m = data;
        m_context.m_capacity = m_context.m_size = size;
    }

    string MatrixState::ToString(const uint32_t& index)
    {
        return glm::to_string(m_context.Get<glm::mat4x4>(index));
    }
}