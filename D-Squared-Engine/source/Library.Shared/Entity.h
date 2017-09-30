#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "Factory.h"


namespace Library
{
	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)

	public:

#pragma region Construction/Copy/Assignment

		Entity();

		~Entity() = default;

		Entity(const Entity& rhs) = delete;

		Entity& operator=(const Entity& rhs) = delete;

		Entity(Entity&& rhs) = delete;

		Entity& operator=(Entity&& rhs) = delete;

#pragma endregion

		/**
		 * Accessor method for the Name of the mEntity
		 * @Return: The mEntity's Name field
		 */
		std::string Name() const;

		/**
		 * Mutator method for the Name of the mEntity
		 * @Param Name: the new Name of the mEntity
		 */
		void SetName(const std::string& name);

		/**
		 * Accessor method for the Actions datum in the mEntity
		 * @Return: A datum reference of the collection of Actions in the mEntity
		 */
		Datum& Actions();

		/**
		 * Method for adding Actions to the mEntity
		 * @Param ClassName: The Name of the base class being instantiated
		 * @Param instanceName: The Name that the mAction will be instantiated with
		 * @Return: A freshly instantiated mAction object
		 */
		class Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**
		 * Mutator method for the parent mSector
		 * @Param mSector: The new mSector that will own this mEntity
		 */
		void SetSector(Sector& sector);

		/**
		 * Accessor method for the parent mSector
		 * @Return: A reference to the mSector that contains this mEntity
		 */
		Sector& GetSector() const;

		/**
		 * Update method for handling change of game state
		 * @Param worldState: The object that contains the mWorld state data
		 */
		void Update(class WorldState& worldState);

	private:

		std::string mName; // The Name of the mEntity

	};
		
#define EntityFactory(ConcreteEntity) ConcreteFactory(Entity, ConcreteEntity)
	EntityFactory(Entity)
}
