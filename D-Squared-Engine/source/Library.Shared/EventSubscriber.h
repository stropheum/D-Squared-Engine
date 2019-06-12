#pragma once
#include "EventPublisher.h"


namespace Library
{
    class EventSubscriber
    {

    public:

#pragma region Construction/Copy/Assignment

        EventSubscriber() = default;

        virtual ~EventSubscriber() = default;

        EventSubscriber(const EventSubscriber& rhs) = delete;

        EventSubscriber& operator=(const EventSubscriber& rhs) = delete;

        EventSubscriber(EventSubscriber&& rhs) = delete;

        EventSubscriber& operator=(EventSubscriber&& rhs) = delete;

#pragma endregion

        /**
         * Notifies the subscriber that an event has been triggered
         * @Param event: The event that the subscriber is being notified of
         */
        virtual void Notify(const EventPublisher& event) = 0;

    protected:

        std::mutex m_notifyMutex; // Mutex to prevent multiple accesses to the event subscriber

    };
}