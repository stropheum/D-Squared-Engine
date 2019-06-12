#include "pch.h"
#include "ActionDestroyAction.h"


namespace Library
{
    ActionDestroyAction::ActionDestroyAction()
    {
        (*this)["ActionInstanceName"].SetStorage(&m_actionInstanceName, 1);
    }

    void ActionDestroyAction::Update(WorldState& worldState)
    {
        worldState.Action() = this;

        Datum* actions = GetParent()->Search("Actions");
        assert(actions != nullptr);

        for (std::uint32_t i = 0; i < actions->Size(); i++)
        {
            assert((*actions)[i].Is(Action::TypeIdClass()));
            Action* action = (*actions)[i].As<Action>();

            if (action->Name() == m_actionInstanceName)
            {
                actions->Remove(action);
                break;
            }
        }

        worldState.Action() = nullptr;
    }

    void ActionDestroyAction::SetActionInstanceName(const std::string& name)
    {
        (*this)["ActionInstanceName"] = name;
    }

    std::string ActionDestroyAction::GetActionInstanceName() const
    {
        return m_actionInstanceName;
    }
}