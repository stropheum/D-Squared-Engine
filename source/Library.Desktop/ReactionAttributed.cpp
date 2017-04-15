#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "World.h"
#include "Scope.h"


namespace Library
{
	ReactionAttributed::ReactionAttributed()
	{
		(*this)["Subtype"].setType(DatumType::String);
//		mPrescribedAttributes.pushBack(Signature("Subtype", DatumType::String, "", 1u, static_cast<std::string*>(nullptr)));
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
		
		assert(castEvent->message().Is(EventMessageAttributed::TypeIdClass()));
		auto message = castEvent->message().As<EventMessageAttributed>();

		if (message->getSubtype() == getSubType())
		{
			for (auto iter = message->begin(); iter != message->end(); ++iter)
			{
				auto& datum = appendAuxiliaryAttribute((*iter).first);
				datum = (*iter).second;
			}

//			for (auto iter = auxAttributes.begin(); iter != auxAttributes.end(); ++iter)
//			{
//				Datum& appendedDatum = appendAuxiliaryAttribute((*iter).first);
//				appendedDatum = *(*iter).second;
//			}
//
//			auto worldState = castEvent->message().getWorldState();
//			if (worldState != nullptr)
//			{
//				update(*worldState);
//			}
		}
	}

	const std::string& ReactionAttributed::getSubType()
	{
		return (*this)["SubType"].get<std::string>();
	}
}
