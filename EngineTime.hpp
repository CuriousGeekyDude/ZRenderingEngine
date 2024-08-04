#pragma once

#include <chrono>

namespace Library
{
	class EngineTime final
	{
	public:
		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		void SetCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime);

		const std::chrono::milliseconds& TotalEngineTime() const;
		void SetTotalEngineTime(const std::chrono::milliseconds& totalGameTime);

		const std::chrono::milliseconds& ElapsedEngineTime() const;
		void SetElapsedEngineTime(const std::chrono::milliseconds& elapsedGameTime);

		std::chrono::duration<float> TotalEngineTimeSeconds() const;
		std::chrono::duration<float> ElapsedEngineTimeSeconds() const;

	private:
		std::chrono::high_resolution_clock::time_point m_currentTime{};
		std::chrono::milliseconds m_totalEngineTime{};
		std::chrono::milliseconds m_elapsedEngineTime{};
	};
}