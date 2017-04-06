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
		
		// Copy semantics
		EventPublisher(const EventPublisher& rhs);
		EventPublisher& operator=(const EventPublisher& rhs);

		// Move semantics
		EventPublisher(EventPublisher&& rhs);
		EventPublisher& operator=(EventPublisher&& rhs);

		void setTime(const std::chrono::high_resolution_clock::time_point& timePoint, std::uint32_t millisecondDelay = 0);
		std::chrono::high_resolution_clock::time_point timeEnqueued() const;
		std::int32_t delay() const;
		bool isExpired() const;
		void deliver();
		bool deleteAfterPublishing() const;
	};
}


