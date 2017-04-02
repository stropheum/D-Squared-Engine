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
		/// Constructor
		Sector();

		/// Defaulted destructor
		~Sector() = default;

		/// Copy constructor(disabled)
		Sector(const Sector& rhs) = delete;

		/// Assignment operator(disabled)
		Sector* operator=(const Sector& rhs) = delete;

		/// Move copy constructor(disabled)
		Sector(Sector&& rhs) = delete;

		/// Move assignment operator(disabled)
		Sector* operator=(Sector&& rhs) = delete;

		/// Accessor method for the name of the sector
		/// @Return: The name of the sector
		std::string name() const;

		/// Mutator method for the name of the sector
		/// @Param name: The new name of the sector
		void setName(const std::string& name);

		/// Accessor method for the entities datum in the sector
		/// @Return: A datum reference of the collection of entities in the sector
		Datum& entities();

		/// Method for adding entities to the sector
		/// @Param className: The name of the base class being instantiated
		/// @Param instanceName: The name that the entity will be instantiated with
		/// @Return: A freshly instantiated entity object
		class Entity* createEntity(const std::string& className, const std::string& instanceName);

		/// Mutator method which allows the sector to be adopted into another world
		/// @Param world: The new world where this sector will live
		void setWorld(World& world);

		/// Accessor method for the world that this sector lives in
		/// @Return: A reference to the world that this sector lives in
		World& getWorld();

		/// Update method for handling change of game state
		/// @Param worldState: The object that contains the world state data
		void update(class WorldState& worldState);

	private:
		std::string mName;
	};
}

