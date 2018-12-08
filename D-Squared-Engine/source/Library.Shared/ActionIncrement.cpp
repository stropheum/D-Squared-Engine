#include "pch.h"
#include "ActionIncrement.h"


using namespace std;

namespace Library
{
    ActionIncrement::ActionIncrement() :
        mIncrementCount(0)
    {
        (*this)["IncrementCount"].SetStorage(&mIncrementCount, 1);
    }

    void ActionIncrement::Update(WorldState& worldState)
    {
        worldState.Action() = this;
        mIncrementCount++;
        worldState.Action() = nullptr;
    }

    int32_t ActionIncrement::GetIncrementCount() const
    {
        return mIncrementCount;
    }
}