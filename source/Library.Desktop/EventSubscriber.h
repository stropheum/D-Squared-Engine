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
		virtual void notify(const EventPublisher& event) = 0;

		std::mutex mNotifyMutex;
	};
}


