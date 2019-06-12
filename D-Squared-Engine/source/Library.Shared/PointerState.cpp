#include "pch.h"
#include "PointerState.h"


using namespace std;

namespace Library
{
    PointerState::PointerState(Datum& context) :
        TypeState(context)
    {}

    bool PointerState::operator==(const Datum& rhs)
    {
        bool result = false;

        if (m_context.m_type == rhs.m_type && m_context.m_size == rhs.m_size)
        {
            result = true;
            for (uint32_t i = 0; i < m_context.m_size; i++)
            {
                if (m_context.m_data.r[i] != rhs.m_data.r[i])
                {
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    Datum& PointerState::operator=(Library::RTTI* const& rhs)
    {
        if (m_context.m_size == 0) { m_context.SetSize(1); }
        m_context.m_data.r[0] = rhs;
        return m_context;
    }

    void PointerState::SetSize(const uint32_t& size)
    {
        m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(Library::RTTI*) * size);
        m_context.m_capacity = m_context.m_size = size;
    }

    void PointerState::Reserve(const uint32_t& capacity)
    {
        if (capacity > m_context.m_capacity)
        {
            m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(Library::RTTI*) * capacity);
            m_context.m_capacity = capacity;
        }
    }

    void PointerState::Clear()
    {
        if (m_context.m_size > 0)
        {
            for (uint32_t i = 0; i < m_context.m_size; i++) m_context.m_data.r[i] = nullptr;
            m_context.m_size = 0;
        }
    }

    void PointerState::SetFromString(const string& value, const uint32_t& index)
    {
        UNREFERENCED_PARAMETER(value);
        UNREFERENCED_PARAMETER(index);
        throw exception("Attempting to Set pointer from string");
    }

    void PointerState::SetStorage(const Datum& rhs)
    {
        SetStorage(rhs.m_data.r, rhs.m_size);
    }

    void PointerState::SetStorage(Library::RTTI** data, const uint32_t& size)
    {
        assert(m_context.m_type == DatumType::Pointer);

        if (m_context.m_capacity > 0) Clear();

        m_context.m_dataIsExternal = true;
        m_context.m_data.r = data;
        m_context.m_capacity = m_context.m_size = size;
    }

    string PointerState::ToString(const uint32_t& index)
    {
        UNREFERENCED_PARAMETER(index);
        return "";
    }
}