
#include "KeyboardComponent.hpp"
#include "Engine.hpp"
#include "Component.hpp"
#include "EngineTime.hpp"

using namespace std;
using namespace DirectX;

namespace Library
{
	RTTI_DEFINITIONS(KeyboardComponent);

	std::unique_ptr<DirectX::Keyboard> KeyboardComponent::sKeyboard{ new DirectX::Keyboard };

	Keyboard* KeyboardComponent::Keyboard()
	{
		return sKeyboard.get();
	}

	KeyboardComponent::KeyboardComponent(Engine& l_engine) :
		Component(l_engine)
	{
	}

	const Keyboard::State& KeyboardComponent::CurrentState() const
	{
		return m_currentState;
	}

	const Keyboard::State& KeyboardComponent::LastState() const
	{
		return m_lastState;
	}

	void KeyboardComponent::Initialize()
	{
		m_currentState = sKeyboard->GetState();
		m_lastState = m_currentState;
	}

	void KeyboardComponent::Update(const EngineTime&)
	{
		m_lastState = m_currentState;
		m_currentState = sKeyboard->GetState();
	}

	bool KeyboardComponent::IsKeyUp(Keys key) const
	{
		return m_currentState.IsKeyUp(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardComponent::IsKeyDown(Keys key) const
	{
		return m_currentState.IsKeyDown(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardComponent::WasKeyUp(Keys key) const
	{
		return m_lastState.IsKeyUp(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardComponent::WasKeyDown(Keys key) const
	{
		return m_lastState.IsKeyDown(static_cast<Keyboard::Keys>(key));
	}

	bool KeyboardComponent::WasKeyPressedThisFrame(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyUp(key));
	}

	bool KeyboardComponent::WasKeyReleasedThisFrame(Keys key) const
	{
		return (IsKeyUp(key) && WasKeyDown(key));
	}

	bool KeyboardComponent::IsKeyHeldDown(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyDown(key));
	}
}