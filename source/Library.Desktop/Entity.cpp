#include "pch.h"
#include "Entity.h"


namespace Library
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity()
	{
		(*this)["Name"].setStorage(&mName, 1);
	}

	std::string Entity::name() const
	{
		return mName;
	}

	void Entity::setName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Sector* Entity::getSector()
	{
		assert(getParent()->Is(Sector::TypeIdClass()));
		return getParent()->As<Sector>();
	}

	void Entity::setSector(Sector& sector)
	{
		sector.adopt(*this, name());
	}

	void Entity::update(WorldState& worldState)
	{
		UNREFERENCED_PARAMETER(worldState);
		// Currently do nothing. Update will be called on all actions within this entity
	}
}
