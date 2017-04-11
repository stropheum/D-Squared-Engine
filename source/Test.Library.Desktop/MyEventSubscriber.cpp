#include "pch.h"
#include "MyEventSubscriber.h"
#include "Event.h"


namespace Library
{
	MyEventSubscriber::MyEventSubscriber():
		mValue(0)
	{
		Event<std::int32_t>::subscribe(*this);
	}

	MyEventSubscriber::~MyEventSubscriber()
	{
		Event<std::int32_t>::unsubscribe(*this);
	}

	void MyEventSubscriber::notify(const EventPublisher& event)
	{
		Event<std::int32_t>* myEvent = event.As<Event<std::int32_t>>();
		if (myEvent != nullptr)
		{
			mValue = myEvent->message();
		}
	}
}
