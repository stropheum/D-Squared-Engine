#include "pch.h"
#include "ActionDestroyAction.h"
#include "WorldState.h"


namespace Library
{
	ActionDestroyAction::ActionDestroyAction()
	{
		(*this)["ActionInstanceName"].setStorage(&mActionInstanceName, 1);
	}

	void ActionDestroyAction::update(WorldState& worldState)
	{
		worldState.action = this;

		Datum* actions = getParent()->search("Actions");
		assert(actions != nullptr);

		for (std::uint32_t i = 0; i < actions->size(); i++)
		{
			assert((*actions)[i].Is(Action::TypeIdClass()));
			Action* action = (*actions)[i].As<Action>();

			if (action->name() == mActionInstanceName)
			{
				actions->remove(action);
				break;
			}
		}

		worldState.action = nullptr;
	}

	void ActionDestroyAction::setActionInstanceName(const std::string& name)
	{
		(*this)["ActionInstanceName"] = name;
	}

	std::string ActionDestroyAction::getActionInstanceName() const
	{
		return mActionInstanceName;
	}
}
