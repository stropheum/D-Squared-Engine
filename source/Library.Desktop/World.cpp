#include "pch.h"
#include "World.h"
#include "Factory.h"


namespace Library
{
	RTTI_DEFINITIONS(World)

	World::World()
	{
	}

	World::~World()
	{
	}

	std::string World::name()
	{
		std::string result = "";

		if (find("Name") != nullptr)
		{
			result = (*this)["Name"].get<std::string>(0);
		}

		return result;
	}

	void World::setName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Sector* World::createSector()
	{
		Sector* sector = Factory<RTTI>::create("Sector")->As<Sector>();
		adopt(*sector, "Sector");
		return sector;
	}

	void World::update(WorldState& worldState, GameTime& gameTime)
	{
		UNREFERENCED_PARAMETER(worldState);
		UNREFERENCED_PARAMETER(gameTime);
	}
}

