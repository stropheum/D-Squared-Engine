#pragma once
#include "Action.h"


namespace Library
{
	class ActionIncrement :
		public Action
	{
	public:

		/**
		 * Constructor
		 */
		ActionIncrement();

		/**
		 * Default Destrutor
		 */
		~ActionIncrement() = default;

		/**
		 * Updates the action based on the current world state
		 * @Param worldState: The current world state
		 */
		virtual void Update(WorldState& worldState) override;

		/**
		 * Accessor for the current increment count
		 * @Return: The number of times the action has been incremented
		 */
		std::int32_t GetIncrementCount() const;

	private:
		std::int32_t mIncrementCount;
	};

	ActionFactory(ActionIncrement)
}

