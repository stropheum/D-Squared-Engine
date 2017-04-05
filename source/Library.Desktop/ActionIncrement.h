#pragma once
#include "Action.h"


namespace Library
{
	class ActionIncrement :
		public Action
	{
	public:
		ActionIncrement();
		~ActionIncrement() = default;
		virtual void update(WorldState& worldState) override;
		std::int32_t getIncrementCount() const;
	private:
		std::int32_t mIncrementCount;
	};

	ActionFactory(ActionIncrement)
}

