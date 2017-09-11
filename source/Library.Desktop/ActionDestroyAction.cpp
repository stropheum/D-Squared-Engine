#include "pch.h"
#include "ActionDestroyAction.h"
#include "WorldState.h"


namespace Library
{
	ActionDestroyAction::ActionDestroyAction()
	{
		(*this)["ActionInstanceName"].SetStorage(&mActionInstanceName, 1);
	}

	void ActionDestroyAction::Update(WorldState& worldState)
	{
		worldState.action = this;

		Datum* actions = GetParent()->Search("Actions");
		assert(actions != nullptr);

		for (std::uint32_t i = 0; i < actions->Size(); i++)
		{
			assert((*actions)[i].Is(Action::TypeIdClass()));
			Action* action = (*actions)[i].As<Action>();

			if (action->Name() == mActionInstanceName)
			{
				actions->Remove(action);
				break;
			}
		}

		worldState.action = nullptr;
	}

	void ActionDestroyAction::SetActionInstanceName(const std::string& name)
	{
		(*this)["ActionInstanceName"] = name;
	}

	std::string ActionDestroyAction::GetActionInstanceName() const
	{
		return mActionInstanceName;
	}
}
