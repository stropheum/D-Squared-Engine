#pragma once


namespace Library
{
    class GameTime;
    class World;
    class Sector;
    class Entity;
    class Action;

    class WorldState
    {

    public:

#pragma region Construction/Copy/Assignment

        WorldState();

        ~WorldState();

        WorldState(const WorldState& rhs) = delete;

        WorldState& operator=(const WorldState& rhs) = delete;

        WorldState(WorldState&& rhs) = delete;

        WorldState& operator=(WorldState&& rhs) = delete;

#pragma endregion

        /**
         * Accessor method for the gametime
         * @Return: A reference to the gametime object
         */
        GameTime& GetGameTime() const;

        /**
         * Mutator method for the gametime
         * @Param mGameTime: A reference to the gametime object
         */
        void SetGameTime(GameTime& gameTime);

        /**
         * Accessor method for the world state's world pointer
         * @Return: A pointer to the world
         */
        World*& World();

        /**
        * Accessor method for the world state's sector pointer
        * @Return: A pointer to the sector
        */
        Sector*& Sector();

        /**
        * Accessor method for the world state's entity pointer
        * @Return: A pointer to the entity
        */
        Entity*& Entity();

        /**
        * Accessor method for the world state's action pointer
        * @Return: A pointer to the action
        */
        Action*& Action();

    private:

        class World* m_world;
        class Sector* m_sector;
        class Entity* m_entity;
        class Action* m_action;

        GameTime* m_gameTime;

    };
}