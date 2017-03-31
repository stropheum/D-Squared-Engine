#pragma once

namespace Library
{
	class WorldState
	{
	public:
		WorldState();
		~WorldState();


		std::uint32_t getgameTime();
		void setGameTime(std::uint32_t time);

		class World* world;
		class Sector* sector;
		class Entity* entity;
		class Action* action;
	};
}