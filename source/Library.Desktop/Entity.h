#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "Factory.h"


namespace Library
{
	class Entity :
		public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)

	public:
		/// constructor
		Entity();

		/// Defautled destructor
		~Entity() = default;

		/// Assignment operator(disabled)
		Entity* operator=(const Entity& rhs) = delete;

		/// Copy constructor(disabled)
		Entity(const Entity& rhs) = delete;

		/// Move assignment operator(disabled)
		Entity* operator=(Entity&& rhs) = delete;

		/// Move cppy constructor(disabled)
		Entity(Entity&& rhs) = delete;

		/// Accessor method for the name of the entity
		/// @Return: The entity's name field
		std::string name() const;

		/// Mutator method for the name of the entity
		/// @Param name: the new name of the entity
		void setName(const std::string& name);

		/// Mutator method for the parent sector
		/// @Param sector: The new sector that will own this entity
		void setSector(Sector& sector);

		/// Accessor method for the parent sector
		/// @Return: A reference to the sector that contains this entity
		Sector& getSector();

		/// Update method for handling change of game state
		/// @Param worldState: The object that contains the world state data
		void update(class WorldState& worldState);

	private:
		std::string mName; /// The name of the entity
	};

	ConcreteFactory(Entity, Entity)										
}
