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

		/// Constructor
		/// @Param subscriberList: The static list of subscribers for a given type
		explicit EventPublisher(Vector<class EventSubscriber*>* subscriberList);

		/// Default destructor
		~EventPublisher() = default;
		
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

		/// Sets the time point and delay of the event publisher
		/// @Param timePoint: The current time point of the event publisher
		/// @Param millisecondDelay: The delay before the event gets delivered
		void setTime(const std::chrono::high_resolution_clock::time_point& timePoint, std::chrono::milliseconds millisecondDelay = std::chrono::milliseconds(0));

		/// Accessor method for the time that the event was queued
		/// @Return: The time point when this event was queued
		std::chrono::high_resolution_clock::time_point timeEnqueued() const;

		/// Accessor method for the millisecond delay of this event
		/// @Return: The number of milliseconds this event is delayed for
		std::chrono::milliseconds delay() const;

		/// Determines if the method is ready to be delivered
		/// @Param timePoint: The current time point of the game
		/// @Return: True if the method is ready to be delivered
		bool isExpired(const std::chrono::high_resolution_clock::time_point& timePoint) const;

		/// Delivers the event to any subscribers listening for it
		void deliver();

		/// Accessor method for whether this event is deleted after it is published
		/// @Return: True if this event is deleted after publishing
		bool deleteAfterPublishing() const;

	private:
		std::chrono::high_resolution_clock::time_point mTimeEnqueued; /// The time point when this event was queued
		std::chrono::milliseconds mMillisecondDelay; /// The amount of delay assigned for this event
		bool mDeleteAfterPublishing; /// Boolean to determine if this event is deleted after being published
		Vector<class EventSubscriber*>* mSubscriberList; /// The list of subscribers to notify of This event type
	};
}


