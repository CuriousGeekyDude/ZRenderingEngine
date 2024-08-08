#pragma once


#include "Entity.hpp"
#include "RTTI.hpp"

namespace Library
{
	class EngineTime;
	class DrawableEntity : public Entity
	{
		RTTI_DECLARATIONS(DrawableEntity, Entity);

	public:
		DrawableEntity() = default;
		DrawableEntity(const DrawableEntity&) = delete;

		void Initialize() override;
		void Draw(const EngineTime&);
		
	};
}