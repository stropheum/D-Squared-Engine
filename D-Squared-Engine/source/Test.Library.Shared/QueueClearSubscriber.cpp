#include "pch.h"
#include "QueueClearSubscriber.h"
#include "Event.h"
#include "Foo.h"
#include "EventQueue.h"


using namespace Library;
using namespace std;

QueueClearSubscriber::QueueClearSubscriber(EventQueue& eventQueue) :
    m_eventQueue(&eventQueue)
{
    Event<Foo>::Subscribe(*this);
}

QueueClearSubscriber::~QueueClearSubscriber()
{
    Event<Foo>::Unsubscribe(*this);
}

void QueueClearSubscriber::Notify(const Library::EventPublisher& event)
{
    if (event.Is(Event<Foo>::TypeIdClass()))
    {
        m_eventQueue->Clear();
    }
}