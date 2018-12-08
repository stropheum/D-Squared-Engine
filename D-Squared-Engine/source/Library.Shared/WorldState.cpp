#include "pch.h"
#include "WorldState.h"


using namespace std;

namespace Library
{
    WorldState::WorldState() :
        mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mAction(nullptr), mGameTime(nullptr)
    {}

    WorldState::~WorldState()
    {}

    GameTime& WorldState::GetGameTime() const
    {
        if (mGameTime == nullptr)
        {
            throw exception("Attempting to get gametime before setting");
        }
        return *mGameTime;
    }

    void WorldState::SetGameTime(GameTime& newGameTime)
    {
        mGameTime = &newGameTime;
    }

    World*& WorldState::World()
    {
        return mWorld;
    }

    Sector*& WorldState::Sector()
    {
        return mSector;
    }

    Entity*& WorldState::Entity()
    {
        return mEntity;
    }

    Action*& WorldState::Action()
    {
        return mAction;
    }
}