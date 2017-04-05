#include "pch.h"
#include "ActionListIf.h"


namespace Library
{
	ActionListIf::ActionListIf()
	{
		(*this)["Condition"].setStorage(&mCondition, 1);
		(*this)["Then"].setType(DatumType::Scope);
		(*this)["Else"].setType(DatumType::Scope);
	}

	void ActionListIf::update(WorldState& worldState)
	{
		if (mCondition != 0)
		{
			for (std::uint32_t i = 0; i < (*this)["Then"].size(); i++)
			{
				assert((*this)["Then"].get<Scope*>(i)->Is(Action::TypeIdClass()));
				(*this)["Then"].get<Scope*>(i)->As<Action>()->update(worldState);
			}
		}
		else
		{
			for (std::uint32_t i = 0; i < (*this)["Else"].size(); i++)
			{
				assert((*this)["Else"].get<Scope*>(i)->Is(Action::TypeIdClass()));
				(*this)["Else"].get<Scope*>(i)->As<Action>()->update(worldState);
			}
		}
	}

	void ActionListIf::setCondition(std::int32_t condition)
	{
		mCondition = condition;
	}

	std::int32_t ActionListIf::getCondition() const
	{
		return mCondition;
	}

	Action* ActionListIf::createThenAction(const std::string& className, const std::string& instanceName)
	{
		Action* instance = Factory<Action>::create(className);
		assert(instance != nullptr);
		instance->setName(instanceName);
		adopt(*instance, "Then");
		return instance;
	}

	Action* ActionListIf::createElseAction(const std::string& className, const std::string& instanceName)
	{
		Action* instance = Factory<Action>::create(className);
		assert(instance != nullptr);
		instance->setName(instanceName);
		adopt(*instance, "Else");
		return instance;
	}
}



