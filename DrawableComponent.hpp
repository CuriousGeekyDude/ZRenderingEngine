#pragma once


#include "Component.hpp"

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
		DrawableComponent(Engine& l_engine, Camera& l_camera);
		DrawableComponent();
		DrawableComponent(const DrawableComponent&) = delete;
		DrawableComponent& operator=(const DrawableComponent&) = delete;

		virtual ~DrawableComponent();

		bool IsVisible() const;
		void SetVisible(bool l_truthValue);
		Camera* GetCamera();
		void SetCamera(Camera& l_camera);

		virtual void Draw(const EngineTime&);

	protected:
		Camera* m_camera{};
		bool m_visible{true};
	};
}