

#include "Component.hpp"
#include "Engine.hpp"
#include "EngineTime.hpp"

namespace Library
{
	RTTI_DEFINITIONS(Component);

	Component::Component(Engine& l_engine) :
		m_engine(&l_engine), m_enabled(true) {}
	Component::Component() = default;

	Component::~Component(){}

	Engine* Component::GetEngine() { return m_engine; };
	bool Component::IsEnabled() const { return m_enabled; }
	void Component::SetEnabled(bool l_truthValue) { m_enabled = l_truthValue; }
	void Component::SetEngine(Engine& l_engine) { m_engine = &l_engine; }

	void Component::Initialize() {};
	void Component::Update(const EngineTime&) {};
}
