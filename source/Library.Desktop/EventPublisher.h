#pragma once
#include "RTTI.h"
#include <chrono>


namespace Library
{
	class EventPublisher :
		public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:
		EventPublisher();
		~EventPublisher() = default;
		
		EventPublisher(const EventPublisher& rhs);
		EventPublisher& operator=(const EventPublisher& rhs);

		EventPublisher(EventPublisher&& rhs);
		EventPublisher& operator=(EventPublisher&& rhs);

		void setTime(const std::chrono::high_resolution_clock::time_point& timePoint, std::chrono::milliseconds millisecondDelay = std::chrono::milliseconds(0));
		std::chrono::high_resolution_clock::time_point timeEnqueued() const;
		std::chrono::milliseconds delay() const;
		bool isExpired() const;
		void deliver();
		bool deleteAfterPublishing() const;

	private:
		std::chrono::high_resolution_clock::time_point mTimeEnqueued;
		std::chrono::milliseconds mMillisecondDelay;
		bool mDeleteAfterPublishing;
	};
}


