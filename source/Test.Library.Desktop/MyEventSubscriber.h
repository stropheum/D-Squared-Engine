#pragma once
#include "EventSubscriber.h"
#include "Foo.h"


namespace Library
{
	class MyEventSubscriber :
		public EventSubscriber
	{
	public:
		
		/// Constructor. Automatically subscribes to Events of type "Foo"
		MyEventSubscriber();

		/// Destructor. Automatically unsubscribes from Events of type "Foo"
		~MyEventSubscriber();

		/// Notify method. Called when an event of type "Foo" is triggered
		/// @Param event: The event that this object is being notified of
		virtual void notify(const EventPublisher& event) override;

		Foo mValue; /// Used to store a copy of the payload of the event for debuggin purposes
	};
}

