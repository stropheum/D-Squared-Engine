#pragma once
#include "EventPublisher.h"
#include "Vector.h"


namespace Library
{
	template <typename Payload> class Event final :
		public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:
		Event(const Payload& payload);
		~Event() = default;

		Event(const Event<Payload>& rhs);
		Event<Payload>& operator=(const Event<Payload>& rhs);

		Event(Event<Payload>&& rhs);
		Event<Payload>& operator=(Event<Payload>&& rhs);

		static void subscribe(class EventSubscriber& eventSubscriber);
		static void unsubscribe(class EventSubscriber& eventSubscriber);
		static void unsubscribeAll();
		const Payload& message();

	private:
		Payload mPayload;
		static Vector<class EventSubscriber*> sSubscriberList;
	};
}

#include "Event.inl"

