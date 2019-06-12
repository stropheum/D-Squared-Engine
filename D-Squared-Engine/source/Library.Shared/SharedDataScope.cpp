#include "pch.h"
#include "SharedDataScope.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(SharedDataScope);

    SharedDataScope::SharedDataScope() :
        SharedData(), 
        m_scope(nullptr)
    {}

    SharedDataScope::~SharedDataScope()
    {
        delete m_scope;
    }

    XmlParseMaster::SharedData* SharedDataScope::Clone()
    {
        SharedDataScope* clone = new SharedDataScope();
        if (m_scope != nullptr)
        {
            clone->m_scope = new Scope(*m_scope);
        }
        return clone;
    }

    string SharedDataScope::ToString() const
    {
        return "Shared Data Scope";
    }

    bool SharedDataScope::Equals(const RTTI* rhs) const
    {
        if (this == rhs) { return true; }
        if (rhs == nullptr) { return false; }
        SharedDataScope* data = rhs->As<SharedDataScope>();
        if (data == nullptr) { return false; }
        return
            (m_scope == data->m_scope) ||
            (m_scope != nullptr) &&
            (data->m_scope != nullptr) &&
            (*m_scope == *data->m_scope);
    }
}