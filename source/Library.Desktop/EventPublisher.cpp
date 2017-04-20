#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include <vector>
#include <future>


using namespace std::chrono;

namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)

	EventPublisher::EventPublisher(Vector<EventSubscriber*>* subscriberList, std::mutex& subscriberListMutex, bool deleteAfterPublishing):
		mDeleteAfterPublishing(deleteAfterPublishing), mTimeEnqueued(), mMillisecondDelay(0), mSubscriberList(subscriberList), mSubscriberListMutex(&subscriberListMutex)
	{
	}

	EventPublisher::EventPublisher(const EventPublisher& rhs):
		mDeleteAfterPublishing(rhs.mDeleteAfterPublishing), mTimeEnqueued(rhs.mTimeEnqueued), 
		mMillisecondDelay(rhs.mMillisecondDelay), mSubscriberList(rhs.mSubscriberList), mSubscriberListMutex(rhs.mSubscriberListMutex)
	{
	}

	EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
	{
		if (this != &rhs)
		{
			mTimeEnqueued = rhs.mTimeEnqueued;
			mMillisecondDelay = rhs.mMillisecondDelay;
			mSubscriberList = rhs.mSubscriberList;
			mSubscriberListMutex = rhs.mSubscriberListMutex;
		}
		return *this;
	}

	EventPublisher::EventPublisher(EventPublisher&& rhs):
		mDeleteAfterPublishing(rhs.mDeleteAfterPublishing), mTimeEnqueued(rhs.mTimeEnqueued), 
		mMillisecondDelay(rhs.mMillisecondDelay), mSubscriberList(rhs.mSubscriberList), mSubscriberListMutex(rhs.mSubscriberListMutex)
	{
		rhs.mMillisecondDelay = milliseconds(0);
		rhs.mSubscriberList = nullptr;
	}

	EventPublisher& EventPublisher::operator=(EventPublisher&& rhs)
	{
		if (this != &rhs)
		{
			mTimeEnqueued = rhs.mTimeEnqueued;
			mMillisecondDelay = rhs.mMillisecondDelay;
			mSubscriberList = rhs.mSubscriberList;
			mSubscriberListMutex = rhs.mSubscriberListMutex;

			rhs.mMillisecondDelay = milliseconds(0);
			rhs.mSubscriberList = nullptr;
		}

		return *this;
	}

	void EventPublisher::setTime(const high_resolution_clock::time_point& timePoint, milliseconds millisecondDelay)
	{
		mTimeEnqueued = timePoint;
		mMillisecondDelay = millisecondDelay;
	}

	high_resolution_clock::time_point EventPublisher::timeEnqueued() const
	{
		return mTimeEnqueued;
	}

	std::chrono::milliseconds EventPublisher::delay() const
	{
		return mMillisecondDelay;
	}

	bool EventPublisher::isExpired(const std::chrono::high_resolution_clock::time_point& timePoint) const
	{
		return timePoint > (mTimeEnqueued + mMillisecondDelay);
	}

	void EventPublisher::deliver()
	{
		std::vector<std::future<void>> futures;
		{
			std::lock_guard<std::mutex> guard(*mSubscriberListMutex);
			Vector<EventSubscriber*> subListCopy(*mSubscriberList);
			for (auto iter = subListCopy.begin(); iter != subListCopy.end(); ++iter)
			{
				EventSubscriber* subscriber = *iter;
				futures.emplace_back(std::async(std::launch::async, [&]
				{
					subscriber->notify(*this);
				}));
			}
		}

		for (auto& future : futures)
		{	// Synchronize the threads before attempting to delete this event publisher
			future.get();
		}

		if (deleteAfterPublishing())
		{	// If the publisher is marked for delete, delete it now 
			delete this;
		}
	}

	bool EventPublisher::deleteAfterPublishing() const
	{
		return mDeleteAfterPublishing;
	}
}

