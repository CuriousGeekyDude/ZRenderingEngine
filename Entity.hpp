#pragma once

#include <vector>
#include <memory>
#include "RTTI.hpp"


namespace Library
{
	class Component;
	class EngineTime;

	class Entity : public RTTI
	{
		RTTI_DECLARATIONS(Entity, RTTI);

	public:

		Entity() = default;
		Entity(const Entity&) = delete;

		template<typename T>
		void AddComponent(std::shared_ptr<T>& l_component)
		{
			m_components.emplace_back(l_component);
		}


		template <typename T>
		void RemoveComponent(const T& l_componentToRemove)
		{
			std::vector<std::shared_ptr<Component>>::const_iterator lv_iterComponent = m_components.cbegin();

			for (; lv_iterComponent != m_components.cend(); ++lv_iterComponent) {
				if (&l_componentToRemove == (*lv_iterComponent->get())) {
					break;
				}
			}

			if (m_components.cend() != lv_iterComponent) {
				m_components.erase(lv_iterComponent);
			}
		}

		virtual void Initialize();
		virtual void Update(const EngineTime& l_engineTime);


		const std::vector<std::shared_ptr<Component>>& GetComponents() const { return m_components; };

	protected:
		std::vector<std::shared_ptr<Component>> m_components{};
	};
}