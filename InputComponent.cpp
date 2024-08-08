

#include "InputComponent.hpp"
#include "Engine.hpp"
#include <DirectXMath.h>

namespace Library
{
	RTTI_DEFINITIONS(InputComponent);

	std::unique_ptr<DirectX::Mouse> InputComponent::sMouse = std::make_unique<DirectX::Mouse>();

	DirectX::Mouse* InputComponent::Mouse()
	{
		return sMouse.get();
	}

	InputComponent::InputComponent(Engine& l_engine, MouseModes mode) :
		Component(l_engine), m_inputEventHandler(l_engine.GetInputEventHandler())
	{
		sMouse->SetWindow(l_engine.WindowHandle());
		sMouse->SetMode(static_cast<DirectX::Mouse::Mode>(mode));
	}

	const DirectX::Mouse::State& InputComponent::CurrentStateMouse() const
	{
		return m_currentStateMouse;
	}

	const DirectX::Mouse::State& InputComponent::LastStateMouse() const
	{
		return m_lastStateMouse;
	}

	void InputComponent::Initialize()
	{
		m_currentStateMouse = sMouse->GetState();
		m_lastStateMouse = m_currentStateMouse;
		m_currentStateKeyboard = sKeyboard->GetState();
		m_lastStateKeyboard = m_currentStateKeyboard;
	}

	void InputComponent::Update(const EngineTime& l_engineTime)
	{
		using namespace DirectX;

		m_lastStateKeyboard = m_currentStateKeyboard;
		m_currentStateKeyboard = sKeyboard->GetState();

		m_lastStateMouse = m_currentStateMouse;
		m_currentStateMouse = sMouse->GetState();


		float dx = XMConvertToRadians(0.25f * static_cast<float>(m_currentStateMouse.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(m_currentStateMouse.y));


		const float dt = l_engineTime.ElapsedEngineTimeSeconds().count();
		const float lv_multiplier{ 10.f };


		if (0 != dx || 0 != dy) {
			m_inputEventHandler.ReceiveInput(dx, dy, dt, lv_multiplier, "");
		}

		if (true == IsKeyDown(Keys::W) || true == IsKeyHeldDown(Keys::W)) {
			m_inputEventHandler.ReceiveInput(dx, dy, dt, lv_multiplier, "W");
		}

		if (true == IsKeyDown(Keys::D) || true == IsKeyHeldDown(Keys::D)) {
			m_inputEventHandler.ReceiveInput(dx, dy, dt, lv_multiplier, "D");

		}

		if (true == IsKeyDown(Keys::S) || true == IsKeyHeldDown(Keys::S)) {
			m_inputEventHandler.ReceiveInput(dx, dy, dt, lv_multiplier, "S");

		}

		if (true == IsKeyDown(Keys::A) || true == IsKeyHeldDown(Keys::A)) {
			m_inputEventHandler.ReceiveInput(dx, dy, dt, lv_multiplier, "A");
		}

		if (true == IsKeyDown(Keys::Escape) || true == IsKeyHeldDown(Keys::Escape)) {
			m_inputEventHandler.ReceiveInput(dx, dy, dt, lv_multiplier, "ESCAPE");
		}
	}

	void InputComponent::SetWindow(HWND window)
	{
		sMouse->SetWindow(window);
	}

	int InputComponent::X() const
	{
		return m_currentStateMouse.x;
	}

	int InputComponent::Y() const
	{
		return m_currentStateMouse.y;
	}

	int InputComponent::Wheel() const
	{
		return m_currentStateMouse.scrollWheelValue;
	}


	bool InputComponent::IsButtonUp(MouseButtons button) const
	{
		return GetButtonState(m_currentStateMouse, button) == false;
	}

	bool InputComponent::IsButtonDown(MouseButtons button) const
	{
		return GetButtonState(m_currentStateMouse, button);
	}

	bool InputComponent::WasButtonUp(MouseButtons button) const
	{
		return GetButtonState(m_lastStateMouse, button) == false;
	}

	bool InputComponent::WasButtonDown(MouseButtons button) const
	{
		return GetButtonState(m_lastStateMouse, button);
	}

	bool InputComponent::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonUp(button));
	}

	bool InputComponent::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return (IsButtonUp(button) && WasButtonDown(button));
	}

	bool InputComponent::IsButtonHeldDown(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonDown(button));
	}

	MouseModes InputComponent::Mode() const
	{
		auto state = sMouse->GetState();
		return static_cast<MouseModes>(state.positionMode);
	}

	void InputComponent::SetMode(MouseModes mode)
	{
		sMouse->SetMode(static_cast<DirectX::Mouse::Mode>(mode));
	}

	bool InputComponent::GetButtonState(const DirectX::Mouse::State& state, MouseButtons button) const
	{
		switch (button)
		{
		case Library::MouseButtons::Left:
			return state.leftButton;

		case Library::MouseButtons::Right:
			return state.rightButton;

		case Library::MouseButtons::Middle:
			return state.middleButton;

		case Library::MouseButtons::X1:
			return state.xButton1;

		case Library::MouseButtons::X2:
			return state.xButton2;

		default:
			throw std::exception("Invalid MouseButtons.");
		}
	}


	std::unique_ptr<DirectX::Keyboard> InputComponent::sKeyboard{ new DirectX::Keyboard };

	DirectX::Keyboard* InputComponent::Keyboard()
	{
		return sKeyboard.get();
	}

	const DirectX::Keyboard::State& InputComponent::CurrentStateKeyboard() const
	{
		return m_currentStateKeyboard;
	}

	const DirectX::Keyboard::State& InputComponent::LastStateKeyboard() const
	{
		return m_lastStateKeyboard;
	}

	

	bool InputComponent::IsKeyUp(Keys key) const
	{
		return m_currentStateKeyboard.IsKeyUp(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool InputComponent::IsKeyDown(Keys key) const
	{
		return m_currentStateKeyboard.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool InputComponent::WasKeyUp(Keys key) const
	{
		return m_lastStateKeyboard.IsKeyUp(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool InputComponent::WasKeyDown(Keys key) const
	{
		return m_lastStateKeyboard.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(key));
	}

	bool InputComponent::WasKeyPressedThisFrame(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyUp(key));
	}

	bool InputComponent::WasKeyReleasedThisFrame(Keys key) const
	{
		return (IsKeyUp(key) && WasKeyDown(key));
	}

	bool InputComponent::IsKeyHeldDown(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyDown(key));
	}
}