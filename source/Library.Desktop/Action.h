#pragma once
#include "Attributed.h"
#include "Factory.h"

namespace Library
{
#define ActionFactory(ConcreteAction) ConcreteFactory(Action, ConcreteAction)

	class Action :
		public Library::Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)

	public:

		/// Constructor
		Action();

		/// Default destructor
		~Action() = default;

		/// Updates the game state
		/// @Param worldState: The worldstate object storing information about the world
		virtual void update(class WorldState& worldState) = 0;

		/// Accessor method for the name of the action
		/// @Return: The name of the action
		std::string name() const;

		/// Mutator method for the name of the action
		/// @Param name: The new name of the action
		void setName(const std::string& name);

	protected:
		std::string mName; /// The name of the action
	};
}


