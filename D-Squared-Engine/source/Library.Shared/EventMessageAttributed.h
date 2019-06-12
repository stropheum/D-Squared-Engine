#pragma once
#include "Scope.h"


namespace Library
{
    class WorldState;

    class EventMessageAttributed final : public Scope
    {

    public:

#pragma region Construction/Copy/Assignment

        EventMessageAttributed();

        virtual ~EventMessageAttributed() = default;

        EventMessageAttributed(const EventMessageAttributed& rhs) = default;

        EventMessageAttributed& operator=(const EventMessageAttributed& rhs) = default;

        EventMessageAttributed(EventMessageAttributed&& rhs) = delete;

        EventMessageAttributed& operator=(EventMessageAttributed&& rhs) = delete;

#pragma endregion

        /**
         * Accessor for the event Message attributed subtype
         * @Return: The subtype of the event Message attributed
         */
        const std::string& GetSubtype() const;

        /**
         * Mutator for the event Message attributed subtype
         * @Param subtype: The subtype of the event Message attributed
         */
        void SetSubtype(const std::string& subtype);

        /**
         * Accessor for the mWorld state
         * @Return: A pointer to the mWorld state
         */
        WorldState* GetWorldState() const;

        /**
         * Mutator for the mWorld state poitner
         * @Param worldState: the mWorld state
         */
        void SetWorldState(WorldState& worldState);

    private:

        std::string m_subtype; // The subtype of the event Message attributed
        WorldState* m_worldState; // The mWorld state object

    };
}