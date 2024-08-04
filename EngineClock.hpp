#pragma once

#include <exception>
#include <chrono>

namespace Library
{
	class EngineTime;

	class EngineClock final
	{
	public:
		EngineClock();
		EngineClock(const EngineClock&) = default;
		EngineClock& operator=(const EngineClock&) = default;
		EngineClock(EngineClock&&) = default;
		EngineClock& operator=(EngineClock&&) = default;
		~EngineClock() = default;

		const std::chrono::high_resolution_clock::time_point& StartTime() const;
		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		const std::chrono::high_resolution_clock::time_point& LastTime() const;

		void Reset();
		void UpdateEngineTime(EngineTime& l_engineTime);

	private:
		std::chrono::high_resolution_clock::time_point m_startTime;
		std::chrono::high_resolution_clock::time_point m_currentTime;
		std::chrono::high_resolution_clock::time_point m_lastTime;
	};
}