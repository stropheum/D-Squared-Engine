#pragma once
#include "Reaction.h"


namespace Library
{
	class ReactionAttributed final:
		public Reaction
	{
	public:
		ReactionAttributed();
		~ReactionAttributed();
		virtual void notify(const EventPublisher& event) override;
		const std::string& getSubType();
	};

	ReactionFactory(ReactionAttributed)
}

