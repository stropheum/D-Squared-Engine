#include "pch.h"
#include "World.h"
#include "Factory.h"
#include "WorldState.h"


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
		sector->setName(name);
		adopt(*sector, "Sectors");
		return sector;
	}

	void World::update(WorldState& worldState, GameTime& gameTime)
	{
		worldState.world = this;

		for (std::uint32_t i = 0; i < sectors().size(); i++)
		{
			assert(sectors()[i].Is(Sector::TypeIdClass()));
			sectors()[i].As<Sector>()->update(worldState);
		}

		mEventQueue.update(gameTime);

		worldState.world = nullptr;
	}

	EventQueue& World::getEventQueue()
	{
		return mEventQueue;
	}
}

