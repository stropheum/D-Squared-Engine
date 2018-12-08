#include "pch.h"
#include "Action.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(Action)

        Action::Action() :
        mName()
    {}

    std::string Action::Name() const
    {
        return mName;
    }

    void Action::SetName(const string& name)
    {
        mName = name;
    }
}