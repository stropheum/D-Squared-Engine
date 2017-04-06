#pragma once
#include "Event.h"


namespace Library
{
	template <typename Payload>
	RTTI_DEFINITIONS(Event<Payload>)

	template <typename Payload>
	Event<Payload>::Event()
	{
	}

	template <typename Payload>
	Event<Payload>::Event(const Event<Payload>& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement copy constructor
	}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(const Event<Payload>& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement assignment operator
		return *this;
	}

	template <typename Payload>
	Event<Payload>::Event(Event<Payload>&& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement move coopy constructor
	}

	template <typename Payload>
	Event<Payload>& Event<Payload>::operator=(Event<Payload>&& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		//TODO: Implement move assignment operator
		return *this;
	}

	template <typename Payload>
	void Event<Payload>::subscribe(EventSubscriber& eventSubscriber)
	{
		UNREFERENCED_PARAMETER(eventSubscriber);
		//TODO: Implement subscribe method
	}

	template <typename Payload>
	void Event<Payload>::unsubscribeAll()
	{
		//TDOO: Implement unsubscribeAll
	}

	template <typename Payload>
	Payload& Event<Payload>::message()
	{
		//TODO: Implement message method. should return the member payload
		return Payload();
	}
}
