#pragma once
#include "Scope.h"


namespace Library
{
	class WorldState;

	class EventMessageAttributed final:
		public Scope
	{
	public:

		/**
		 * Constructor
		 */
		EventMessageAttributed();

		/**
		 * Default destructor
		 */
		virtual ~EventMessageAttributed() = default;

		/**
		 * Accessor for the event Message attributed subtype
		 * @Return: The subtype of the event Message attributed
		 */
		const std::string& GetSubtype() const;

		/**
		 * Mutator for the event Message attributed subtype
		 * @Param subtype: The subtype of the event Message attributed
		 */
		void SetSubtype(const std::string& subtype);

		/**
		 * Accessor for the world state
		 * @Return: A pointer to the world state
		 */
		WorldState* GetWorldState() const;

		/**
		 * Mutator for the world state poitner
		 * @Param worldState: the world state
		 */
		void SetWorldState(WorldState& worldState);

	private:

		std::string mSubtype; // The subtype of the event Message attributed
		WorldState* mWorldState; // The world state object
	};
}