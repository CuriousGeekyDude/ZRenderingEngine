

#include "FPSComponent.hpp"
#include "EngineGlobalVariables.hpp"
#include <DirectXMath.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Engine.hpp"
#include "EngineTime.hpp"
#include "MouseComponent.hpp"


namespace Library
{
	RTTI_DEFINITIONS(FPSComponent);

	void FPSComponent::Initialize()
	{

		std::wstring lv_spritFontFile{ EngineGlobalVariables::lv_spriteFontPath + L"Arial_14_Regular.spritefont"};

		m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_deviceContext);
		m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device, lv_spritFontFile.c_str());
	}

	void FPSComponent::Update(const EngineTime& l_engineTime)
	{
		if (1 <= l_engineTime.TotalEngineTimeSeconds().count() - m_lastTotalElapsedTime) {
			m_lastTotalElapsedTime = (double)l_engineTime.TotalEngineTimeSeconds().count();
			m_frameRate = m_frameCount;
			m_frameCount = 0;
		}
		m_frameCount++;
	}

	void FPSComponent::Draw(const EngineTime& l_engineTime)
	{
		using namespace Library;

		m_spriteBatch->Begin();

		std::wostringstream lv_fpsLabel{};
		
		lv_fpsLabel << std::setprecision(6) << L"Frame rate: " <<
			m_frameRate << L"\nTotal Elapsed time: " << l_engineTime.TotalEngineTimeSeconds().count();
				

		m_spriteFont->DrawString(m_spriteBatch.get(), lv_fpsLabel.str().c_str(),
			m_textPosition);

		m_spriteBatch->End();
	}
}