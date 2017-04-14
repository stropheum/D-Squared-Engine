#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "EventQueue.h"


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

		/// Accessor method for the name of the world
		/// @Return: The name of the world
		std::string name() const;

		/// Mutator method for the name of the world
		/// @Param name: the new name of the world
		void setName(const std::string& name);

		/// Accessor method for the collection of sectors in the world
		/// @Return: A datum reference containing the collection of sectors
		Datum& sectors();

		/// Method used to create a sector as a child of this world
		/// @Param name: The name of the freshly created sector object
		Sector* createSector(const std::string& name);

		/// Update method for handling change of game state
		/// @Param worldState: The object that contains the world state data
		/// @param gameTime: The GameTime instance for the game
		void update(class WorldState& worldState, class GameTime& gameTime);

		/// Accessor method for the event queue
		/// @Return: A reference to the event queue associated with this world
		EventQueue& getEventQueue();

	private:
		std::string mName; /// The name of the world
		EventQueue mEventQueue;
	};
}


