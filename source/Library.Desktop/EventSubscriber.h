#pragma once
#include "EventPublisher.h"


namespace Library
{
	class EventSubscriber
	{
	public:
		/// Default constructor
		EventSubscriber() = default;

		/// Default destructor
		virtual ~EventSubscriber() = default;

		/// Notifies the subscriber that an event has been triggered
		/// @Param event: The event that the subscriber is being notified of
		virtual void Notify(const EventPublisher& event) = 0;

	protected:
		std::mutex mNotifyMutex; /// Mutex to prevent multiple accesses to the event subscriber
	};
}


