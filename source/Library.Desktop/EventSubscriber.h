#pragma once


namespace Library
{
	class EventSubscriber
	{
	public:
		EventSubscriber();
		~EventSubscriber() = default;
		void notify(class Event* event);
	};
}


