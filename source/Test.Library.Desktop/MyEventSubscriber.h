#pragma once
#include "EventSubscriber.h"


namespace Library
{
	class MyEventSubscriber :
		public EventSubscriber
	{
	public:
		MyEventSubscriber();
		~MyEventSubscriber();
		virtual void notify(const EventPublisher& event) override;
		std::int32_t mValue;
	};
}

