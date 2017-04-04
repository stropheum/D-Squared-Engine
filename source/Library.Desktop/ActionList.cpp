#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"


namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList()
	{
		(*this)["Actions"].setType(DatumType::Scope);
	}

	void ActionList::update(WorldState& worldState)
	{
		worldState.action = this;

		for (std::uint32_t i = 0; i < (*this)["Actions"].size(); i++)
		{
			Scope* scope = (*this)["Actions"].get<Scope*>(i);
			assert(scope != nullptr);
			Action* action = scope->As<Action>();
			assert(action != nullptr);
			action->update(worldState);
		}

		worldState.action = nullptr;
	}

	Action* ActionList::createAction(const std::string& className, const std::string& instanceName)
	{
		Action* instance = Factory<Action>::create(className);
		assert(instance != nullptr);
		instance->setName(instanceName);
		adopt(*instance, "Actions");
		return instance;
	}
}
