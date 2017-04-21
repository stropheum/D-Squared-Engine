#include "pch.h"
#include "ListClearingSubscriber.h"
#include <cassert>
#include "Event.h"
#include "Foo.h"


ListClearingSubscriber::ListClearingSubscriber()
{
	Library::Event<Foo>::subscribe(*this);
}


ListClearingSubscriber::~ListClearingSubscriber()
{
//	Library::Event<Foo>::unsubscribe(*this);
}

void ListClearingSubscriber::notify(const Library::EventPublisher& event)
{
	std::lock_guard<std::mutex> guard(mNotifyMutex);
	if (event.Is(Library::Event<Foo>::TypeIdClass()))
	{
		Library::Event<Foo>::unsubscribe(*this);
	}
}
