#include "pch.h"
#include "World.h"
#include "Factory.h"
#include "WorldState.h"


namespace Library
{
	RTTI_DEFINITIONS(World)

	World::World()
	{
		(*this)["Name"].SetStorage(&mName, 1);
		(*this)["Sectors"].SetType(DatumType::Scope);
	}

	std::string World::Name() const
	{
		return mName;
	}

	void World::SetName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& World::Sectors()
	{
		return (*this)["Sectors"];
	}

	Sector* World::CreateSector(const std::string& name)
	{
		Sector* sector = new Sector();
		sector->SetName(name);
		Adopt(*sector, "Sectors");
		return sector;
	}

	void World::Update(WorldState& worldState, GameTime& gameTime)
	{
		worldState.world = this;

		for (std::uint32_t i = 0; i < Sectors().Size(); i++)
		{
			assert(Sectors()[i].Is(Sector::TypeIdClass()));
			Sectors()[i].As<Sector>()->Update(worldState);
		}

		mEventQueue.Update(gameTime);

		worldState.world = nullptr;
	}

	EventQueue& World::GetEventQueue()
	{
		return mEventQueue;
	}
}

