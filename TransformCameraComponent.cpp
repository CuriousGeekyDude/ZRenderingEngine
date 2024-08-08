

#include "TransformCameraComponent.hpp"
#include "Camera.hpp"

namespace Library
{
	void TransformCameraComponent::Update(float dt, float l_multiplier, const std::string& l_key)
	{

		if ("W" == l_key) {
			m_camera->Walk(dt*l_multiplier);
			return;
		}
		if ("D" == l_key) {
			m_camera->Strafe(dt*l_multiplier);
			return;
		}
		if ("S" == l_key) {
			m_camera->Walk(-dt * l_multiplier);
			return;
		}
		if ("A" == l_key) {
			m_camera->Strafe(-dt * l_multiplier);
		}

		if ("ESCAPE" == l_key) {
			PostQuitMessage(0);
		}

	}

	void TransformCameraComponent::Update(float x, float y)
	{
		m_camera->Pitch(y);
		m_camera->RotateY(x);
	}
}