#pragma once
#include "Attributed.h"
#include "Factory.h"


namespace Library
{
    class Action : public Library::Attributed
    {
        RTTI_DECLARATIONS(Action, Attributed)

    public:

#pragma region Construction/Copy/Assignment

        Action();

        virtual ~Action() = default;

        Action(const Action& rhs) = delete;

        Action& operator=(const Action& rhs) = delete;

        Action(Action&& rhs) = delete;

        Action& operator=(Action&& rhs) = delete;

#pragma endregion

        /**
         * Updates the game state
         * @Param worldState: The worldstate object storing information about the mWorld
         */
        virtual void Update(class WorldState& worldState) = 0;

        /**
         * Accessor method for the Name of the mAction
         * @Return: The Name of the mAction
         */
        std::string Name() const;

        /**
         * Mutator method for the Name of the mAction
         * @Param Name: The new Name of the mAction
         */
        void SetName(const std::string& name);

    protected:

        std::string mName; // The Name of the mAction

    };

#define ActionFactory(ConcreteAction) ConcreteFactory(Action, ConcreteAction)
}