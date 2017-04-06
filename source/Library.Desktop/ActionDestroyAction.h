#pragma once
#include "Action.h"


namespace Library
{
	class ActionDestroyAction :
		public Action
	{
	public:

		/// Constructor
		ActionDestroyAction();

		/// Destructor(defaulted)
		~ActionDestroyAction() = default;

		/// Destroys the action with the specified name, if it exists in the hierarchy
		/// @Param worldState: The world state object that stores the current world state
		virtual void update(WorldState& worldState) override;

		/// Mutator method for the name of the action being destroyed
		/// @Param name: The name of the action being destroyed
		void setActionInstanceName(const std::string& name);

		/// Accessor for the name of the action being destroyed
		/// @Return: The name of the action being destroyed
		std::string getActionInstanceName() const;

	private:
		std::string mActionInstanceName; /// The name of the action being destroyed
	};

	ActionFactory(ActionDestroyAction)
}

