#pragma once
#include "Attributed.h"
#include "Sector.h"


namespace Library
{
	class World final :
		public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)

	public:
		World();
		~World();

		World* operator=(const World& rhs) = delete;
		World(const World& rhs) = delete;

		World* operator=(World&& rhs) = delete;
		World(World&& rhs) = delete;

		std::string name();
		void setName(const std::string& name);
		// sectors method
		Sector* createSector();
		void update(class WorldState& worldState, class GameTime& gameTime);
	};
}


