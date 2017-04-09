#pragma once
#include "EventPublisher.h"


namespace Library
{
	class EventSubscriber
	{
	public:
		EventSubscriber() = default;
		virtual ~EventSubscriber() = default;
		virtual void notify(const EventPublisher& event) = 0;
	};
}


