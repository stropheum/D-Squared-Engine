#include "pch.h"
#include "WorldState.h"


using namespace std;

namespace Library
{
    WorldState::WorldState() :
        m_world(nullptr), 
        m_sector(nullptr), 
        m_entity(nullptr), 
        m_action(nullptr), 
        m_gameTime(nullptr)
    {}

    WorldState::~WorldState()
    {}

    GameTime& WorldState::GetGameTime() const
    {
        if (m_gameTime == nullptr)
        {
            throw exception("Attempting to get gametime before setting");
        }
        return *m_gameTime;
    }

    void WorldState::SetGameTime(GameTime& newGameTime)
    {
        m_gameTime = &newGameTime;
    }

    World*& WorldState::World()
    {
        return m_world;
    }

    Sector*& WorldState::Sector()
    {
        return m_sector;
    }

    Entity*& WorldState::Entity()
    {
        return m_entity;
    }

    Action*& WorldState::Action()
    {
        return m_action;
    }
}