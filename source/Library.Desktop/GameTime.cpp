#include "pch.h"
#include "GameTime.h"

using namespace std::chrono;

namespace Library
{
	GameTime::GameTime()
		: mCurrentTime(), mTotalGameTime(0), mElapsedGameTime(0)
	{
	}

	const high_resolution_clock::time_point& GameTime::CurrentTime() const
	{
		return mCurrentTime;
	}

	void GameTime::SetCurrentTime(const high_resolution_clock::time_point& currentTime)
	{
		mCurrentTime = currentTime;
	}

	const milliseconds& GameTime::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void GameTime::SetTotalGameTime(const std::chrono::milliseconds& totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	const milliseconds& GameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}
}