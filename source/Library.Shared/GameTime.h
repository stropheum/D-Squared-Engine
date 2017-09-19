#pragma once

#include <chrono>
#include "GameClock.h"

namespace Library
{
	class GameTime final
	{
	public:
		GameTime();

		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		void SetCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime);
		
		const std::chrono::milliseconds& TotalGameTime() const;
		void SetTotalGameTime(const std::chrono::milliseconds& totalGameTime);

		const std::chrono::milliseconds& ElapsedGameTime() const;		
		void SetElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime);

	private:
		std::chrono::high_resolution_clock::time_point mCurrentTime;
		std::chrono::milliseconds mTotalGameTime;
		std::chrono::milliseconds mElapsedGameTime;
	};
}
