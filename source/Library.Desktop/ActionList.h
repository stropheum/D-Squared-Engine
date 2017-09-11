#pragma once
#include "Action.h"


namespace Library
{
	class ActionList :
		public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:

		/**
		 * Constructor
		 */
		ActionList();

		/**
		 * Destructor(defaulted)
		 */
		~ActionList() = default;

		/**
		 * Updates the Actions contained in the action list
		 * @Param worldState: The world state object that holds the current world state
		 */
		virtual void Update(WorldState& worldState) override;

		/**
		 * Method for adding Actions to the action list
		 * @Param ClassName: The Name of the base class being instantiated
		 * @Param instanceName: The Name that the action will be instantiated with
		 * @Return: A freshly instantiated action object
		 */
		class Action* CreateAction(const std::string& className, const std::string& instanceName);
	};

	// Macro for creating a factory for action list objects
	ActionFactory(ActionList)
}

