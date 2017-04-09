#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"


using namespace std::chrono;

namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)

	EventPublisher::EventPublisher(Vector<EventSubscriber*>* subscriberList):
		mTimeEnqueued(), mMillisecondDelay(0), mDeleteAfterPublishing(false), mSubscriberList(subscriberList)
	{
	}

	EventPublisher::EventPublisher(const EventPublisher& rhs):
		mTimeEnqueued(rhs.mTimeEnqueued), mMillisecondDelay(rhs.mMillisecondDelay), 
		mDeleteAfterPublishing(rhs.mDeleteAfterPublishing), mSubscriberList(rhs.mSubscriberList)
	{
	}

	EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
	{
		mTimeEnqueued = rhs.mTimeEnqueued;
		mMillisecondDelay = rhs.mMillisecondDelay;
		mSubscriberList = rhs.mSubscriberList;
		return *this;
	}

	EventPublisher::EventPublisher(EventPublisher&& rhs):
		mTimeEnqueued(rhs.mTimeEnqueued), mMillisecondDelay(rhs.mMillisecondDelay), 
		mDeleteAfterPublishing(rhs.mDeleteAfterPublishing), mSubscriberList(rhs.mSubscriberList)
	{
		rhs.mMillisecondDelay = milliseconds(0);
		rhs.mSubscriberList = nullptr;
	}

	EventPublisher& EventPublisher::operator=(EventPublisher&& rhs)
	{
		mTimeEnqueued = rhs.mTimeEnqueued;
		mMillisecondDelay = rhs.mMillisecondDelay;
		mSubscriberList = rhs.mSubscriberList;

		rhs.mMillisecondDelay = milliseconds(0);
		rhs.mSubscriberList = nullptr;

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

	bool EventPublisher::isExpired() const
	{
		return high_resolution_clock::now() > (mTimeEnqueued + mMillisecondDelay);
	}

	void EventPublisher::deliver()
	{
		// TODO: Implement deliver. Notify all subscribers of this event
		for (auto iter = mSubscriberList->begin(); iter != mSubscriberList->end(); ++iter)
		{
			(*iter)->notify(*this);
		}
	}

	bool EventPublisher::deleteAfterPublishing() const
	{
		return mDeleteAfterPublishing;
	}
}

