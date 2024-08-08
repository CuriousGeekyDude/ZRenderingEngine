

#include "Entity.hpp"
#include "EngineTime.hpp"
#include "DrawableComponent.hpp"

namespace Library
{
	RTTI_DEFINITIONS(Entity);

	void Entity::Initialize()
	{
		for (auto& l_component : m_components) {
			l_component->Initialize();
		}
	}

	void Entity::Update(const EngineTime& l_engineTime)
	{
		for (auto& l_component : m_components) {
			if (true == l_component->IsEnabled()) {
				l_component->Update(l_engineTime);
			}
		}
	}

	
}