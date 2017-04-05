#include "pch.h"
#include "ActionCreateAction.h"
#include "Entity.h"
#include "ActionList.h"
#include "WorldState.h"


namespace Library
{
	ActionCreateAction::ActionCreateAction()
	{
		(*this)["Prototype"].setStorage(&mPrototype, 1);
		(*this)["Name"].setStorage(&mName, 1);
	}

	void ActionCreateAction::update(WorldState& worldState)
	{
		worldState.action = this;

		assert(getParent()->Is(Entity::TypeIdClass()) || getParent()->Is(ActionList::TypeIdClass()));

		if (getParent()->Is(Entity::TypeIdClass()))
		{
			getParent()->As<Entity>()->createAction(mPrototype, mName);
		}
		
		else if (getParent()->Is(ActionList::TypeIdClass()))
		{
			getParent()->As<ActionList>()->createAction(mPrototype, mName);
		}

		worldState.action = nullptr;
	}

	void ActionCreateAction::setPrototype(const std::string& name)
	{
		(*this)["Prototype"] = name;
	}

	std::string ActionCreateAction::getPrototype() const
	{
		return mPrototype;
	}
}
