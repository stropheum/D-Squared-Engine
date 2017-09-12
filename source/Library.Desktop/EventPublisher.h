#pragma once
#include "RTTI.h"
#include <chrono>
#include "Vector.h"
#include <mutex>


namespace Library
{
	class EventPublisher abstract :
		public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:

#pragma region Construction/Copy/Assignment

		explicit EventPublisher(Vector<class EventSubscriber*>* subscriberList, std::mutex& subscriberListMutex, bool deleteAfterPublishing = false);

		virtual ~EventPublisher() = default;
		
		EventPublisher(const EventPublisher& rhs);

		EventPublisher& operator=(const EventPublisher& rhs);

		EventPublisher(EventPublisher&& rhs) noexcept;

		EventPublisher& operator=(EventPublisher&& rhs) noexcept;

#pragma endregion

		/**
		 * Sets the time point and Delay of the event publisher
		 * @Param timePoint: The current time point of the event publisher
		 * @Param millisecondDelay: The Delay before the event gets delivered
		 */
		void SetTime(const std::chrono::high_resolution_clock::time_point& timePoint, const std::chrono::milliseconds& millisecondDelay = std::chrono::milliseconds(0));

		/**
		 * Accessor method for the time that the event was queued
		 * @Return: The time point when this event was queued
		 */
		std::chrono::high_resolution_clock::time_point TimeEnqueued() const;

		/**
		 * Accessor method for the millisecond Delay of this event
		 * @Return: The number of milliseconds this event is delayed for
		 */
		std::chrono::milliseconds Delay() const;

		/**
		 * Determines if the method is ready to be delivered
		 * @Param timePoint: The current time point of the game
		 * @Return: True if the method is ready to be delivered
		 */
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& timePoint) const;

		/**
		 * Delivers the event to any subscribers listening for it
		 */
		void Deliver() const;

		/**
		 * Accessor method for whether this event is deleted after it is published
		 * @Return: True if this event is deleted after publishing
		 */
		bool DeleteAfterPublishing() const;

	protected:

		bool mDeleteAfterPublishing; // Boolean to determine if this event is deleted after being published

	private:

		std::chrono::high_resolution_clock::time_point mTimeEnqueued;	// The time point when this event was queued
		std::chrono::milliseconds mMillisecondDelay;	// The amount of Delay assigned for this event
		Vector<class EventSubscriber*>* mSubscriberList;	// The list of subscribers to Notify of This event Type
		std::mutex* mSubscriberListMutex;	// Mutex to prevent concurrent access to the subscriber list on Deliver
	};
}


