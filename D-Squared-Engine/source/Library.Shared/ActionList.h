#pragma once
#include "Action.h"


namespace Library
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:

#pragma region Construction/Copy/Assignment

		ActionList();

		virtual ~ActionList() = default;

		ActionList(const ActionList& rhs) = delete;

		ActionList& operator=(const ActionList& rhs) = delete;

		ActionList(ActionList&& rhs) = delete;

		ActionList& operator=(ActionList&& rhs) = delete;

#pragma endregion

		/**
		 * Updates the Actions contained in the mAction list
		 * @Param worldState: The mWorld state object that holds the current mWorld state
		 */
		void Update(WorldState& worldState) override;

		/**
		 * Method for adding Actions to the mAction list
		 * @Param ClassName: The Name of the base class being instantiated
		 * @Param instanceName: The Name that the mAction will be instantiated with
		 * @Return: A freshly instantiated mAction object
		 */
		class Action* CreateAction(const std::string& className, const std::string& instanceName);

	};

	// Macro for creating a factory for mAction list objects
	ActionFactory(ActionList)
}

