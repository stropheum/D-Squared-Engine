#include "pch.h"
#include "GameClock.h"
#include "GameTime.h"

using namespace std::chrono;

namespace Library
{
    GameClock::GameClock() :
        m_startTime(), m_currentTime(), m_lastTime()
    {
        Reset();
    }

    const high_resolution_clock::time_point& GameClock::StartTime() const
    {
        return m_startTime;
    }

    const high_resolution_clock::time_point& GameClock::CurrentTime() const
    {
        return m_currentTime;
    }

    const high_resolution_clock::time_point& GameClock::LastTime() const
    {
        return m_lastTime;
    }

    void GameClock::Reset()
    {
        m_startTime = high_resolution_clock::now();
        m_currentTime = m_startTime;
        m_lastTime = m_currentTime;
    }

    void GameClock::UpdateGameTime(GameTime& gameTime)
    {
        m_currentTime = high_resolution_clock::now();

        gameTime.SetCurrentTime(m_currentTime);
        gameTime.SetTotalGameTime(duration_cast<milliseconds>(m_currentTime - m_startTime));
        gameTime.SetElapsedGameTime(duration_cast<milliseconds>(m_currentTime - m_lastTime));
        m_lastTime = m_currentTime;
    }
}