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
		UNREFERENCED_PARAMETER(gameTime);
		
		std::uint32_t expiredEventCount = 0;
		bool elementHasBeenMoved = true;
		while (elementHasBeenMoved)
		{
			elementHasBeenMoved = false;

			for (std::uint32_t i = 0; i < mQueue.size() - expiredEventCount; i++)
			{
				if (mQueue[i]->isExpired())
				{
					EventPublisher* expiredEvent = mQueue[i];
					mQueue.remove(expiredEvent);
					mQueue.pushBack(expiredEvent);
					elementHasBeenMoved = true;
					expiredEventCount++;
				}
			}

			for (std::uint32_t i = 0; i < expiredEventCount; i++)
			{
				mQueue.popBack();
			}
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

}
