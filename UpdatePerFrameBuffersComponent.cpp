

#include "UpdatePerFrameBuffersComponent.hpp"
#include "EngineGlobalVariables.hpp"
#include "DirectX11Helper.hpp"
#include "Camera.hpp"
#include "EngineTime.hpp"
#include "Engine.hpp"



namespace Library
{

	RTTI_DEFINITIONS(UpdatePerFrameBuffersComponent);


	UpdatePerFrameBuffersComponent::UpdatePerFrameBuffersComponent(Engine& l_engine, std::shared_ptr<Camera>& l_camera)
		:Component(l_engine), m_camera(l_camera) 
	{
		m_device = l_engine.Direct3DDevice();
		m_deviceContext = l_engine.Direct3DDeviceContext();
	}

	void UpdatePerFrameBuffersComponent::Initialize()
	{
		if (true == EngineGlobalVariables::lv_InitializePerFrameConstantBuffers) {
			ID3D11Buffer* lv_constantBuffer{};
			DirectX11Helper::CreateConstantBuffer<ShaderStructures::MainPassConstantBuffer>(m_mainPassCBData,
				&lv_constantBuffer, m_device, 6 * 16 * sizeof(float), D3D11_USAGE_DYNAMIC,
				D3D11_CPU_ACCESS_WRITE);
			m_constantBuffers.insert(std::pair<std::string, ID3D11Buffer*>("MainPass", lv_constantBuffer));
			EngineGlobalVariables::lv_InitializePerFrameConstantBuffers = false;
		}
	}

	void UpdatePerFrameBuffersComponent::Update(const EngineTime& l_engineTime)
	{
		if (true == EngineGlobalVariables::lv_UpdatePerFrameConstantBuffers) {

			using namespace DirectX;

			m_camera->UpdateViewMatrix();

			XMMATRIX view = m_camera->GetView();
			XMMATRIX proj = m_camera->GetProj();
			XMMATRIX viewProj = XMMatrixMultiply(view, proj);

			auto lv_determinantView = XMMatrixDeterminant(view);
			auto lv_determinantProj = XMMatrixDeterminant(proj);
			auto lv_determinantViewProj = XMMatrixDeterminant(viewProj);

			XMMATRIX invView = XMMatrixInverse(&lv_determinantView, view);
			XMMATRIX invProj = XMMatrixInverse(&lv_determinantProj, proj);
			XMMATRIX invViewProj = XMMatrixInverse(&lv_determinantViewProj, viewProj);
			XMStoreFloat4x4(&m_mainPassCBData.View, XMMatrixTranspose(view));
			XMStoreFloat4x4(&m_mainPassCBData.InvView, XMMatrixTranspose(invView));
			XMStoreFloat4x4(&m_mainPassCBData.Proj, XMMatrixTranspose(proj));
			XMStoreFloat4x4(&m_mainPassCBData.InvProj, XMMatrixTranspose(invProj));
			XMStoreFloat4x4(&m_mainPassCBData.ViewProj, XMMatrixTranspose(viewProj));
			XMStoreFloat4x4(&m_mainPassCBData.InvViewProj, XMMatrixTranspose(invViewProj));
			m_mainPassCBData.EyePosW = m_camera->GetPosition3f();
			m_mainPassCBData.NearZ = 1.0f;
			m_mainPassCBData.FarZ = 10000.0f;
			m_mainPassCBData.TotalTime = l_engineTime.TotalEngineTimeSeconds().count();
			m_mainPassCBData.DeltaTime = l_engineTime.ElapsedEngineTimeSeconds().count();

			HRESULT lv_hr{};
			D3D11_MAPPED_SUBRESOURCE lv_mappedSub{};
			auto* lv_mainPassConstantBuffer = (*m_constantBuffers.find("MainPass")).second;
			lv_hr = m_deviceContext->Map(lv_mainPassConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &lv_mappedSub);

			ThrowIfFailed(lv_hr, "Mapping failed for constant buffer.\n");

			Library::ShaderStructures::MainPassConstantBuffer* lv_mainPassCBData =
				(Library::ShaderStructures::MainPassConstantBuffer*)lv_mappedSub.pData;


			{
				lv_mainPassCBData->ViewProj = m_mainPassCBData.ViewProj;
				lv_mainPassCBData->View = m_mainPassCBData.View;
				lv_mainPassCBData->TotalTime = m_mainPassCBData.TotalTime;
				lv_mainPassCBData->Proj = m_mainPassCBData.Proj;
				lv_mainPassCBData->NearZ = m_mainPassCBData.NearZ;
				lv_mainPassCBData->InvViewProj = m_mainPassCBData.InvViewProj;
				lv_mainPassCBData->InvView = m_mainPassCBData.InvView;
				lv_mainPassCBData->InvProj = m_mainPassCBData.InvProj;
				lv_mainPassCBData->FarZ = m_mainPassCBData.FarZ;
				lv_mainPassCBData->EyePosW = m_mainPassCBData.EyePosW;
				lv_mainPassCBData->DeltaTime = m_mainPassCBData.DeltaTime;

			}

			m_deviceContext->Unmap(lv_mainPassConstantBuffer, 0);
			EngineGlobalVariables::lv_UpdatePerFrameConstantBuffers = false;
		}
	}

	void UpdatePerFrameBuffersComponent::AddConstantBuffer(const std::string& l_name, ID3D11Buffer* l_cb)
	{
		m_constantBuffers.insert(std::pair<std::string, ID3D11Buffer*>(l_name, l_cb));
	}

	void UpdatePerFrameBuffersComponent::RemoveConstantBuffer(const std::string& l_cbName)
	{
		m_constantBuffers.erase(l_cbName);
	}

	ID3D11Buffer* UpdatePerFrameBuffersComponent::GetConstantBuffer(const std::string& l_cbName)
	{
		std::map<std::string, ID3D11Buffer*>::const_iterator lv_service =
			m_constantBuffers.find(l_cbName);

		return lv_service != m_constantBuffers.end() ? lv_service->second : nullptr;
	}
}