

#include "Engine.hpp"
#include "EngineTime.hpp"
#include "MouseComponent.hpp"
#include "KeyboardComponent.hpp"
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

	MouseComponent::MouseComponent(Engine& l_engine, Camera* l_camera, KeyboardComponent* l_keyboard ,MouseModes mode) :
		Component(l_engine), m_camera(l_camera), m_keyboard(l_keyboard)
	{
		sMouse->SetWindow(l_engine.WindowHandle());
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
		m_camera = (Camera*)m_serviceProvider.GetService(Camera::TypeIdClass());
	}

	void MouseComponent::Update(const EngineTime& l_engineTime)
	{
		using namespace Library;
		using namespace DirectX;

		m_lastState = m_currentState;
		m_currentState = sMouse->GetState();

		float dx = XMConvertToRadians(0.25f * static_cast<float>(m_currentState.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(m_currentState.y));

		m_camera->Pitch(dy);
		m_camera->RotateY(dx);

		const float dt = l_engineTime.ElapsedEngineTimeSeconds().count();
		const float lv_multiplier{ 10.f };

		if (true == m_keyboard->IsKeyDown(Keys::W) || true == m_keyboard->IsKeyHeldDown(Keys::W)) {
			m_camera->Walk(lv_multiplier * dt);

		}

		if (true == m_keyboard->IsKeyDown(Keys::D) || true == m_keyboard->IsKeyHeldDown(Keys::D)) {
			m_camera->Strafe(lv_multiplier * dt);

		}

		if (true == m_keyboard->IsKeyDown(Keys::S) || true == m_keyboard->IsKeyHeldDown(Keys::S)) {
			m_camera->Walk(-lv_multiplier * dt);

		}

		if (true == m_keyboard->IsKeyDown(Keys::A) || true == m_keyboard->IsKeyHeldDown(Keys::A)) {
			m_camera->Strafe(-lv_multiplier * dt);
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