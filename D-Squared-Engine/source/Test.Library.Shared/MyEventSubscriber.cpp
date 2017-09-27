#include "pch.h"
#include "MyEventSubscriber.h"
#include "Event.h"
#include <cassert>


namespace Library
{
	MyEventSubscriber::MyEventSubscriber():
		mValue(0)
	{
		Event<Foo>::Subscribe(*this);
	}

	MyEventSubscriber::~MyEventSubscriber()
	{
		Event<Foo>::Unsubscribe(*this);
	}

	void MyEventSubscriber::Notify(const EventPublisher& event)
	{
		std::lock_guard<std::mutex> guard(mNotifyMutex);
		assert(event.Is(Event<Foo>::TypeIdClass()));
		Event<Foo>* myEvent = event.As<Event<Foo>>();
		if (myEvent != nullptr)
		{
			mValue = myEvent->Message();
		}
	}
}
