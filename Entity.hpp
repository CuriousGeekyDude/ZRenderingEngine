#pragma once

#include <vector>
#include <memory>

namespace Library
{
	class Component;

	class Entity
	{

	public:

		Entity() = default;


		template<typename T>
		void AddComponent(T& l_component)
		{
			m_components.emplace_back(std::move(l_component));
		}


		template <typename T>
		void RemoveComponent(const T& l_componentToRemove)
		{
			std::vector<std::unique_ptr<Component>>::const_iterator lv_iterComponent = m_components.cbegin();

			for (; lv_iterComponent != m_components.cend(); ++lv_iterComponent) {
				if (&l_componentToRemove == (*lv_iterComponent->get())) {
					break;
				}
			}

			if (m_components.cend() != lv_iterComponent) {
				m_components.erase(lv_iterComponent);
			}
		}


		const std::vector<std::unique_ptr<Component>>& GetComponents() const { return m_components; };

	private:
		std::vector<std::unique_ptr<Component>> m_components{};
	};
}