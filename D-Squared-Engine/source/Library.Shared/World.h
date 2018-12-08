#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "EventQueue.h"
#include "WorldState.h"


namespace Library
{
    class World final : public Attributed
    {
        RTTI_DECLARATIONS(World, Attributed)

    public:

#pragma region Construction/Copy/Assignment

        World();

        ~World() = default;

        World(const World& rhs) = delete;

        World* operator=(const World& rhs) = delete;

        World(World&& rhs) = delete;

        World* operator=(World&& rhs) = delete;

#pragma endregion

        /**
         * Accessor method for the Name of the mWorld
         * @Return: The Name of the mWorld
         */
        std::string Name() const;

        /**
         * Mutator method for the Name of the mWorld
         * @Param Name: the new Name of the mWorld
         */
        void SetName(const std::string& name);

        /**
         * Accessor method for the collection of Sectors in the mWorld
         * @Return: A datum reference containing the collection of Sectors
         */
        Datum& Sectors();

        /**
         * Method used to Create a mSector as a child of this mWorld
         * @Param Name: The Name of the freshly created mSector object
         */
        Sector* CreateSector(const std::string& name);

        /**
         * Update method for handling change of game state
         * @Param worldState: The object that contains the mWorld state data
         * @param gameTime: The GameTime instance for the game
         */
        void Update(class WorldState& worldState, class GameTime& gameTime);

        /**
         * Accessor method for the event queue
         * @Return: A reference to the event queue associated with this mWorld
         */
        EventQueue& GetEventQueue();

    private:

        std::string mName; // The Name of the mWorld
        EventQueue mEventQueue;

    };
}