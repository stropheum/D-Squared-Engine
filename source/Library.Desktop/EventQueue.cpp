#include "pch.h"
#include "EventQueue.h"
#include "EventPublisher.h"
#include <algorithm>


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
		eventPublisher.deliver();
	}

	void EventQueue::update(GameTime& gameTime)
	{
		std::uint32_t expiredEventCount = 0;

		for (std::uint32_t i = 0; i < mQueue.size(); i++)
		{
			if (mQueue[i]->isExpired())
			{
				mQueue[i]->deliver();
				expiredEventCount++;
			}
		}

		partitionEventQueue();

		for (std::uint32_t i = 0; i < expiredEventCount; i++)
		{	// Pop off all expired values
			mQueue.popBack();
		}
	}

	void EventQueue::clear()
	{
		mQueue.clear();
	}

	bool EventQueue::isEmpty() const
	{
		return mQueue.size() == 0;
	}

	std::uint32_t EventQueue::size() const
	{
		return mQueue.size();
	}

	void EventQueue::partitionEventQueue()
	{
		auto iter = mQueue.begin();
		std::partition(iter, mQueue.end(), [&]() { !(*iter)->isExpired(); });
	}
}
