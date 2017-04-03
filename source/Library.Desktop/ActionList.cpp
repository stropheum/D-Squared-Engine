#include "pch.h"
#include "ActionList.h"


namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList()
	{
	}

	ActionList::~ActionList()
	{
		mActions.clear();
	}

	void ActionList::update(WorldState& worldState)
	{
		UNREFERENCED_PARAMETER(worldState);
	}
}
