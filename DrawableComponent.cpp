

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
		:Component(l_engine), m_device(l_engine.Direct3DDevice()), m_deviceContext(l_engine.Direct3DDeviceContext()) {}
	DrawableComponent::DrawableComponent(Engine& l_engine, std::shared_ptr<Camera>& l_camera)
		:Component(l_engine), m_camera(l_camera), m_device(l_engine.Direct3DDevice()), m_deviceContext(l_engine.Direct3DDeviceContext()) {}

	bool DrawableComponent::IsVisible() const { return m_visible; }
	void DrawableComponent::SetVisible(bool l_truthValue) { m_visible = l_truthValue; }
	Camera* DrawableComponent::GetCamera() { return m_camera.get(); }

	DrawableComponent::~DrawableComponent() {}
}