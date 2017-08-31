#include "pch.h"
#include "MyEventSubscriber.h"
#include "Event.h"
#include <cassert>


namespace Library
{
	MyEventSubscriber::MyEventSubscriber():
		mValue(0)
	{
		Event<Foo>::subscribe(*this);
	}

	MyEventSubscriber::~MyEventSubscriber()
	{
		Event<Foo>::unsubscribe(*this);
	}

	void MyEventSubscriber::notify(const EventPublisher& event)
	{
		std::lock_guard<std::mutex> guard(mNotifyMutex);
		assert(event.Is(Event<Foo>::TypeIdClass()));
		Event<Foo>* myEvent = event.As<Event<Foo>>();
		if (myEvent != nullptr)
		{
			mValue = myEvent->message();
		}
	}
}
