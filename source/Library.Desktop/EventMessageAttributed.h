#pragma once
#include "Scope.h"


namespace Library
{
	class WorldState;

	class EventMessageAttributed final:
		public Scope
	{
	public:

		/// Constructor
		EventMessageAttributed();

		/// Default destructor
		virtual ~EventMessageAttributed() = default;

		/// Accessor for the event message attributed subtype
		/// @Return: The subtype of the event message attributed
		const std::string& getSubtype() const;

		/// Mutator for the event message attributed subtype
		/// @Param subtype: The subtype of the event message attributed
		void setSubtype(const std::string& subtype);

		/// Accessor for the world state
		/// @Return: A pointer to the world state
		WorldState* getWorldState() const;

		/// Mutator for the world state poitner
		/// @Param worldState: the world state
		void setWorldState(WorldState& worldState);

	private:
		std::string mSubtype; /// The subtype of the event message attributed
		WorldState* mWorldState; /// The world state object
	};
}