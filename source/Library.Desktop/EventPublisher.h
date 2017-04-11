#pragma once
#include "RTTI.h"
#include <chrono>
#include "Vector.h"


namespace Library
{
	class EventPublisher abstract :
		public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:
		explicit EventPublisher(Vector<class EventSubscriber*>* subscriberList);
		~EventPublisher() = default;
		
		EventPublisher(const EventPublisher& rhs);
		EventPublisher& operator=(const EventPublisher& rhs);

		EventPublisher(EventPublisher&& rhs);
		EventPublisher& operator=(EventPublisher&& rhs);

		void setTime(const std::chrono::high_resolution_clock::time_point& timePoint, std::chrono::milliseconds millisecondDelay = std::chrono::milliseconds(0));
		std::chrono::high_resolution_clock::time_point timeEnqueued() const;
		std::chrono::milliseconds delay() const;
		bool isExpired(const std::chrono::high_resolution_clock::time_point& timePoint) const;
		void deliver();
		bool deleteAfterPublishing() const;

	private:
		std::chrono::high_resolution_clock::time_point mTimeEnqueued;
		std::chrono::milliseconds mMillisecondDelay;
		bool mDeleteAfterPublishing;
		Vector<class EventSubscriber*>* mSubscriberList;
	};
}


