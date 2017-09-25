#include "pch.h"
#include "Entity.h"


using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity()
	{
		(*this)["Name"].SetStorage(&mName, 1);
		(*this)["Actions"].SetType(DatumType::Scope);
	}

	string Entity::Name() const
	{
		return mName;
	}

	void Entity::SetName(const string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& Entity::Actions()
	{
		return (*this)["Actions"];
	}

	Action* Entity::CreateAction(const string& className, const string& instanceName)
	{
		Action* instance = Factory<Action>::Create(className);
		assert(instance != nullptr);
		instance->SetName(instanceName);
		Adopt(*instance, "Actions");
		return instance;
	}

	void Entity::SetSector(Sector& sector)
	{
		sector.Adopt(*this, mName);
	}

	Sector& Entity::GetSector() const
	{
		if (GetParent() == nullptr)
		{
			throw exception("Parent is null");
		}
		assert(GetParent()->Is(Sector::TypeIdClass()));
		return *GetParent()->As<Sector>();
	}

	void Entity::Update(WorldState& worldState)
	{
		worldState.Entity() = this;

		for (uint32_t i = 0; i < (*this)["Actions"].Size(); i++)
		{
			Scope& scope = (*this)["Actions"].Get<Scope>(i);
			Action* action = scope.As<Action>();
			assert(action != nullptr);
			action->Update(worldState);
		}

		worldState.Entity() = nullptr;
	}
}
