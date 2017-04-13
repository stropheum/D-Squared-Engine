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
		Reaction() = default;
		virtual ~Reaction() = default;
	};

#define ReactionFactory(ConcreteReaction) ConcreteFactory(Reaction, ConcreteReaction)
}
