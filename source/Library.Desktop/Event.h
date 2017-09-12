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

#pragma region Construction/Copy/Assignment

		explicit Event(const Payload& payload, bool deleteAfterPublishing = false);

		~Event() = default;

		Event<Payload>& operator=(const Event<Payload>& rhs);

		Event(const Event<Payload>& rhs);

		Event<Payload>& operator=(Event<Payload>&& rhs) noexcept;

		Event(Event<Payload>&& rhs) noexcept;

#pragma endregion

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

