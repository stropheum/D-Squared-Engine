#include "pch.h"
#include "EventQueue.h"


namespace Library
{
	EventQueue::EventQueue()
	{
	}

	void EventQueue::enqueue(EventPublisher& eventPublisher, GameTime& gameTime, std::uint32_t delay)
	{
		UNREFERENCED_PARAMETER(eventPublisher);
		UNREFERENCED_PARAMETER(gameTime);
		UNREFERENCED_PARAMETER(delay);
		//TODO: Implement enqueue
	}

	void EventQueue::send(EventPublisher& eventPublisher)
	{
		UNREFERENCED_PARAMETER(eventPublisher);
		//TODO: Implement send
	}

	void EventQueue::update(GameTime& gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);
		//TODO: Implement update
	}

	void EventQueue::clear()
	{
		//TODO: Implement clear
	}

	bool EventQueue::isEmpty() const
	{
		//TODO: Implement isEmpty
		return false;
	}

	std::uint32_t EventQueue::size() const
	{
		//TODO: Implement size
		return 0;
	}
}
