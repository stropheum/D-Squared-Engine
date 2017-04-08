#pragma once
#include "EventPublisher.h"


namespace Library
{
	class EventSubscriber
	{
	public:
		EventSubscriber();
		~EventSubscriber() = default;
		void notify(const EventPublisher& event);
	};
}


