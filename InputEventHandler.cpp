

#include "InputEventHandler.hpp"
#include "Component.hpp"
#include "Observer.hpp"

namespace Library
{
	void InputEventHandler::ReceiveInput(float dx, float dy, float dt, 
		float l_multiplier, const std::string& l_command)
	{
		for (auto l_observer : m_observers) {
			l_observer->Update(dx, dy);
			l_observer->Update(dt,l_multiplier, l_command);
		}
	}


	void InputEventHandler::AddObservers(Observer* l_observer)
	{
		m_observers.push_back(l_observer);
	}

	void InputEventHandler::RemoveObservers(Observer* l_observer)
	{
		auto lv_iterToRemove = m_observers.cbegin();

		for (; lv_iterToRemove != m_observers.cend(); ++lv_iterToRemove) {
			if (*lv_iterToRemove == l_observer) {
				break;
			}
		}

		if (m_observers.cend() != lv_iterToRemove) {
			m_observers.erase(lv_iterToRemove);
		}
	}
}