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
		(*this)["Subtype"].SetType(DatumType::String);
		(*this)["Subtype"] = "";
		mPrescribedAttributes.PushBack(
			Signature("Subtype", DatumType::String, 1u, static_cast<std::string*>(nullptr)));
		Event<EventMessageAttributed>::Subscribe(*this);
	}

	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::Unsubscribe(*this);
	}

	void ReactionAttributed::Notify(const EventPublisher& event)
	{
		assert(event.Is(Event<EventMessageAttributed>::TypeIdClass()));

		auto castEvent = event.As<Event<EventMessageAttributed>>();
		
		assert(castEvent->Message().Is(EventMessageAttributed::TypeIdClass()));
		EventMessageAttributed* message = castEvent->Message().As<EventMessageAttributed>();

		auto lhs = message->GetSubtype();
		auto rhs = GetSubtype();

		if (lhs == rhs)
		{
			for (auto iter = message->begin(); iter != message->end(); ++iter)
			{
				auto& datum = AppendAuxiliaryAttribute((*iter).first);
				datum.SetType((*iter).second.Type());
				datum = (*iter).second;
			}
		}
	}

	std::string ReactionAttributed::GetSubtype()
	{
		return (*this)["Subtype"].Get<std::string>(0);
	}

	void ReactionAttributed::SetSubtype(const std::string& subtype)
	{
		(*this)["Subtype"] = subtype;
	}
}
