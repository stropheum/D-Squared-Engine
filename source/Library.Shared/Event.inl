#pragma once
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
	Event<Payload>::Event(const Payload& payload, bool deleteAfterPublishing) :
		EventPublisher(&sSubscriberList, sSubscriberListMutex, deleteAfterPublishing), mPayload(payload)
	{}

	template <typename Payload>
	Event<Payload>::Event(const Event<Payload>& rhs) :
		EventPublisher(rhs), mPayload(rhs.mPayload)
	{}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(const Event<Payload>& rhs)
	{
		if (this != &rhs)
		{
			EventPublisher::operator=(rhs);
			mPayload = rhs.mPayload;
			mDeleteAfterPublishing = rhs.mDeleteAfterPublishing;
		}
		return *this;
	}

	template <typename Payload>
	Event<Payload>::Event(Event<Payload>&& rhs) noexcept :
		EventPublisher(std::move(rhs)), mPayload(std::move(rhs.mPayload))
	{}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(Event<Payload>&& rhs) noexcept
	{
		if (this != &rhs)
		{
			EventPublisher::operator=(std::move(rhs));
			mPayload = std::move(rhs.mPayload);
		}
		return *this;
	}

	template <typename Payload>
	void Event<Payload>::Subscribe(EventSubscriber& eventSubscriber)
	{
		sSubscriberList.PushBack(&eventSubscriber);
	}

	template <typename Payload>
	void Event<Payload>::Unsubscribe(EventSubscriber& eventSubscriber)
	{
		sSubscriberList.Remove(&eventSubscriber);
	}

	template <typename Payload>
	void Event<Payload>::UnsubscribeAll()
	{
		std::lock_guard<std::mutex> guard(sSubscriberListMutex);
		if (!sSubscriberList.IsEmpty())
		{
			sSubscriberList.Clear();
		}
	}

	template <typename Payload>
	const Payload& Event<Payload>::Message()
	{
		return mPayload;
	}
}
