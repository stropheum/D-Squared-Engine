#include "pch.h"
#include "QueueClearSubscriber.h"
#include "Event.h"
#include "Foo.h"
#include "EventQueue.h"


using namespace Library;
using namespace std;

QueueClearSubscriber::QueueClearSubscriber(EventQueue& eventQueue):
	mEventQueue(&eventQueue)
{
	Event<Foo>::subscribe(*this);
}


QueueClearSubscriber::~QueueClearSubscriber()
{
	Event<Foo>::unsubscribe(*this);
}

void QueueClearSubscriber::notify(const Library::EventPublisher& event)
{
	if (event.Is(Event<Foo>::TypeIdClass()))
	{
		mEventQueue->clear();
	}
}
