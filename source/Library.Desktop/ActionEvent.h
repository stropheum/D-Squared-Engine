#pragma once
#include "Action.h"


namespace Library
{
	class ActionEvent final:
		public Action
	{
	public:

		/// Constructor
		ActionEvent();

		/// Destructor
		~ActionEvent() = default;

		/// Updates the game state
		/// @Param worldState: The worldstate object storing information about the world
		virtual void update(class WorldState& worldState) override;

		/// Accessor method for the subtype of the reaction
		/// @Return: String representation of the subtype
		std::string getSubtype();

		/// Mutator method for the subtype of the reaction
		/// @Param subtype: The subtype of the reaction
		void setSubtype(const std::string& subtype);

		/// Accessor method for the delay of the event
		/// @Return: The delay in milliseconds
		const std::int32_t& getDelay();

		/// Mutator method for the delay of the event
		/// @Param delay: The delay of the event
		void setDelay(const std::int32_t delay);
	};

	ActionFactory(ActionEvent)
}

