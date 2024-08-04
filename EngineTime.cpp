

#include "EngineTime.hpp"


namespace Library
{
	const std::chrono::high_resolution_clock::time_point& EngineTime::CurrentTime() const
	{
		return m_currentTime;
	}

	void EngineTime::SetCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime)
	{
		m_currentTime = currentTime;
	}

	const std::chrono::milliseconds& EngineTime::TotalEngineTime() const
	{
		return m_totalEngineTime;
	}

	void EngineTime::SetTotalEngineTime(const std::chrono::milliseconds& totalGameTime)
	{
		m_totalEngineTime = totalGameTime;
	}

	const std::chrono::milliseconds& EngineTime::ElapsedEngineTime() const
	{
		return m_elapsedEngineTime;
	}

	void EngineTime::SetElapsedEngineTime(const std::chrono::milliseconds& elapsedGameTime)
	{
		m_elapsedEngineTime = elapsedGameTime;
	}

	std::chrono::duration<float> EngineTime::TotalEngineTimeSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::duration<float>>(m_totalEngineTime);
	}

	std::chrono::duration<float> EngineTime::ElapsedEngineTimeSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::duration<float>>(m_elapsedEngineTime);
	}
}