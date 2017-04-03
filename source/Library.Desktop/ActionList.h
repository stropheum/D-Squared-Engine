#pragma once
#include "Action.h"


namespace Library
{
	class ActionList :
		public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:
		ActionList();
		~ActionList();
		virtual void update(WorldState& worldState) override;

	protected:
		Vector<Action*> mActions;
	};

	/// Macro for creating a factory for action list objects
	ActionFactory(ActionList)
}

