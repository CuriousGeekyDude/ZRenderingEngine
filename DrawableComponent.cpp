

#include "DrawableComponent.hpp"
#include "RTTI.hpp"
#include "Engine.hpp"


namespace Library
{
	RTTI_DEFINITIONS(DrawableComponent);

	void DrawableComponent::Draw(const EngineTime& l_engineTime)
	{

	}

	DrawableComponent::DrawableComponent(Engine& l_engine)
		:Component(l_engine) {}
	DrawableComponent::DrawableComponent(Engine& l_engine, Camera& l_camera)
		:Component(l_engine), m_camera(&l_camera) {}
	DrawableComponent::DrawableComponent() = default;

	bool DrawableComponent::IsVisible() const { return m_visible; }
	void DrawableComponent::SetVisible(bool l_truthValue) { m_visible = l_truthValue; }
	Camera* DrawableComponent::GetCamera() { return m_camera; }
	void DrawableComponent::SetCamera(Camera& l_camera) { m_camera = &l_camera; }

	DrawableComponent::~DrawableComponent() {}
}