#include "pch.h"
#include "Entity.h"
#include "Action.h"
#include "WorldState.h"


namespace Library
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity()
	{
		(*this)["Name"].SetStorage(&mName, 1);
		(*this)["Actions"].SetType(DatumType::Scope);
	}

	std::string Entity::Name() const
	{
		return mName;
	}

	void Entity::SetName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& Entity::Actions()
	{
		return (*this)["Actions"];
	}

	Action* Entity::CreateAction(const std::string& className, const std::string& instanceName)
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

	Sector& Entity::GetSector()
	{
		if (GetParent() == nullptr)
		{
			throw std::exception("Parent is null");
		}
		assert(GetParent()->Is(Sector::TypeIdClass()));
		return *GetParent()->As<Sector>();
	}

	void Entity::Update(WorldState& worldState)
	{
		worldState.entity = this;

		for (std::uint32_t i = 0; i < (*this)["Actions"].Size(); i++)
		{
			Scope* scope = (*this)["Actions"].Get<Scope*>(i);
			assert(scope != nullptr);
			Action* action = scope->As<Action>();
			assert(action != nullptr);
			action->Update(worldState);
		}

		worldState.entity = nullptr;
	}
}
