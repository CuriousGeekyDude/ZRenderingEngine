#pragma once

#include "Component.hpp"
#include "Observer.hpp"
#include <memory>

namespace DirectX
{
	class Keyboard;
	class Mouse;
}

namespace Library
{
	class Camera;
	class Engine;

	class TransformCameraComponent final : public Component, public Observer
	{
	public:

		TransformCameraComponent(Engine& l_engine, std::shared_ptr<Camera>& l_camera)
			:Component(l_engine), m_camera(l_camera){}

		void Update(float dt, float l_multiplier, const std::string& l_key);
		void Update(float x, float y);

	private:
		std::shared_ptr<Camera> m_camera{};
	};
}