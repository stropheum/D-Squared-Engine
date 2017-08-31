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
	virtual void notify(const Library::EventPublisher& event) override;
private:
	Library::EventQueue* mEventQueue;
	Library::GameTime mGameTime;
	std::chrono::milliseconds mDelay;
};

