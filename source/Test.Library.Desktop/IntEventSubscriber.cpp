#include "pch.h"
#include "IntEventSubscriber.h"
#include "Event.h"
#include <cassert>


IntEventSubscriber::IntEventSubscriber() :
	mValue(0), mNotified(false)
{
	Library::Event<std::int32_t>::subscribe(*this);
}


IntEventSubscriber::~IntEventSubscriber()
{
	Library::Event<std::int32_t>::unsubscribe(*this);
}

void IntEventSubscriber::notify(const Library::EventPublisher& event)
{
	assert(event.Is(Library::Event<std::int32_t>::TypeIdClass()));
	if (event.Is(Library::Event<int32_t>::TypeIdClass()))
	{
		std::lock_guard<std::mutex> guard(mMutex);
		mValue = event.As<Library::Event<int32_t>>()->message();
		mNotified = true;
	}
}
