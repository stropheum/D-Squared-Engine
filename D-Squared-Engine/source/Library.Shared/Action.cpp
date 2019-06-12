#include "pch.h"
#include "Action.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(Action);

    Action::Action() :
        m_name()
    {}

    std::string Action::Name() const
    {
        return m_name;
    }

    void Action::SetName(const string& name)
    {
        m_name = name;
    }
}