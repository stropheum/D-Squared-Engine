#include "pch.h"
#include "EventMessageAttributed.h"


using namespace std;

namespace Library
{
    EventMessageAttributed::EventMessageAttributed() :
        mSubtype(""), mWorldState(nullptr)
    {}

    const string& EventMessageAttributed::GetSubtype() const
    {
        return mSubtype;
    }

    void EventMessageAttributed::SetSubtype(const string& subtype)
    {
        mSubtype = subtype;
    }

    WorldState* EventMessageAttributed::GetWorldState() const
    {
        return mWorldState;
    }

    void EventMessageAttributed::SetWorldState(WorldState& worldState)
    {
        mWorldState = &worldState;
    }
}