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
		lock_guard<mutex> guard(mQueueMutex);
		if (mQueue.find(&eventPublisher) == mQueue.end())
		{
			eventPublisher.setTime(gameTime.CurrentTime(), delay);
			mQueue.pushBack(&eventPublisher);
		}
	}

	void EventQueue::send(EventPublisher& eventPublisher)
	{
		lock_guard<mutex> guard(mQueueMutex);
		eventPublisher.deliver();
	}

	void EventQueue::update(GameTime& gameTime)
	{
		Vector<EventPublisher*> nonExpiredEvents;
		vector<future<void>> futures;
		Vector<EventPublisher*> queueCopy(mQueue);

		{
			lock_guard<mutex> guard(mQueueMutex);	

			for (uint32_t i = 0; i < queueCopy.size(); i++)
			{
				if (queueCopy[i]->isExpired(gameTime.CurrentTime()))
				{
					futures.emplace_back(async(std::launch::async, [&queueCopy, i]
					{
						queueCopy[i]->deliver();
					}));
				}
				else
				{
					nonExpiredEvents.pushBack(mQueue[i]);
				}
			}
		}

		for (auto& future : futures)
		{
			future.get();
		}

		{
			lock_guard<mutex> assignmentGuard(mQueueMutex);
			mQueue = nonExpiredEvents;
		}
		
	}

	void EventQueue::clear()
	{
		lock_guard<mutex> guard(mQueueMutex);
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
