#include "pch.h"
#include "ActionCreateAction.h"


using namespace std;

namespace Library
{
	ActionCreateAction::ActionCreateAction()
	{
		(*this)["Prototype"].SetStorage(&mPrototype, 1);
		(*this)["Name"].SetStorage(&mName, 1);
	}

	void ActionCreateAction::Update(WorldState& worldState)
	{
		worldState.Action() = this;

		assert(GetParent()->Is(Entity::TypeIdClass()) || GetParent()->Is(ActionList::TypeIdClass()));

		if (GetParent()->Is(Entity::TypeIdClass()))
		{
			GetParent()->As<Entity>()->CreateAction(mPrototype, mName);
		}
		
		else if (GetParent()->Is(ActionList::TypeIdClass()))
		{
			GetParent()->As<ActionList>()->CreateAction(mPrototype, mName);
		}

		worldState.Action() = nullptr;
	}

	void ActionCreateAction::SetPrototype(const string& name)
	{
		(*this)["Prototype"] = name;
	}

	string ActionCreateAction::GetPrototype() const
	{
		return mPrototype;
	}
}
