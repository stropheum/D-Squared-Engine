#pragma once
#include "Event.h"
#include "EventSubscriber.h"


namespace Library
{
	template <typename Payload>
	RTTI_DEFINITIONS(Event<Payload>)

	template <typename Payload>
	Vector<class EventSubscriber*> Event<Payload>::sSubscriberList;

	template <typename Payload>
	Event<Payload>::Event(const Payload& payload):
		EventPublisher(&sSubscriberList), mPayload(payload)
	{
	}

	template <typename Payload>
	Event<Payload>::Event(const Event<Payload>& rhs):
		EventPublisher(rhs.sSubscriberList), mPayload(rhs.mPayload)
	{
	}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(const Event<Payload>& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement assignment operator
		return *this;
	}

	template <typename Payload>
	Event<Payload>::Event(Event<Payload>&& rhs):
		EventPublisher(rhs.sSubscriberList), mPayload(rhs.mPayload)
	{
		//TODO: Implement move copy constructor
	}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(Event<Payload>&& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement move assignment operator
		return *this;
	}

	template <typename Payload>
	void Event<Payload>::subscribe(EventSubscriber& eventSubscriber)
	{
		sSubscriberList.pushBack(&eventSubscriber);
	}

	template <typename Payload>
	void Event<Payload>::unsubscribe(EventSubscriber& eventSubscriber)
	{
		sSubscriberList.remove(&eventSubscriber);
	}

	template <typename Payload>
	void Event<Payload>::unsubscribeAll()
	{
		sSubscriberList.clear();
	}

	template <typename Payload>
	const Payload& Event<Payload>::message()
	{
		return mPayload;
	}
}
