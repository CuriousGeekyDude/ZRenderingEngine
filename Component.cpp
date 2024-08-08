

#include "Component.hpp"
#include "Engine.hpp"
#include "EngineTime.hpp"

namespace Library
{
	RTTI_DEFINITIONS(Component);

	Component::Component(Engine& l_engine) :
	 m_enabled(true) {}

	Component::Component(const Component& l_component) = default;

	Component::~Component(){}

	bool Component::IsEnabled() const { return m_enabled; }
	void Component::SetEnabled(bool l_truthValue) { m_enabled = l_truthValue; }

	void Component::Initialize() {};
	void Component::Update(const EngineTime&) {};
}
