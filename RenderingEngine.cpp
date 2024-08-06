
#include "RenderingEngine.hpp"
#include "EngineException.hpp"
#include "FPSComponent.hpp"
#include "KeyboardComponent.hpp"
#include "MouseComponent.hpp"
#include "Camera.hpp"
#include "Node.hpp"
#include "DirectX11Helper.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

namespace RenderingEngine
{

	ZRenderingEngine::ZRenderingEngine(HINSTANCE l_instance, const std::wstring& l_windowClass,
		const std::wstring& l_windowTitle, int l_showCommand) : Library::Engine(l_instance, l_windowClass,
			l_windowTitle, l_showCommand)
	{
		m_multiSamplingEnabled = true;
		m_depthStencilBufferEnabled = true;
	}

	void ZRenderingEngine::Initialize()
	{
		using namespace Library;


		m_components.emplace_back(std::make_unique<FPSComponent>(*this));
		m_serviceProvider.AddService(((FPSComponent*)m_components[0].get())->TypeIdClass(), (void*)m_components[0].get());
		m_components.emplace_back(std::make_unique<KeyboardComponent>(*this));
		m_serviceProvider.AddService(((KeyboardComponent*)m_components[1].get())->TypeIdClass(), (void*)m_components[1].get());
		m_components.emplace_back(std::make_unique<MouseComponent>(*this));
		m_serviceProvider.AddService(((MouseComponent*)m_components[2].get())->TypeIdClass(), (void*)m_components[2].get());
		m_components.emplace_back(std::make_unique<Camera>(*this));
		m_serviceProvider.AddService(((Camera*)m_components[3].get())->TypeIdClass(), (void*)m_components[3].get());

		std::string lv_modelName{};
		while (m_modelNamesFile >> lv_modelName) {
			std::string lv_modelFullPath{ EngineGlobalVariables::lv_modelsFolderPath + lv_modelName + "/gltf/" + lv_modelName + ".gltf" };
			Model lv_model{ GetEngine(), lv_modelFullPath };
			m_models.emplace(std::move(lv_modelName), std::move(lv_model));
		}

		for (auto& l_model : m_models) {
			for (auto& l_mesh : l_model.second.GetMeshes()) {
				m_components.emplace_back(std::make_unique<Node>(*this, DirectX::XMFLOAT3{}, l_mesh.get()));
			}
		}


		//Create main pass constant buffer resource
		{
			DirectX11Helper::CreateConstantBuffer<ShaderStructures::MainPassConstantBuffer>(m_mainPassCBData,
				&m_mainPassCB, Direct3DDevice(), 7 * 16 * sizeof(float), D3D11_USAGE_DYNAMIC,
				D3D11_CPU_ACCESS_WRITE);


			m_serviceProvider.AddService("mainPassCB", m_mainPassCB);
		}

		m_keyboard = (KeyboardComponent*)m_components[1].get();
		m_mouse = (MouseComponent*)m_components[2].get();
		m_camera = (Camera*)m_components[3].get();

		Engine::Initialize();

	}

	void ZRenderingEngine::Update(const Library::EngineTime& l_engineTime)
	{
		using namespace Library;
		using namespace DirectX;

		UpdateKeyboard(l_engineTime);
		m_camera->UpdateViewMatrix();
		UpdateMainPassConstantBuffer(l_engineTime);


		HRESULT lv_hr{};
		D3D11_MAPPED_SUBRESOURCE lv_mappedSub{};
		lv_hr = Direct3DDeviceContext()->Map(m_mainPassCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &lv_mappedSub);

		ThrowIfFailed(lv_hr, "Mapping failed for constant buffer.\n");

		Library::ShaderStructures::MainPassConstantBuffer* lv_mainPassCBData =
			(Library::ShaderStructures::MainPassConstantBuffer*)lv_mappedSub.pData;


		{
			lv_mainPassCBData->ViewProj = m_mainPassCBData.ViewProj;
			lv_mainPassCBData->View = m_mainPassCBData.View;
			lv_mainPassCBData->TotalTime = m_mainPassCBData.TotalTime;
			lv_mainPassCBData->RenderTargetSize = m_mainPassCBData.RenderTargetSize;
			lv_mainPassCBData->Proj = m_mainPassCBData.Proj;
			lv_mainPassCBData->NearZ = m_mainPassCBData.NearZ;
			lv_mainPassCBData->InvViewProj = m_mainPassCBData.InvViewProj;
			lv_mainPassCBData->InvView = m_mainPassCBData.InvView;
			lv_mainPassCBData->InvRenderTargetSize = m_mainPassCBData.InvRenderTargetSize;
			lv_mainPassCBData->InvProj = m_mainPassCBData.InvProj;
			lv_mainPassCBData->FarZ = m_mainPassCBData.FarZ;
			lv_mainPassCBData->EyePosW = m_mainPassCBData.EyePosW;
			lv_mainPassCBData->DeltaTime = m_mainPassCBData.DeltaTime;

		}

		Direct3DDeviceContext()->Unmap(m_mainPassCB, 0);


		Library::Engine::Update(l_engineTime);
	}

	void ZRenderingEngine::Draw(const Library::EngineTime& l_engineTime)
	{
		m_direct3DDeviceContext->ClearRenderTargetView(m_renderTargetView, m_defaultBackGroundColor);
		m_direct3DDeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL
			, 1.f, 0);

		Library::Engine::Draw(l_engineTime);

		HRESULT lv_hr = m_swapChain->Present(0, 0);

		Library::ThrowIfFailed(lv_hr, "IDXGISwapChain::Present() failed.\n");

	}


	void ZRenderingEngine::UpdateMainPassConstantBuffer(const Library::EngineTime& l_engineTime)
	{
		using namespace DirectX;

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
		m_mainPassCBData.RenderTargetSize = XMFLOAT2((float)ScreenWidth(), (float)ScreenHeight());
		m_mainPassCBData.InvRenderTargetSize = XMFLOAT2(1.0f / (float)ScreenWidth(), 1.0f / (float)ScreenHeight());
		m_mainPassCBData.NearZ = 1.0f;
		m_mainPassCBData.FarZ = 10000.0f;
		m_mainPassCBData.TotalTime = l_engineTime.TotalEngineTimeSeconds().count();
		m_mainPassCBData.DeltaTime = l_engineTime.ElapsedEngineTimeSeconds().count();
	}


	void ZRenderingEngine::UpdateKeyboard(const Library::EngineTime& l_engineTime)
	{
		using namespace Library;
		using namespace DirectX;

		const float dt = l_engineTime.ElapsedEngineTimeSeconds().count();
		const float lv_multiplier{ 10.f };


		if (true == m_keyboard->WasKeyPressedThisFrame(Keys::Escape)) {
			PostQuitMessage(0);
		}

		if (true == m_keyboard->IsKeyDown(Keys::W) || true == m_keyboard->IsKeyHeldDown(Keys::W)) {
			m_camera->Walk(lv_multiplier * dt);

		}

		if (true == m_keyboard->IsKeyDown(Keys::D) || true == m_keyboard->IsKeyHeldDown(Keys::D)) {
			m_camera->Strafe(lv_multiplier * dt);

		}

		if (true == m_keyboard->IsKeyDown(Keys::S) || true == m_keyboard->IsKeyHeldDown(Keys::S)) {
			m_camera->Walk(-lv_multiplier * dt);

		}

		if (true == m_keyboard->IsKeyDown(Keys::A) || true == m_keyboard->IsKeyHeldDown(Keys::A)) {
			m_camera->Strafe(-lv_multiplier * dt);
		}
	}
}