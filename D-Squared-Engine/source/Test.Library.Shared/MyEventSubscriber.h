#pragma once
#include "EventSubscriber.h"
#include "Foo.h"


namespace Library
{
    class MyEventSubscriber :
        public EventSubscriber
    {
    public:

        // Constructor. Automatically subscribes to Events of Type "Foo"
        MyEventSubscriber();

        // Destructor. Automatically unsubscribes from Events of Type "Foo"
        ~MyEventSubscriber();

        // Notify method. Called when an event of Type "Foo" is triggered
        // @Param event: The event that this object is being notified of
        virtual void Notify(const EventPublisher& event) override;

        Foo m_value; // Used to store a copy of the payload of the event for debuggin purposes
    };
}