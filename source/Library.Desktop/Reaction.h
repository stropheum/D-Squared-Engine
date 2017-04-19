#pragma once
#include "EventSubscriber.h"
#include "ActionList.h"


namespace Library
{
	class Reaction abstract : 
		public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)

	public:

		/// Default constructor
		Reaction() = default;

		/// Default destructor
		virtual ~Reaction() = default;
	};

#define ReactionFactory(ConcreteReaction) ConcreteFactory(Reaction, ConcreteReaction)
}
