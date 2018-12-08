#pragma once
#include "EventSubscriber.h"

class IntEventSubscriber :
    public Library::EventSubscriber
{
public:

    /// Constructor. Automatically subscribes to Events of Type "Foo"
    IntEventSubscriber();

    /// Destructor. Automatically unsubscribes from Events of Type "Foo"
    ~IntEventSubscriber();

    /// Notify method. Called when an event of type "Foo" is triggered
    /// @Param event: The event that this object is being notified of
    virtual void Notify(const Library::EventPublisher& event) override;

    std::int32_t mValue;
    bool mNotified;
    std::mutex mMutex;
};