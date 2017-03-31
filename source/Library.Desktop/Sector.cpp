#include "pch.h"
#include "Sector.h"
#include "Entity.h"


namespace Library
{
	RTTI_DEFINITIONS(Sector)

	Sector::Sector()
	{
		(*this)["Name"].setStorage(&mName, 1);
	}

	std::string Sector::name() const
	{
		return mName;
	}

	void Sector::setName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& Sector::entities()
	{
		return (*this)["Entities"];
	}

	Entity* Sector::createEntity(const std::string& className, const std::string& instanceName)
	{
		Entity* instance = Factory<RTTI>::create(className)->As<Entity>();
		instance->name() = instanceName;
		return instance;
	}
}
