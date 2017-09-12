#pragma once
#include "Action.h"


namespace Library
{
	class ActionCreateAction :
		public Action
	{
	public:

#pragma region Cosntruction/Copy/Assignment

		ActionCreateAction();

		virtual ~ActionCreateAction() = default;

		ActionCreateAction(const ActionCreateAction& rhs) = delete;

		ActionCreateAction& operator=(const ActionCreateAction& rhs) = delete;

		ActionCreateAction(ActionCreateAction&& rhs) = delete;

		ActionCreateAction& operator=(ActionCreateAction&& rhs) = delete;

#pragma endregion

		/**
		 * Creates an action
		 * @Param worldState: The world state object that stores the current world state
		 */
		virtual void Update(WorldState& worldState) override;
		
		/**
		 * Mutator method for the action being created
		 * @Param Name: The Name of the action being created
		 */
		void SetPrototype(const std::string& name);

		/**
		 * Accessor method for the action being created
		 * @Return: The Name of the action being created
		 */
		std::string GetPrototype() const;

	private:

		std::string mPrototype; // The Type of class being constructed
	};

	ActionFactory(ActionCreateAction)
}

