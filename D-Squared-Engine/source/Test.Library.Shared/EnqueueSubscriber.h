#pragma once
#include "EventSubscriber.h"
#include "EventQueue.h"
#include "GameTime.h"

class EnqueueSubscriber :
    public Library::EventSubscriber
{
public:
    explicit EnqueueSubscriber(Library::EventQueue& eventQueue, Library::GameTime& gametime, std::chrono::milliseconds delay);
    ~EnqueueSubscriber();
    virtual void Notify(const Library::EventPublisher& event) override;
private:
    Library::EventQueue* m_eventQueue;
    Library::GameTime m_gameTime;
    std::chrono::milliseconds m_delay;
};