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

#pragma region Construction/Copy/Assignment

		Entity();

		~Entity() = default;

		Entity(const Entity& rhs) = delete;

		Entity* operator=(const Entity& rhs) = delete;

		Entity(Entity&& rhs) = delete;

		Entity* operator=(Entity&& rhs) = delete;

#pragma endregion

		/**
		 * Accessor method for the Name of the entity
		 * @Return: The entity's Name field
		 */
		std::string Name() const;

		/**
		 * Mutator method for the Name of the entity
		 * @Param Name: the new Name of the entity
		 */
		void SetName(const std::string& name);

		/**
		 * Accessor method for the Actions datum in the entity
		 * @Return: A datum reference of the collection of Actions in the entity
		 */
		Datum& Actions();

		/**
		 * Method for adding Actions to the entity
		 * @Param ClassName: The Name of the base class being instantiated
		 * @Param instanceName: The Name that the action will be instantiated with
		 * @Return: A freshly instantiated action object
		 */
		class Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**
		 * Mutator method for the parent sector
		 * @Param sector: The new sector that will own this entity
		 */
		void SetSector(Sector& sector);

		/**
		 * Accessor method for the parent sector
		 * @Return: A reference to the sector that contains this entity
		 */
		Sector& GetSector();

		/**
		 * Update method for handling change of game state
		 * @Param worldState: The object that contains the world state data
		 */
		void Update(class WorldState& worldState);

	private:
		std::string mName; // The Name of the entity
	};
		
#define EntityFactory(ConcreteEntity) ConcreteFactory(Entity, ConcreteEntity)
	EntityFactory(Entity)
}
