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
	Event<std::int32_t>::Subscribe(*this);
}

EnqueueSubscriber::~EnqueueSubscriber()
{
	Event<std::int32_t>::Unsubscribe(*this);
}

void EnqueueSubscriber::Notify(const Library::EventPublisher& event)
{
	if (event.Is(Event<std::int32_t>::TypeIdClass()))
	{
		std::int32_t message = event.As<Event<std::int32_t>>()->Message();
		Event<std::int32_t> newEvent(message);
		mEventQueue->Enqueue(newEvent, mGameTime, mDelay);
	}
}
