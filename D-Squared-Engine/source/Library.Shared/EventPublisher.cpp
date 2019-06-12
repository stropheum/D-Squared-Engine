#include "pch.h"
#include "EventPublisher.h"


using namespace std;
using namespace chrono;

namespace Library
{
    RTTI_DEFINITIONS(EventPublisher);

    EventPublisher::EventPublisher(
        Vector<EventSubscriber*>* subscriberList,
        mutex& subscriberListMutex, bool deleteAfterPublishing) :
        m_deleteAfterPublishing(deleteAfterPublishing), 
        m_timeEnqueued(), 
        m_millisecondDelay(0),
        m_subscriberList(subscriberList), 
        m_subscriberListMutex(&subscriberListMutex)
    {}

    EventPublisher::EventPublisher(const EventPublisher& rhs) :
        m_deleteAfterPublishing(rhs.m_deleteAfterPublishing), 
        m_timeEnqueued(rhs.m_timeEnqueued),
        m_millisecondDelay(rhs.m_millisecondDelay), 
        m_subscriberList(rhs.m_subscriberList),
        m_subscriberListMutex(rhs.m_subscriberListMutex)
    {}

    EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
    {
        if (this != &rhs)
        {
            m_timeEnqueued = rhs.m_timeEnqueued;
            m_millisecondDelay = rhs.m_millisecondDelay;
            m_subscriberList = rhs.m_subscriberList;
            m_subscriberListMutex = rhs.m_subscriberListMutex;
        }
        return *this;
    }

    EventPublisher::EventPublisher(EventPublisher&& rhs) noexcept :
        m_deleteAfterPublishing(rhs.m_deleteAfterPublishing), 
        m_timeEnqueued(rhs.m_timeEnqueued),
        m_millisecondDelay(rhs.m_millisecondDelay), 
        m_subscriberList(rhs.m_subscriberList),
        m_subscriberListMutex(rhs.m_subscriberListMutex)
    {
        rhs.m_millisecondDelay = milliseconds(0);
        rhs.m_subscriberList = nullptr;
    }

    EventPublisher& EventPublisher::operator=(EventPublisher&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_timeEnqueued = rhs.m_timeEnqueued;
            m_millisecondDelay = rhs.m_millisecondDelay;
            m_subscriberList = rhs.m_subscriberList;
            m_subscriberListMutex = rhs.m_subscriberListMutex;

            rhs.m_millisecondDelay = milliseconds(0);
            rhs.m_subscriberList = nullptr;
        }

        return *this;
    }

    void EventPublisher::SetTime(
        const high_resolution_clock::time_point& timePoint,
        const milliseconds& millisecondDelay)
    {
        m_timeEnqueued = timePoint;
        m_millisecondDelay = millisecondDelay;
    }

    high_resolution_clock::time_point EventPublisher::TimeEnqueued() const
    {
        return m_timeEnqueued;
    }

    chrono::milliseconds EventPublisher::Delay() const
    {
        return m_millisecondDelay;
    }

    bool EventPublisher::IsExpired(const chrono::high_resolution_clock::time_point& timePoint) const
    {
        return timePoint > (m_timeEnqueued + m_millisecondDelay);
    }

    void EventPublisher::Deliver() const
    {
        vector<future<void>> futures;
        {
            lock_guard<mutex> guard(*m_subscriberListMutex);
            Vector<EventSubscriber*> subListCopy(*m_subscriberList);
            for (uint32_t i = 0; i < subListCopy.Size(); i++)
            {
                EventSubscriber* subscriber = subListCopy[i];
                futures.emplace_back(async(&EventSubscriber::Notify, subscriber, cref(*this)));
            }
        }

        for (auto& future : futures)
        {	// Synchronize the threads before attempting to delete this event publisher
            future.get();
        }

        if (DeleteAfterPublishing())
        {	// If the publisher is marked for delete, delete it now 
            delete this;
        }
    }

    bool EventPublisher::DeleteAfterPublishing() const
    {
        return m_deleteAfterPublishing;
    }
}