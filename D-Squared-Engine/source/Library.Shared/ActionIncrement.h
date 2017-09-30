#pragma once
#include "Action.h"


namespace Library
{
	class ActionIncrement : public Action
	{

	public:

#pragma region Construction/Copy/Assignment

		ActionIncrement();

		virtual ~ActionIncrement() = default;

		ActionIncrement(const ActionIncrement& rhs) = delete;

		ActionIncrement& operator=(const ActionIncrement& rhs) = delete;

		ActionIncrement(ActionIncrement&& rhs) = delete;

		ActionIncrement& operator=(ActionIncrement&& rhs) = delete;

#pragma endregion

		/**
		 * Updates the mAction based on the current mWorld state
		 * @Param worldState: The current mWorld state
		 */
		void Update(WorldState& worldState) override;

		/**
		 * Accessor for the current increment count
		 * @Return: The number of times the mAction has been incremented
		 */
		std::int32_t GetIncrementCount() const;

	private:

		std::int32_t mIncrementCount;

	};

	ActionFactory(ActionIncrement)
}

