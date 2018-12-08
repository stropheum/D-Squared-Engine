#pragma once
#include "EventSubscriber.h"

namespace Library {
    class EventQueue;
}

class QueueClearSubscriber :
    public Library::EventSubscriber
{
public:
    QueueClearSubscriber(Library::EventQueue& eventQueue);
    ~QueueClearSubscriber();
    virtual void Notify(const Library::EventPublisher& event) override;
private:
    Library::EventQueue* mEventQueue;
};