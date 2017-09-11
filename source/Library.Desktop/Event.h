#pragma once
#include "EventPublisher.h"
#include "Vector.h"


namespace Library
{
	template <typename Payload> class Event final :
		public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:

		/**
		 * Constructor
		 * @Param paylod: The payload that this event will carry to its destination
		 * @Param DeleteAfterPublishing: Value to determine if the event queue should delete this after when delivered
		 */
		Event(const Payload& payload, bool deleteAfterPublishing = false);

		/**
		 * Default destructor
		 */
		~Event() = default;

		/**
		 * Copy constructor
		 * @Param rhs: The event being copied
		 */
		Event(const Event<Payload>& rhs);

		/**
		 * Assignment operator
		 * @Param rhs: The event being assigned to
		 * @Return: A copy of the event
		 */
		Event<Payload>& operator=(const Event<Payload>& rhs);

		/**
		 * Move copy constructor
		 * @Param rhs: The event being moved to this object
		 */
		Event(Event<Payload>&& rhs) noexcept;

		/**
		 * Move assignment operator
		 * @Param rhs: The event being moved
		 * @Return: The newly moved event
		 */
		Event<Payload>& operator=(Event<Payload>&& rhs) noexcept;

		/**
		 * Adds the event subscriber to the static list of event subscribers
		 * @Param eventSubscriber: Event Subscriber being added to the list
		 */
		static void Subscribe(class EventSubscriber& eventSubscriber);

		/**
		 * Removes the event subscriber to the staitc list of event subscribers
		 * @Param eventSubscriber: Event Subscriber being removed from the list
		 */
		static void Unsubscribe(class EventSubscriber& eventSubscriber);

		/**
		 * Removes all event subscribers from the static list of event subscribers of this Type
		 */
		static void UnsubscribeAll();

		/**
		 * Accessor method for the payload that the event is carrying
		 * @Return: A constant reference to the payload of the event
		 */
		const Payload& Message();

	private:

		Payload mPayload; // The object that will be carried to the event subscribers for this Type
		static Vector<class EventSubscriber*> sSubscriberList; // The static list of event subscribers for this event Type
		static std::mutex sSubscriberListMutex;
	};
}

#include "Event.inl"

