#include "pch.h"
#include "EventPublisher.h"


using namespace std::chrono;

namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)

	EventPublisher::EventPublisher()
	{
	}

	EventPublisher::EventPublisher(const EventPublisher& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement copy constructor
	}

	EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement assignment operator
		return *this;
	}

	EventPublisher::EventPublisher(EventPublisher&& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement move copy constructor
	}

	EventPublisher& EventPublisher::operator=(EventPublisher&& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement move assignment operator)
		return *this;
	}

	void EventPublisher::setTime(const std::chrono::high_resolution_clock::time_point& timePoint, std::uint32_t millisecondDelay)
	{
		UNREFERENCED_PARAMETER(timePoint);
		UNREFERENCED_PARAMETER(millisecondDelay);
		//TODO: Implement setTime method
	}

	high_resolution_clock::time_point EventPublisher::timeEnqueued() const
	{
		//TODO: Implement timeEnqueued method
		return high_resolution_clock::time_point();
	}

	std::int32_t EventPublisher::delay() const
	{
		//TODO: Implement delay method. return the amount of time after being enqueued that this event expires
		return 0;
	}

	bool EventPublisher::isExpired() const
	{
		//TODO: Implement isExpired
		return false;
	}

	void EventPublisher::deliver()
	{
		// TODO: Implement deliver. Notify all subscribers of this event
	}

	bool EventPublisher::deleteAfterPublishing() const
	{
		//TODO: Implement deleteAfterPublishing. Return whether this event should be deleted after it is published
		return false;
	}
}

