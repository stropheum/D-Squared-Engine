#include "pch.h"
#include "ActionIncrement.h"
#include "WorldState.h"


namespace Library
{
	ActionIncrement::ActionIncrement():
		mIncrementCount(0)
	{
		(*this)["IncrementCount"].SetStorage(&mIncrementCount, 1);
	}

	void ActionIncrement::Update(WorldState& worldState)
	{
		worldState.action = this;
		mIncrementCount++;
		worldState.action = nullptr;
	}

	std::int32_t ActionIncrement::GetIncrementCount() const
	{
		return mIncrementCount;
	}
}
