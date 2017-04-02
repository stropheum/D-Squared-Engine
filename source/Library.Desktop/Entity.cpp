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
		UNREFERENCED_PARAMETER(worldState);
	}
}
