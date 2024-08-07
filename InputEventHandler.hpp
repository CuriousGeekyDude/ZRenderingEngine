#pragma once

#include <string>
#include <vector>
#include <memory>


namespace Library
{
	class Component;
	class Observer;

	class InputEventHandler
	{
	public:

		void ReceiveInput(float dx, float dy, float dt, float l_multiplier, const std::string& l_command);
		

		void AddObservers(Observer* l_observer);
		void RemoveObservers(Observer* l_observer);

	private:
		std::vector<Observer*> m_observers{};

	};
}