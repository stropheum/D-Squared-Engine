#include "pch.h"
#include "EventQueue.h"


using namespace std;
using namespace chrono;

namespace Library
{
    EventQueue::~EventQueue()
    {
        if (!mQueue.IsEmpty())
        {
            for (uint32_t i = 0; i < mQueue.Size(); i++)
            {
                if (mQueue[i]->DeleteAfterPublishing())
                {
                    delete mQueue[i];
                }
            }
            mQueue.Clear();
        }
    }

    void EventQueue::Enqueue(EventPublisher& eventPublisher,
        GameTime& gameTime, const chrono::milliseconds& delay)
    {
        lock_guard<mutex> guard(mQueueMutex);
        if (mQueue.Find(&eventPublisher) == mQueue.end())
        {
            eventPublisher.SetTime(gameTime.CurrentTime(), delay);
            mQueue.PushBack(&eventPublisher);
        }
    }

    void EventQueue::Send(EventPublisher& eventPublisher)
    {
        lock_guard<mutex> guard(mQueueMutex);
        eventPublisher.Deliver();
    }

    void EventQueue::Update(GameTime& gameTime)
    {
        Vector<EventPublisher*> nonExpiredEvents;
        vector<future<void>> futures;
        Vector<EventPublisher*> queueCopy(mQueue);

        {
            lock_guard<mutex> guard(mQueueMutex);

            for (uint32_t i = 0; i < queueCopy.Size(); i++)
            {
                if (queueCopy[i]->IsExpired(gameTime.CurrentTime()))
                {
                    futures.emplace_back(async(launch::async, [&queueCopy, i]
                    {
                        queueCopy[i]->Deliver();
                    }));
                }
                else
                {
                    nonExpiredEvents.PushBack(mQueue[i]);
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

    void EventQueue::Clear()
    {
        lock_guard<mutex> guard(mQueueMutex);
        mQueue.Clear();
    }

    bool EventQueue::IsEmpty() const
    {
        return mQueue.Size() == 0;
    }

    uint32_t EventQueue::Size() const
    {
        return mQueue.Size();
    }

}