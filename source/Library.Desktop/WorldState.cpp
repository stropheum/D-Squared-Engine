#include "pch.h"
#include "WorldState.h"


namespace Library
{
	WorldState::WorldState() :
		world(nullptr), sector(nullptr), entity(nullptr), gameTime(nullptr)
	{
	}

	WorldState::~WorldState()
	{
	}

	GameTime& WorldState::getGameTime() const
	{
		if (gameTime == nullptr)
		{
			throw std::exception("Attempting to get gametime before setting");
		}
		return *gameTime;
	}

	void WorldState::setGameTime(GameTime& newGameTime)
	{
		gameTime = &newGameTime;
	}
}
