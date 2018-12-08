#pragma once
#include "Attributed.h"


namespace Library
{
    class World;

    class Sector final : public Attributed
    {
        RTTI_DECLARATIONS(Sector, Attributed)

    public:

#pragma region Construction/Copy/Assignment

        Sector();

        ~Sector() = default;

        Sector(const Sector& rhs) = delete;

        Sector* operator=(const Sector& rhs) = delete;

        Sector(Sector&& rhs) = delete;

        Sector* operator=(Sector&& rhs) = delete;

#pragma endregion

        /**
         * Accessor method for the Name of the mSector
         * @Return: The Name of the mSector
         */
        std::string Name() const;

        /**
         * Mutator method for the Name of the mSector
         * @Param Name: The new Name of the mSector
         */
        void SetName(const std::string& name);

        /**
         * Accessor method for the Entities datum in the mSector
         * @Return: A datum reference of the collection of Entities in the mSector
         */
        Datum& Entities();

        /**
         * Method for adding Entities to the mSector
         * @Param ClassName: The Name of the base class being instantiated
         * @Param instanceName: The Name that the mEntity will be instantiated with
         * @Return: A freshly instantiated mEntity object
         */
        class Entity* CreateEntity(const std::string& className, const std::string& instanceName);

        /**
         * Mutator method which allows the mSector to be adopted into another mWorld
         * @Param mWorld: The new mWorld where this mSector will live
         */
        void SetWorld(World& world);

        /**
         * Accessor method for the mWorld that this mSector lives in
         * @Return: A reference to the mWorld that this mSector lives in
         */
        World& GetWorld() const;

        /**
         * Update method for handling change of game state
         * @Param worldState: The object that contains the mWorld state data
         */
        void Update(class WorldState& worldState);

    private:

        std::string mName;
    };
}