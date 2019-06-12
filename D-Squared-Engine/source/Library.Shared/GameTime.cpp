#include "pch.h"
#include "GameTime.h"

using namespace std::chrono;

namespace Library
{
    GameTime::GameTime()
        : m_currentTime(), m_totalGameTime(0), m_elapsedGameTime(0)
    {}

    const high_resolution_clock::time_point& GameTime::CurrentTime() const
    {
        return m_currentTime;
    }

    void GameTime::SetCurrentTime(const high_resolution_clock::time_point& currentTime)
    {
        m_currentTime = currentTime;
    }

    const milliseconds& GameTime::TotalGameTime() const
    {
        return m_totalGameTime;
    }

    void GameTime::SetTotalGameTime(const std::chrono::milliseconds& totalGameTime)
    {
        m_totalGameTime = totalGameTime;
    }

    const milliseconds& GameTime::ElapsedGameTime() const
    {
        return m_elapsedGameTime;
    }

    void GameTime::SetElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime)
    {
        m_elapsedGameTime = elapsedGameTime;
    }
}