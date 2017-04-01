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

		World* operator=(const World& rhs) = delete;
		World(const World& rhs) = delete;

		World* operator=(World&& rhs) = delete;
		World(World&& rhs) = delete;

		std::string name() const;
		void setName(const std::string& name);
		Datum& sectors();
		Sector* createSector(const std::string& name);
		void update(class WorldState& worldState, class GameTime& gameTime);

	private:
		std::string mName;
	};
}


