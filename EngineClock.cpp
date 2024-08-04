

#include "EngineClock.hpp"
#include "EngineTime.hpp"


namespace Library
{
	EngineClock::EngineClock()
	{
		Reset();
	}

	const std::chrono::high_resolution_clock::time_point& EngineClock::StartTime() const
	{
		return m_startTime;
	}

	const std::chrono::high_resolution_clock::time_point& EngineClock::CurrentTime() const
	{
		return m_currentTime;
	}

	const std::chrono::high_resolution_clock::time_point& EngineClock::LastTime() const
	{
		return m_lastTime;
	}

	void EngineClock::Reset()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
		m_currentTime = m_startTime;
		m_lastTime = m_currentTime;
	}

	void EngineClock::UpdateEngineTime(EngineTime& l_engineTime)
	{
		m_currentTime = std::chrono::high_resolution_clock::now();

		l_engineTime.SetCurrentTime(m_currentTime);
		l_engineTime.SetTotalEngineTime(std::chrono::duration_cast<std::chrono::milliseconds>(m_currentTime - m_startTime));
		l_engineTime.SetElapsedEngineTime(std::chrono::duration_cast<std::chrono::milliseconds>(m_currentTime - m_lastTime));
		m_lastTime = m_currentTime;
	}
}
