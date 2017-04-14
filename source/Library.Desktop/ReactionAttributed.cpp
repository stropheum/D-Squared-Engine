#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "EventMessageAttributed.h"


namespace Library
{
	ReactionAttributed::ReactionAttributed()
	{
		(*this)["Subtype"].setType(DatumType::String);
	}

	void ReactionAttributed::notify(const EventPublisher& event)
	{
		assert(event.Is(Event<EventMessageAttributed>::TypeIdClass()));

		auto castEvent = event.As<Event<EventMessageAttributed>>();
		if (castEvent->message().getSubtype() == getSubType())
		{
			// TODO: Copy the attribute "arguments" to this instance of reaction attributed, then execute ActionList::Update
		}
	}

	const std::string& ReactionAttributed::getSubType()
	{
		return (*this)["SubType"].get<std::string>();
	}
}
