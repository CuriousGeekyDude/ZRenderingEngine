#pragma once


#include <memory>
#include "DrawableComponent.hpp"
#include "RTTI.hpp"
#include "directxtk/SpriteBatch.h"
#include "directxtk/SpriteFont.h"


namespace DirectX
{
	struct XMFLOAT2;
}

namespace Library
{
	class Engine;
	class EngineTime;

	class FPSComponent final: public DrawableComponent
	{
		RTTI_DECLARATIONS(FPSComponent, DrawableComponent);

	public:
		FPSComponent(Engine& l_engine) : DrawableComponent(l_engine) {}
		FPSComponent(const FPSComponent&) = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;

		const DirectX::XMFLOAT2& GetTextPos() const { return m_textPosition; }
		DirectX::XMFLOAT2& GetTextPos() { return m_textPosition; }
		int FrameRate() const { return m_frameRate; }

		void Initialize() override;
		void Update(const EngineTime& l_engineTime) override;
		void Draw(const EngineTime& l_engineTime) override;

	private:
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch{};
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont{};
		DirectX::XMFLOAT2 m_textPosition{0.f, 5.f};
		int m_frameRate{};
		int m_frameCount{};
		double m_lastTotalElapsedTime{};

	};
}