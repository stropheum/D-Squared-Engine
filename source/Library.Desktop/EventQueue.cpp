#include "pch.h"
#include "EventQueue.h"
#include "EventPublisher.h"
#include <algorithm>
#include "GameTime.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include <future>


using namespace std;
using namespace std::chrono;

namespace Library
{
	EventQueue::~EventQueue()
	{
		if (!mQueue.isEmpty())
		{
			for (uint32_t i = 0; i < mQueue.size(); i++)
			{
				if (mQueue[i]->deleteAfterPublishing())
				{
					delete mQueue[i];
				}
			}
			mQueue.clear();
		}
	}

	void EventQueue::enqueue(EventPublisher& eventPublisher, GameTime& gameTime, std::chrono::milliseconds delay)
	{
		if (mQueue.find(&eventPublisher) == mQueue.end())
		{
			eventPublisher.setTime(gameTime.CurrentTime(), delay);
			mQueue.pushBack(&eventPublisher);
		}
	}

	void EventQueue::send(EventPublisher& eventPublisher)
	{
		eventPublisher.deliver();
		if (eventPublisher.deleteAfterPublishing())
		{
			delete &eventPublisher;
		}
	}

	void EventQueue::update(GameTime& gameTime)
	{
		Vector<EventPublisher*> nonExpiredEvents;

		{
			lock_guard<mutex> guard(mQueueMutex);
			vector<future<void>> futures;

			auto queueCopy = mQueue;

			for (uint32_t i = 0; i < queueCopy.size(); i++)
			{
				if (queueCopy[i]->isExpired(gameTime.CurrentTime()))
				{
					queueCopy[i]->deliver();
					if (queueCopy[i]->deleteAfterPublishing())
					{
						delete queueCopy[i];
					}
				}
				else
				{
					nonExpiredEvents.pushBack(mQueue[i]);
				}
			}
		}

		mQueue = nonExpiredEvents;
	}

	void EventQueue::clear()
	{
		mQueue.clear();
	}

	bool EventQueue::isEmpty() const
	{
		return mQueue.size() == 0;
	}

	uint32_t EventQueue::size() const
	{
		return mQueue.size();
	}

}
