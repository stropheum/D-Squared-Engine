#include "pch.h"
#include "ActionCreateAction.h"


using namespace std;

namespace Library
{
    ActionCreateAction::ActionCreateAction()
    {
        (*this)["Prototype"].SetStorage(&m_prototype, 1);
        (*this)["Name"].SetStorage(&m_name, 1);
    }

    void ActionCreateAction::Update(WorldState& worldState)
    {
        worldState.Action() = this;

        assert(GetParent()->Is(Entity::TypeIdClass()) || GetParent()->Is(ActionList::TypeIdClass()));

        if (GetParent()->Is(Entity::TypeIdClass()))
        {
            GetParent()->As<Entity>()->CreateAction(m_prototype, m_name);
        }

        else if (GetParent()->Is(ActionList::TypeIdClass()))
        {
            GetParent()->As<ActionList>()->CreateAction(m_prototype, m_name);
        }

        worldState.Action() = nullptr;
    }

    void ActionCreateAction::SetPrototype(const string& name)
    {
        (*this)["Prototype"] = name;
    }

    string ActionCreateAction::GetPrototype() const
    {
        return m_prototype;
    }
}