

#include "Engine.hpp"
#include "EngineTime.hpp"
#include "MouseComponent.hpp"
#include "Camera.hpp"


using namespace std;
using namespace DirectX;

namespace Library
{
	RTTI_DEFINITIONS(MouseComponent);

	unique_ptr<Mouse> MouseComponent::sMouse = std::make_unique<DirectX::Mouse>();

	Mouse* MouseComponent::Mouse()
	{
		return sMouse.get();
	}

	MouseComponent::MouseComponent(Engine& game, MouseModes mode) :
		Component(game)
	{
		sMouse->SetWindow(m_engine->WindowHandle());
		sMouse->SetMode(static_cast<Mouse::Mode>(mode));
	}

	const Mouse::State& MouseComponent::CurrentState() const
	{
		return m_currentState;
	}

	const Mouse::State& MouseComponent::LastState() const
	{
		return m_lastState;
	}

	void MouseComponent::Initialize()
	{
		m_currentState = sMouse->GetState();
		m_lastState = m_currentState;
		m_fpsX = m_currentState.x;
		m_fpsY = m_currentState.y;
		m_camera = (Camera*)m_engine->GetServiceProvider().GetService(Camera::TypeIdClass());
	}

	void MouseComponent::Update(const EngineTime&)
	{
		m_lastState = m_currentState;
		m_currentState = sMouse->GetState();

		float dx = XMConvertToRadians(0.25f * static_cast<float>(m_currentState.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(m_currentState.y));

		m_camera->Pitch(dy);
		m_camera->RotateY(dx);

		int lv_tmpX = m_fpsX + m_currentState.x;
		int lv_tmpY = m_fpsY + m_currentState.y;

		if (0 <= lv_tmpX && lv_tmpX <= m_engine->ScreenWidth()-1) {
			m_fpsX += m_currentState.x;
		}
		if (0 <= lv_tmpY && lv_tmpY <= m_engine->ScreenHeight()-1) {
			m_fpsY += m_currentState.y;
		}
	}

	void MouseComponent::SetWindow(HWND window)
	{
		sMouse->SetWindow(window);
	}

	int MouseComponent::X() const
	{
		return m_currentState.x;
	}

	int MouseComponent::Y() const
	{
		return m_currentState.y;
	}

	int MouseComponent::Wheel() const
	{
		return m_currentState.scrollWheelValue;
	}

	int MouseComponent::GetPositionX() const
	{
		return m_fpsX;
	}

	int MouseComponent::GetPositionY() const
	{
		return m_fpsY;
	}


	bool MouseComponent::IsButtonUp(MouseButtons button) const
	{
		return GetButtonState(m_currentState, button) == false;
	}

	bool MouseComponent::IsButtonDown(MouseButtons button) const
	{
		return GetButtonState(m_currentState, button);
	}

	bool MouseComponent::WasButtonUp(MouseButtons button) const
	{
		return GetButtonState(m_lastState, button) == false;
	}

	bool MouseComponent::WasButtonDown(MouseButtons button) const
	{
		return GetButtonState(m_lastState, button);
	}

	bool MouseComponent::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonUp(button));
	}

	bool MouseComponent::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return (IsButtonUp(button) && WasButtonDown(button));
	}

	bool MouseComponent::IsButtonHeldDown(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonDown(button));
	}

	MouseModes MouseComponent::Mode() const
	{
		auto state = sMouse->GetState();
		return static_cast<MouseModes>(state.positionMode);
	}

	void MouseComponent::SetMode(MouseModes mode)
	{
		sMouse->SetMode(static_cast<Mouse::Mode>(mode));
	}

	bool MouseComponent::GetButtonState(const Mouse::State& state, MouseButtons button) const
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
			throw exception("Invalid MouseButtons.");
		}
	}
}