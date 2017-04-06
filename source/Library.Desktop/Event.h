#pragma once
#include "EventPublisher.h"


namespace Library
{
	template <typename Payload> class Event :
		public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:
		Event();
		~Event() = default;

		Event(const Event<Payload>& rhs);
		Event<Payload>& operator=(const Event<Payload>& rhs);

		Event(Event<Payload>&& rhs);
		Event<Payload>& operator=(Event<Payload>&& rhs);

		static void subscribe(class EventSubscriber& eventSubscriber);
		static void unsubscribeAll();
		Payload& message();
	};

	
}

#include "Event.inl"

