#include "pch.h"
#include "ScopeState.h"


using namespace std;

namespace Library
{
    ScopeState::ScopeState(Datum& context) :
        TypeState(context)
    {}

    bool ScopeState::operator==(const Datum& rhs)
    {
        bool result = false;

        if (rhs.Type() == DatumType::Scope)
        {
            result = true;
            for (uint32_t i = 0; i < m_context.Size(); i++)
            {
                if (m_context.Get<Scope>(i) != rhs.Get<Scope>(i))
                {	// If every scope doesn't match, we're done
                    result = false;
                    break;
                }
            }
        }

        return result;
    }

    Datum& ScopeState::operator=(Scope* const rhs)
    {
        if (m_context.m_size > 1) { throw exception("Invalid assignment invocation"); }
        if (m_context.m_size == 0) { m_context.SetSize(1); }
        m_context.m_data.sc[0] = rhs;
        return m_context;
    }

    void ScopeState::SetSize(const uint32_t& size)
    {
        m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(Scope*) * size);
        m_context.m_capacity = m_context.m_size = size;
    }

    void ScopeState::Reserve(const uint32_t& capacity)
    {
        if (capacity > m_context.m_capacity)
        {
            m_context.m_data.vp = realloc(m_context.m_data.vp, sizeof(Scope*) * capacity);
            m_context.m_capacity = capacity;
        }
    }
}