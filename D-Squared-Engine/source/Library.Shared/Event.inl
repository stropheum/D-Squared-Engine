#pragma once
#include "EventSubscriber.h"
#include <mutex>


namespace Library
{
    template <typename Payload>
    RTTI_DEFINITIONS(Event<Payload>);

    template <typename Payload>
    Vector<class EventSubscriber*> Event<Payload>::s_subscriberList;

    template <typename Payload>
    std::mutex Event<Payload>::s_subscriberListMutex;

    template <typename Payload>
    Event<Payload>::Event(
        const Payload& payload, 
        bool deleteAfterPublishing) :
        EventPublisher(
            &s_subscriberList, 
            s_subscriberListMutex, 
            deleteAfterPublishing), 
        m_payload(payload)
    {}

    template <typename Payload>
    Event<Payload>::Event(const Event<Payload>& rhs) :
        EventPublisher(rhs), 
m_payload(rhs.m_payload)
    {}

    template <typename Payload>
    Event<Payload>& Event<Payload>::operator=(const Event<Payload>& rhs)
    {
        if (this != &rhs)
        {
            EventPublisher::operator=(rhs);
            m_payload = rhs.m_payload;
            m_deleteAfterPublishing = rhs.m_deleteAfterPublishing;
        }
        return *this;
    }

    template <typename Payload>
    Event<Payload>::Event(Event<Payload>&& rhs) noexcept :
        EventPublisher(std::move(rhs)), m_payload(std::move(rhs.m_payload))
    {}

    template <typename Payload>
    Event<Payload>& Event<Payload>::operator=(Event<Payload>&& rhs) noexcept
    {
        if (this != &rhs)
        {
            EventPublisher::operator=(std::move(rhs));
            m_payload = std::move(rhs.m_payload);
        }
        return *this;
    }

    template <typename Payload>
    void Event<Payload>::Subscribe(EventSubscriber& eventSubscriber)
    {
        s_subscriberList.PushBack(&eventSubscriber);
    }

    template <typename Payload>
    void Event<Payload>::Unsubscribe(EventSubscriber& eventSubscriber)
    {
        s_subscriberList.Remove(&eventSubscriber);
    }

    template <typename Payload>
    void Event<Payload>::UnsubscribeAll()
    {
        std::lock_guard<std::mutex> guard(s_subscriberListMutex);
        if (!s_subscriberList.IsEmpty())
        {
            s_subscriberList.Clear();
        }
    }

    template <typename Payload>
    const Payload& Event<Payload>::Message()
    {
        return m_payload;
    }
}