#include "pch.h"
#include "EventPublisher.h"


using namespace std;
using namespace chrono;

namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)

	EventPublisher::EventPublisher(Vector<EventSubscriber*>* subscriberList, 
		mutex& subscriberListMutex, bool deleteAfterPublishing) :
		mDeleteAfterPublishing(deleteAfterPublishing), mTimeEnqueued(), mMillisecondDelay(0), 
		mSubscriberList(subscriberList), mSubscriberListMutex(&subscriberListMutex)
	{}

	EventPublisher::EventPublisher(const EventPublisher& rhs) :
		mDeleteAfterPublishing(rhs.mDeleteAfterPublishing), mTimeEnqueued(rhs.mTimeEnqueued), 
		mMillisecondDelay(rhs.mMillisecondDelay), mSubscriberList(rhs.mSubscriberList), 
		mSubscriberListMutex(rhs.mSubscriberListMutex)
	{}

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

	EventPublisher::EventPublisher(EventPublisher&& rhs) noexcept:
		mDeleteAfterPublishing(rhs.mDeleteAfterPublishing), mTimeEnqueued(rhs.mTimeEnqueued), 
		mMillisecondDelay(rhs.mMillisecondDelay), mSubscriberList(rhs.mSubscriberList), 
		mSubscriberListMutex(rhs.mSubscriberListMutex)
	{
		rhs.mMillisecondDelay = milliseconds(0);
		rhs.mSubscriberList = nullptr;
	}

	EventPublisher& EventPublisher::operator=(EventPublisher&& rhs) noexcept
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

	void EventPublisher::SetTime(const high_resolution_clock::time_point& timePoint, 
		const milliseconds& millisecondDelay)
	{
		mTimeEnqueued = timePoint;
		mMillisecondDelay = millisecondDelay;
	}

	high_resolution_clock::time_point EventPublisher::TimeEnqueued() const
	{
		return mTimeEnqueued;
	}

	chrono::milliseconds EventPublisher::Delay() const
	{
		return mMillisecondDelay;
	}

	bool EventPublisher::IsExpired(const chrono::high_resolution_clock::time_point& timePoint) const
	{
		return timePoint > (mTimeEnqueued + mMillisecondDelay);
	}

	void EventPublisher::Deliver() const
	{
		vector<future<void>> futures;
		{
			lock_guard<mutex> guard(*mSubscriberListMutex);
			Vector<EventSubscriber*> subListCopy(*mSubscriberList);
			for (uint32_t i = 0; i < subListCopy.Size(); i++)
			{
				EventSubscriber* subscriber = subListCopy[i];
				futures.emplace_back(async(&EventSubscriber::Notify, subscriber, cref(*this)));
			}
		}

		for (auto& future : futures)
		{	// Synchronize the threads before attempting to delete this event publisher
			future.get();
		}

		if (DeleteAfterPublishing())
		{	// If the publisher is marked for delete, delete it now 
			delete this;
		}
	}

	bool EventPublisher::DeleteAfterPublishing() const
	{
		return mDeleteAfterPublishing;
	}
}

