#pragma once

namespace Library
{
	class GameTime;

	class WorldState
	{
	public:
		WorldState();
		~WorldState();

		GameTime& getGameTime() const;
		void setGameTime(GameTime& gameTime);

		class World* world;
		class Sector* sector;
		class Entity* entity;
		class Action* action;

		GameTime* gameTime;
	};
}