#pragma once
#include "Event.h"
#include "EventSubscriber.h"
#include <mutex>


namespace Library
{
	template <typename Payload>
	RTTI_DEFINITIONS(Event<Payload>)

	template <typename Payload>
	Vector<class EventSubscriber*> Event<Payload>::sSubscriberList;

	template <typename Payload>
	std::mutex Event<Payload>::sSubscriberListMutex;

	template <typename Payload>
	Event<Payload>::Event(const Payload& payload, bool deleteAfterPublishing):
		EventPublisher(&sSubscriberList, sSubscriberListMutex, deleteAfterPublishing), mPayload(payload)
	{
	}

	template <typename Payload>
	Event<Payload>::Event(const Event<Payload>& rhs):
		EventPublisher(&rhs.sSubscriberList, sSubscriberListMutex, rhs.mDeleteAfterPublishing), mPayload(rhs.mPayload)
	{
	}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(const Event<Payload>& rhs)
	{
		if (this != &rhs)
		{
			mPayload = rhs.mPayload;
			mDeleteAfterPublishing = rhs.mDeleteAfterPublishing;
		}
		return *this;
	}

	template <typename Payload>
	Event<Payload>::Event(Event<Payload>&& rhs):
		EventPublisher(&rhs.sSubscriberList, sSubscriberListMutex, rhs.mDeleteAfterPublishing), mPayload(rhs.mPayload)
	{
	}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(Event<Payload>&& rhs)
	{
		if (this != &rhs)
		{
			mPayload = rhs.mPayload;
			mDeleteAfterPublishing = rhs.mDeleteAfterPublishing;
		}
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
		std::lock_guard<std::mutex> guard(sSubscriberListMutex);
		if (!sSubscriberList.isEmpty())
		{
			sSubscriberList.clear();
		}
	}

	template <typename Payload>
	const Payload& Event<Payload>::message()
	{
		return mPayload;
	}
}
