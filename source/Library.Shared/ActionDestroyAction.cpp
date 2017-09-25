#include "pch.h"
#include "ActionDestroyAction.h"


using namespace std;

namespace Library
{
	ActionDestroyAction::ActionDestroyAction()
	{
		(*this)["ActionInstanceName"].SetStorage(&mActionInstanceName, 1);
	}

	void ActionDestroyAction::Update(WorldState& worldState)
	{
		worldState.Action() = this;

		Datum* actions = GetParent()->Search("Actions");
		assert(actions != nullptr);

		for (uint32_t i = 0; i < actions->Size(); i++)
		{
			assert((*actions)[i].Is(Action::TypeIdClass()));
			Action* action = (*actions)[i].As<Action>();

			if (action->Name() == mActionInstanceName)
			{
				actions->Remove(action);
				break;
			}
		}

		worldState.Action() = nullptr;
	}

	void ActionDestroyAction::SetActionInstanceName(const string& name)
	{
		(*this)["ActionInstanceName"] = name;
	}

	string ActionDestroyAction::GetActionInstanceName() const
	{
		return mActionInstanceName;
	}
}
