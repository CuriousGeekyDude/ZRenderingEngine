#pragma once

#include "Component.hpp"
#include "Observer.hpp"

namespace DirectX
{
	class Keyboard;
	class Mouse;
}

namespace Library
{
	class Camera;

	class TransformCameraComponent final : public Component, public Observer
	{
	public:

		void Update(float dt, float l_multiplier, const std::string& l_key);
		void Update(float x, float y);

	private:
		Camera* m_camera{};
	};
}