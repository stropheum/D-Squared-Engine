#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "World.h"


namespace Library
{
	ReactionAttributed::ReactionAttributed()
	{
		(*this)["Subtype"].setType(DatumType::String);
		Event<EventMessageAttributed>::subscribe(*this);
	}

	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::unsubscribe(*this);
	}

	void ReactionAttributed::notify(const EventPublisher& event)
	{
		assert(event.Is(Event<EventMessageAttributed>::TypeIdClass()));

		auto castEvent = event.As<Event<EventMessageAttributed>>();
		if (castEvent->message().getSubtype() == getSubType())
		{
			auto auxAttributes = getAuxilliaryAttributes();
			for (auto iter = auxAttributes.begin(); iter != auxAttributes.end(); ++iter)
			{
				Datum& appendedDatum = appendAuxiliaryAttribute((*iter).first);
				appendedDatum = (*iter).second;
			}

			auto worldState = castEvent->message().getWorldState();
			if (worldState != nullptr)
			{
				update(*worldState);
			}
		}
	}

	const std::string& ReactionAttributed::getSubType()
	{
		return (*this)["SubType"].get<std::string>();
	}
}
