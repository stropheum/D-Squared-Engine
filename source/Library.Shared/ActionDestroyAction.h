#pragma once
#include "Action.h"


namespace Library
{
	class ActionDestroyAction : public Action
	{

	public:

#pragma region Construction/Copy/Assignment

		ActionDestroyAction();

		~ActionDestroyAction() = default;

		ActionDestroyAction(const ActionDestroyAction& rhs) = delete;

		ActionDestroyAction& operator=(const ActionDestroyAction& rhs) = delete;

		ActionDestroyAction(ActionDestroyAction&& rhs) = delete;

		ActionDestroyAction& operator=(ActionDestroyAction&& rhs) = delete;

#pragma endregion

		/**
		 * Destroys the mAction with the specified Name, if it exists in the hierarchy
		 * @Param worldState: The mWorld state object that stores the current mWorld state
		 */
		virtual void Update(WorldState& worldState) override;

		/**
		 * Mutator method for the Name of the mAction being destroyed
		 * @Param Name: The Name of the mAction being destroyed
		 */
		void SetActionInstanceName(const std::string& name);

		/**
		 * Accessor for the Name of the mAction being destroyed
		 * @Return: The Name of the mAction being destroyed
		 */
		std::string GetActionInstanceName() const;

	private:

		std::string mActionInstanceName; // The Name of the mAction being destroyed

	};

	ActionFactory(ActionDestroyAction)
}

