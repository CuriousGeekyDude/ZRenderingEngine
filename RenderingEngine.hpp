#pragma once

#include "Engine.hpp"
#include <DirectXColors.h>
#include "MainPassConstantBuffer.hpp"
#include <d3d11_1.h>
#include "Model.hpp"
#include <map>
#include <fstream>
#include "EngineGlobalVariables.hpp"

namespace Library
{
	class KeyboardComponent;
	class MouseComponent;
	class Camera;
}

namespace RenderingEngine
{
	
	
	class ZRenderingEngine : public Library::Engine
	{
	public:

		ZRenderingEngine(HINSTANCE l_instance, const std::wstring& l_windowClass,
			const std::wstring& l_windowTitle, int l_showCommand);
		ZRenderingEngine(const ZRenderingEngine& l_rhs) = delete;
		ZRenderingEngine& operator=(const ZRenderingEngine& l_rhs) = delete;

		virtual void Initialize() override;
		virtual void Update(const Library::EngineTime& l_engineTime) override;
		virtual void Draw(const Library::EngineTime& l_engineTime) override;


	private:

		void UpdateMainPassConstantBuffer(const Library::EngineTime& l_engineTime);
		void UpdateKeyboard(const Library::EngineTime& l_engineTime);

		DirectX::XMVECTORF32 m_defaultBackGroundColor{DirectX::Colors::Crimson};
		Library::KeyboardComponent* m_keyboard{};
		Library::MouseComponent* m_mouse{};
		Library::Camera* m_camera{};
		ID3D11Buffer* m_mainPassCB{};

		Library::ShaderStructures::MainPassConstantBuffer m_mainPassCBData{};
		std::map<std::string, Library::Model> m_models{};
		std::ifstream m_modelNamesFile{ EngineGlobalVariables::lv_modelNamesFile };
	};
}