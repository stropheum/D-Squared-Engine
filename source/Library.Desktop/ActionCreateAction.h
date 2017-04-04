#pragma once
#include "Action.h"


namespace Library
{
	class ActionCreateAction :
		public Action
	{
	public:
		ActionCreateAction();
		~ActionCreateAction() = default;
		virtual void update(WorldState& worldState) override;
		
		std::string mPrototype;
	};

	ActionFactory(ActionCreateAction)
}

