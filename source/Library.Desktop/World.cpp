#include "pch.h"
#include "World.h"
#include "Factory.h"


namespace Library
{
	RTTI_DEFINITIONS(World)

	World::World()
	{
		(*this)["Name"].setStorage(&mName, 1);
		(*this)["Sectors"].setType(DatumType::Scope);
	}

	std::string World::name() const
	{
		return mName;
	}

	void World::setName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& World::sectors()
	{
		return (*this)["Sectors"];
	}

	Sector* World::createSector(const std::string& name)
	{
		Sector* sector = new Sector();
		adopt(*sector, name);
		return sector;
	}

	void World::update(WorldState& worldState, GameTime& gameTime)
	{
		UNREFERENCED_PARAMETER(worldState);
		UNREFERENCED_PARAMETER(gameTime);
	}
}

