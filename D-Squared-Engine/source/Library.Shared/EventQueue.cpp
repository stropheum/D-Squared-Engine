#include "pch.h"
#include "EventQueue.h"


using namespace std;
using namespace chrono;

namespace Library
{
    EventQueue::~EventQueue()
    {
        if (!m_queue.IsEmpty())
        {
            for (uint32_t i = 0; i < m_queue.Size(); i++)
            {
                if (m_queue[i]->DeleteAfterPublishing())
                {
                    delete m_queue[i];
                }
            }
            m_queue.Clear();
        }
    }

    void EventQueue::Enqueue(EventPublisher& eventPublisher,
        GameTime& gameTime, const chrono::milliseconds& delay)
    {
        lock_guard<mutex> guard(m_queueMutex);
        if (m_queue.Find(&eventPublisher) == m_queue.end())
        {
            eventPublisher.SetTime(gameTime.CurrentTime(), delay);
            m_queue.PushBack(&eventPublisher);
        }
    }

    void EventQueue::Send(EventPublisher& eventPublisher)
    {
        lock_guard<mutex> guard(m_queueMutex);
        eventPublisher.Deliver();
    }

    void EventQueue::Update(GameTime& gameTime)
    {
        Vector<EventPublisher*> nonExpiredEvents;
        vector<future<void>> futures;
        Vector<EventPublisher*> queueCopy(m_queue);

        {
            lock_guard<mutex> guard(m_queueMutex);

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
                    nonExpiredEvents.PushBack(m_queue[i]);
                }
            }
        }

        for (auto& future : futures)
        {
            future.get();
        }

        {
            lock_guard<mutex> assignmentGuard(m_queueMutex);
            m_queue = nonExpiredEvents;
        }

    }

    void EventQueue::Clear()
    {
        lock_guard<mutex> guard(m_queueMutex);
        m_queue.Clear();
    }

    bool EventQueue::IsEmpty() const
    {
        return m_queue.Size() == 0;
    }

    uint32_t EventQueue::Size() const
    {
        return m_queue.Size();
    }

}