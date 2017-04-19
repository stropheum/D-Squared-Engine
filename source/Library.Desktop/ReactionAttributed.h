#pragma once
#include "Reaction.h"


namespace Library
{
	class ReactionAttributed final:
		public Reaction
	{
	public:

		/// Constructor
		ReactionAttributed();

		/// Destructor
		~ReactionAttributed();

		/// Notifies the subscriber that an event has been triggered
		/// @Param event: The event that the subscriber is being notified of
		virtual void notify(const EventPublisher& event) override;

		/// Accessor method for the subtype of the reaction
		/// @Return: String representation of the subtype
		std::string getSubtype();

		/// Mutator method for the subtype of the reaction
		/// @Param subtype: The subtype of the reaction
		void setSubtype(const std::string& subtype);
	};

	ReactionFactory(ReactionAttributed)
}

