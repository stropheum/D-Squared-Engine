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

		/// Constructor
		/// @Param subscriberList: The static list of subscribers for a given Type
		/// @Param DeleteAfterPublishing: Bool to determine if the event queue should delete this when delivered
		explicit EventPublisher(Vector<class EventSubscriber*>* subscriberList, std::mutex& subscriberListMutex, bool deleteAfterPublishing = false);

		/// Default destructor
		virtual ~EventPublisher() = default;
		
		/// Copy constructor
		/// @Param rhs: The event publisher being copied
		EventPublisher(const EventPublisher& rhs);

		/// Assignment operator
		/// @Param rhs: The event publisher being assigned to
		/// @Return: A reference to the newly copied event publisher
		EventPublisher& operator=(const EventPublisher& rhs);

		/// Move copy constructor
		/// @Param rhs: The event publisher being copied
		EventPublisher(EventPublisher&& rhs);

		/// Move assignment operator
		/// @Param rhs: The event publisher being copied
		/// @Return: A reference to the newly copied event publisher
		EventPublisher& operator=(EventPublisher&& rhs);

		/// Sets the time point and Delay of the event publisher
		/// @Param timePoint: The current time point of the event publisher
		/// @Param millisecondDelay: The Delay before the event gets delivered
		void SetTime(const std::chrono::high_resolution_clock::time_point& timePoint, std::chrono::milliseconds millisecondDelay = std::chrono::milliseconds(0));

		/// Accessor method for the time that the event was queued
		/// @Return: The time point when this event was queued
		std::chrono::high_resolution_clock::time_point TimeEnqueued() const;

		/// Accessor method for the millisecond Delay of this event
		/// @Return: The number of milliseconds this event is delayed for
		std::chrono::milliseconds Delay() const;

		/// Determines if the method is ready to be delivered
		/// @Param timePoint: The current time point of the game
		/// @Return: True if the method is ready to be delivered
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& timePoint) const;

		/// Delivers the event to any subscribers listening for it
		void Deliver();

		/// Accessor method for whether this event is deleted after it is published
		/// @Return: True if this event is deleted after publishing
		bool DeleteAfterPublishing() const;

	protected:
		bool mDeleteAfterPublishing; /// Boolean to determine if this event is deleted after being published

	private:
		std::chrono::high_resolution_clock::time_point mTimeEnqueued; /// The time point when this event was queued
		std::chrono::milliseconds mMillisecondDelay; /// The amount of Delay assigned for this event
		Vector<class EventSubscriber*>* mSubscriberList; /// The list of subscribers to Notify of This event Type
		std::mutex* mSubscriberListMutex;	/// Mutex to prevent concurrent access to the subscriber list on Deliver
	};
}


