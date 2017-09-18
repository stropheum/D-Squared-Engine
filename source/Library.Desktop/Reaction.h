#pragma once
#include "EventSubscriber.h"
#include "ActionList.h"


namespace Library
{
	class Reaction abstract : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)

	public:

#pragma region Construction/Copy/Assignment

		Reaction() = default;

		virtual ~Reaction() = default;

		Reaction(const Reaction& rhs) = delete;

		Reaction& operator=(const Reaction& rhs) = delete;

		Reaction(Reaction&& rhs) = delete;

		Reaction& operator=(Reaction&& rhs) = delete;

#pragma endregion

	};

#define ReactionFactory(ConcreteReaction) ConcreteFactory(Reaction, ConcreteReaction)
}
