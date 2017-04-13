#pragma once
#include "Reaction.h"


namespace Library
{
	class ReactionAttributed :
		public Reaction
	{
	public:
		ReactionAttributed();
		~ReactionAttributed();
		virtual void notify(const EventPublisher& event) override;
	};

	ReactionFactory(ReactionAttributed)
}

