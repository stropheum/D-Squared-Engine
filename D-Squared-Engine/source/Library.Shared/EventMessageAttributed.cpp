#include "pch.h"
#include "EventMessageAttributed.h"


using namespace std;

namespace Library
{
    EventMessageAttributed::EventMessageAttributed() :
        m_subtype(""), m_worldState(nullptr)
    {}

    const string& EventMessageAttributed::GetSubtype() const
    {
        return m_subtype;
    }

    void EventMessageAttributed::SetSubtype(const string& subtype)
    {
        m_subtype = subtype;
    }

    WorldState* EventMessageAttributed::GetWorldState() const
    {
        return m_worldState;
    }

    void EventMessageAttributed::SetWorldState(WorldState& worldState)
    {
        m_worldState = &worldState;
    }
}