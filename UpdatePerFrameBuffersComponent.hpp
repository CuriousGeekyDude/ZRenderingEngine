#pragma once

#include "Component.hpp"
#include <map>
#include <string>
#include <d3d11_1.h>
#include "MainPassConstantBuffer.hpp"
#include "RTTI.hpp"


namespace Library
{
	class Camera;
	class EngineTime;
	class Engine;

	class UpdatePerFrameBuffersComponent final : public Component 
	{
		RTTI_DECLARATIONS(UpdatePerFrameBuffersComponent, Component);

	public:

		UpdatePerFrameBuffersComponent(Engine& l_engine, std::shared_ptr<Camera>& l_camera);

		void Initialize();
		void Update(const EngineTime&);


		void AddConstantBuffer(const std::string&, ID3D11Buffer*);
		void RemoveConstantBuffer(const std::string&);
		ID3D11Buffer* GetConstantBuffer(const std::string&);

	private:
		std::map<std::string, ID3D11Buffer*> m_constantBuffers{};
		std::shared_ptr<Camera> m_camera;
		ShaderStructures::MainPassConstantBuffer m_mainPassCBData{};
		ID3D11Device1* m_device{};
		ID3D11DeviceContext1* m_deviceContext{};
	};
}