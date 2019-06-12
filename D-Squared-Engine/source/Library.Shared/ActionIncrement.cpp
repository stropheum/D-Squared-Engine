#include "pch.h"
#include "ActionIncrement.h"


namespace Library
{
    ActionIncrement::ActionIncrement() :
        m_incrementCount(0)
    {
        (*this)["IncrementCount"].SetStorage(&m_incrementCount, 1);
    }

    void ActionIncrement::Update(WorldState& worldState)
    {
        worldState.Action() = this;
        m_incrementCount++;
        worldState.Action() = nullptr;
    }

    std::int32_t ActionIncrement::GetIncrementCount() const
    {
        return m_incrementCount;
    }
}