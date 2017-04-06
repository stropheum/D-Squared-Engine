#pragma once
#include "Action.h"


namespace Library
{
	class ActionCreateAction :
		public Action
	{
	public:

		/// Constructor
		ActionCreateAction();

		/// Destructor(Defaulted)
		~ActionCreateAction() = default;

		/// Creates an action
		/// @Param worldState: The world state object that stores the current world state
		virtual void update(WorldState& worldState) override;
		
		/// Mutator method for the action being created
		/// @Param name: The name of the action being created
		void setPrototype(const std::string& name);

		/// Accessor method for the action being created
		/// @Return: The name of the action being created
		std::string getPrototype() const;

	private:
		std::string mPrototype; /// The type of class being constructed
	};

	ActionFactory(ActionCreateAction)
}

