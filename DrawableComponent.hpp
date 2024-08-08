#pragma once


#include "Component.hpp"
#include <d3d11_1.h>

namespace Library
{
	class Camera;
	class Engine;
	class EngineTime;

	class DrawableComponent : public Component
	{
		RTTI_DECLARATIONS(DrawableComponent, Component);

	public:

		DrawableComponent(Engine& l_engine);
		DrawableComponent(Engine& l_engine, std::shared_ptr<Camera>& l_camera);
		DrawableComponent(const DrawableComponent&) = delete;
		DrawableComponent& operator=(const DrawableComponent&) = delete;

		virtual ~DrawableComponent();

		bool IsVisible() const;
		void SetVisible(bool l_truthValue);
		Camera* GetCamera();

		virtual void Draw(const EngineTime&);

	protected:
		std::shared_ptr<Camera> m_camera{};
		ID3D11Device1* m_device{};
		ID3D11DeviceContext1* m_deviceContext{};
		bool m_visible{true};
	};
}