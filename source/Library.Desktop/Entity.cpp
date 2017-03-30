#include "pch.h"
#include "Entity.h"


namespace Library
{
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	std::string Entity::name()
	{
		// TODO: implement name method
		return "name";
	}

	void Entity::setName(const std::string& name)
	{
		UNREFERENCED_PARAMETER(name);
	}

	Sector* Entity::getSector()
	{
		return nullptr;
	}

	void Entity::setSector(const Sector& sector)
	{
		UNREFERENCED_PARAMETER(sector);
	}

	void Entity::update()
	{
	}
}
