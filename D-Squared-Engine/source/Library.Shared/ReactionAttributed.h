#pragma once
#include "Reaction.h"


namespace Library
{
    class ReactionAttributed final : public Reaction
    {

    public:

#pragma region Construction/Copy/Assignment

        ReactionAttributed();

        ~ReactionAttributed();

        ReactionAttributed(const ReactionAttributed& rhs) = delete;

        ReactionAttributed& operator=(const ReactionAttributed& rhs) = delete;

        ReactionAttributed(ReactionAttributed&& rhs) = delete;

        ReactionAttributed& operator=(ReactionAttributed&& rhs) = delete;

#pragma endregion

        /**
         * Notifies the subscriber that an event has been triggered
         * @Param event: The event that the subscriber is being notified of
         */
        virtual void Notify(const EventPublisher& event) override;

        /**
         * Accessor method for the subtype of the reaction
         * @Return: String representation of the subtype
         */
        std::string GetSubtype();

        /**
         * Mutator method for the subtype of the reaction
         * @Param subtype: The subtype of the reaction
         */
        void SetSubtype(const std::string& subtype);

    };

    ReactionFactory(ReactionAttributed)
}