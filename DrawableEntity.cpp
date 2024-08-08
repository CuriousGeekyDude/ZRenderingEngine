

#include "DrawableEntity.hpp"
#include "UpdatePerFrameBuffersComponent.hpp"
#include "Node.hpp"
#include "EngineTime.hpp"

namespace Library
{
	RTTI_DEFINITIONS(DrawableEntity);

	void DrawableEntity::Initialize()
	{
		Entity::Initialize();
		UpdatePerFrameBuffersComponent* lv_perFrameCB{};
		for (auto& l_component : m_components) {
			lv_perFrameCB = l_component->As<UpdatePerFrameBuffersComponent>();
			if (nullptr != lv_perFrameCB) {
				break;
			}
		}

		if (nullptr != lv_perFrameCB) {
			Node* lv_node{};

			for (auto& l_component : m_components) {
				lv_node = l_component->As<Node>();
				if (nullptr != lv_node) {
					lv_node->SetPerFrameConstantBuffer(lv_perFrameCB->GetConstantBuffer("MainPass"));
				}
			}
		}
	}
	
	void DrawableEntity::Draw(const EngineTime & l_engineTime)
	{
			for (auto& l_component : m_components) {
				DrawableComponent* lv_drawableComponent =
					l_component->As<DrawableComponent>();
				if (nullptr != lv_drawableComponent && true == lv_drawableComponent->IsVisible()) {
					lv_drawableComponent->Draw(l_engineTime);
				}
			}
	}
	
}