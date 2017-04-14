#pragma once
#include "Action.h"


namespace Library
{
	class ActionEvent final:
		public Action
	{
	public:

		/// Constructor
		ActionEvent();

		/// Destructor
		~ActionEvent() = default;

		/// Updates the game state
		/// @Param worldState: The worldstate object storing information about the world
		virtual void update(class WorldState& worldState) override;
	};

	ActionFactory(ActionEvent)
}

