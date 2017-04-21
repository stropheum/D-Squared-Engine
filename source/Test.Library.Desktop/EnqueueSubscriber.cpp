#include "pch.h"
#include "EnqueueSubscriber.h"
#include "Foo.h"
#include "Event.h"
#include "EventQueue.h"
#include "GameTime.h"


using namespace Library;

EnqueueSubscriber::EnqueueSubscriber(Library::EventQueue& eventQueue, Library::GameTime& gametime, std::chrono::milliseconds delay):
	mEventQueue(&eventQueue), mGameTime(gametime), mDelay(delay)
{
	Event<std::int32_t>::subscribe(*this);
}

EnqueueSubscriber::~EnqueueSubscriber()
{
	Event<std::int32_t>::unsubscribe(*this);
}

void EnqueueSubscriber::notify(const Library::EventPublisher& event)
{
	if (event.Is(Event<std::int32_t>::TypeIdClass()))
	{
		std::int32_t message = event.As<Event<std::int32_t>>()->message();
		Event<std::int32_t> newEvent(message);
		mEventQueue->enqueue(newEvent, mGameTime, mDelay);
	}
}
