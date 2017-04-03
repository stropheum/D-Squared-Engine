#include "pch.h"
#include "Entity.h"
#include "Action.h"


namespace Library
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity()
	{
		(*this)["Name"].setStorage(&mName, 1);
		(*this)["Actions"].setType(DatumType::Scope);
	}

	std::string Entity::name() const
	{
		return mName;
	}

	void Entity::setName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& Entity::actions()
	{
		return (*this)["Actions"];
	}

	Action* Entity::createAction(const std::string& className, const std::string& instanceName)
	{
		Action* instance = Factory<Action>::create(className);
		assert(instance != nullptr);
		instance->setName(instanceName);
		adopt(*instance, "Actions");
		return instance;
	}

	void Entity::setSector(Sector& sector)
	{
		sector.adopt(*this, mName);
	}

	Sector& Entity::getSector()
	{
		if (getParent() == nullptr)
		{
			throw std::exception("Parent is null");
		}
		assert(getParent()->Is(Sector::TypeIdClass()));
		return *getParent()->As<Sector>();
	}

	void Entity::update(WorldState& worldState)
	{
		for (std::uint32_t i = 0; i < (*this)["Actions"].size(); i++)
		{
			Scope* scope = (*this)["Actions"].get<Scope*>(i);
			assert(scope != nullptr);
			Action* action = scope->As<Action>();
			assert(action != nullptr);
			action->update(worldState);
		}
	}
}
