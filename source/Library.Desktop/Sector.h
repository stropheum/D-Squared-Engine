#pragma once
#include "Attributed.h"
#include "Factory.h"


namespace Library
{
	class World;

	class Sector final :
		public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:
		Sector();
		~Sector() = default;

		Sector(const Sector& rhs) = delete;
		Sector* operator=(const Sector& rhs) = delete;

		Sector(Sector&& rhs) = delete;
		Sector* operator=(Sector&& rhs) = delete;

		std::string name() const;
		void setName(const std::string& name);
		Datum& entities();
		class Entity* createEntity(const std::string& className, const std::string& instanceName) const;
		void setWorld(World& world);
		World& getWorld();
		void update(class WorldState& worldState);

	private:
		std::string mName;
	};
}

