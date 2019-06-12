#include "pch.h"
#include "World.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(World);

    World::World()
    {
        (*this)["Name"].SetStorage(&m_name, 1);
        (*this)["Sectors"].SetType(DatumType::Scope);
    }

    string World::Name() const
    {
        return m_name;
    }

    void World::SetName(const string& name)
    {
        (*this)["Name"] = name;
    }

    Datum& World::Sectors()
    {
        return (*this)["Sectors"];
    }

    Sector* World::CreateSector(const string& name)
    {
        Sector* sector = new Sector();
        sector->SetName(name);
        Adopt(*sector, "Sectors");
        return sector;
    }

    void World::Update(WorldState& worldState, GameTime& gameTime)
    {
        worldState.World() = this;

        for (uint32_t i = 0; i < Sectors().Size(); i++)
        {
            assert(Sectors()[i].Is(Sector::TypeIdClass()));
            Sectors()[i].As<Sector>()->Update(worldState);
        }

        m_eventQueue.Update(gameTime);

        worldState.World() = nullptr;
    }

    EventQueue& World::GetEventQueue()
    {
        return m_eventQueue;
    }
}