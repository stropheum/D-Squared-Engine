#include "pch.h"
#include "ActionListIf.h"


using namespace std;

namespace Library
{
	ActionListIf::ActionListIf()
	{
		(*this)["Condition"].SetStorage(&mCondition, 1);
		(*this)["Then"].SetType(DatumType::Scope);
		(*this)["Else"].SetType(DatumType::Scope);
	}

	void ActionListIf::Update(WorldState& worldState)
	{
		if (mCondition != 0)
		{
			for (uint32_t i = 0; i < (*this)["Then"].Size(); i++)
			{
				assert((*this)["Then"].Get<Scope>(i).Is(Action::TypeIdClass()));
				(*this)["Then"].Get<Scope>(i).As<Action>()->Update(worldState);
			}
		}
		else
		{
			for (uint32_t i = 0; i < (*this)["Else"].Size(); i++)
			{
				assert((*this)["Else"].Get<Scope>(i).Is(Action::TypeIdClass()));
				(*this)["Else"].Get<Scope>(i).As<Action>()->Update(worldState);
			}
		}
	}

	void ActionListIf::SetCondition(const int32_t& condition)
	{
		mCondition = condition;
	}

	int32_t ActionListIf::GetCondition() const
	{
		return mCondition;
	}

	Action* ActionListIf::CreateThenAction(const string& className, const string& instanceName)
	{
		Action* instance = Factory<Action>::Create(className);
		assert(instance != nullptr);
		instance->SetName(instanceName);
		Adopt(*instance, "Then");
		return instance;
	}

	Action* ActionListIf::CreateElseAction(const string& className, const string& instanceName)
	{
		Action* instance = Factory<Action>::Create(className);
		assert(instance != nullptr);
		instance->SetName(instanceName);
		Adopt(*instance, "Else");
		return instance;
	}
}



