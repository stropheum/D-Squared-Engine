#include "pch.h"
#include "ActionIncrement.h"
#include "WorldState.h"


namespace Library
{
	ActionIncrement::ActionIncrement():
		mIncrementCount(0)
	{
		(*this)["IncrementCount"].setStorage(&mIncrementCount, 1);
	}

	void ActionIncrement::update(WorldState& worldState)
	{
		worldState.action = this;
		mIncrementCount++;
		worldState.action = nullptr;
	}

	std::int32_t ActionIncrement::getIncrementCount() const
	{
		return mIncrementCount;
	}
}
