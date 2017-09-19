#pragma once
#include "Action.h"


namespace Library
{
	class ActionEvent final: public Action
	{

	public:

#pragma region Construction/Copy/Assignment

		ActionEvent();

		~ActionEvent() = default;

		ActionEvent(const ActionEvent& rhs) = delete;

		ActionEvent& operator=(const ActionEvent& rhs) = delete;

		ActionEvent(ActionEvent&& rhs) = delete;

		ActionEvent& operator=(ActionEvent&& rhs) = delete;

#pragma endregion

		/**
		 * Updates the game state
		 * @Param worldState: The worldstate object storing information about the world
		 */
		virtual void Update(class WorldState& worldState) override;

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

		/**
		 * Accessor method for the Delay of the event
		 * @Return: The Delay in milliseconds
		 */
		const std::int32_t& GetDelay();

		/**
		 * Mutator method for the Delay of the event
		 * @Param Delay: The Delay of the event
		 */
		void SetDelay(const std::int32_t& delay);

	};

	ActionFactory(ActionEvent)
}

