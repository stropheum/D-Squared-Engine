#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "EventQueue.h"
#include "WorldState.h"


namespace Library
{
	class World final :
		public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)

	public:
		/// constructor
		World();

		/// Assignment operator(disabled)
		World* operator=(const World& rhs) = delete;

		/// copy constructor(disabled)
		World(const World& rhs) = delete;

		/// Move copy constructor(disabled)
		World* operator=(World&& rhs) = delete;

		/// Move assignment operator(disabled)
		World(World&& rhs) = delete;

		/// Accessor method for the Name of the world
		/// @Return: The Name of the world
		std::string Name() const;

		/// Mutator method for the Name of the world
		/// @Param Name: the new Name of the world
		void SetName(const std::string& name);

		/// Accessor method for the collection of Sectors in the world
		/// @Return: A datum reference containing the collection of Sectors
		Datum& Sectors();

		/// Method used to Create a sector as a child of this world
		/// @Param Name: The Name of the freshly created sector object
		Sector* CreateSector(const std::string& name);

		/// Update method for handling change of game state
		/// @Param worldState: The object that contains the world state data
		/// @param gameTime: The GameTime instance for the game
		void Update(class WorldState& worldState, class GameTime& gameTime);

		/// Accessor method for the event queue
		/// @Return: A reference to the event queue associated with this world
		EventQueue& GetEventQueue();

	private:
		std::string mName; /// The Name of the world
		EventQueue mEventQueue;
	};
}


