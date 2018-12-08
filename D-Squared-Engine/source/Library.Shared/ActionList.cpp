#include "pch.h"
#include "ActionList.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(ActionList)

        ActionList::ActionList()
    {
        (*this)["Actions"].SetType(DatumType::Scope);
    }

    void ActionList::Update(WorldState& worldState)
    {
        worldState.Action() = this;

        for (uint32_t i = 0; i < (*this)["Actions"].Size(); i++)
        {
            Scope& scope = (*this)["Actions"].Get<Scope>(i);
            Action* action = scope.As<Action>();
            assert(action != nullptr);
            action->Update(worldState);
        }

        worldState.Action() = nullptr;
    }

    Action* ActionList::CreateAction(const string& className, const string& instanceName)
    {
        Action* instance = Factory<Action>::Create(className);
        assert(instance != nullptr);
        instance->SetName(instanceName);
        Adopt(*instance, "Actions");
        return instance;
    }
}