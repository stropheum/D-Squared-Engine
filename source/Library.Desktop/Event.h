#pragma once
#include "EventPublisher.h"
#include "Vector.h"


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

	private:
		Payload mPayload;
		static Vector<EventSubscriber> mSubscriberList;
	};
}

#include "Event.inl"

