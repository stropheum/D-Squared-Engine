#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"


namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList()
	{
		(*this)["Actions"].SetType(DatumType::Scope);
	}

	void ActionList::Update(WorldState& worldState)
	{
		worldState.action = this;

		for (std::uint32_t i = 0; i < (*this)["Actions"].Size(); i++)
		{
			Scope* scope = (*this)["Actions"].Get<Scope*>(i);
			assert(scope != nullptr);
			Action* action = scope->As<Action>();
			assert(action != nullptr);
			action->Update(worldState);
		}

		worldState.action = nullptr;
	}

	Action* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Action* instance = Factory<Action>::Create(className);
		assert(instance != nullptr);
		instance->SetName(instanceName);
		Adopt(*instance, "Actions");
		return instance;
	}
}
