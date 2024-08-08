

//Need it for D3D11CreateDevice()
#pragma comment(lib,"d3d11.lib")

#include <d3d11.h>
#include <array>
#include "Engine.hpp"
#include "EngineException.hpp"
#include "Common.hpp"
#include "Entity.hpp"
#include "directxtk/Keyboard.h"
#include "directxtk/Mouse.h"
#include "DrawableEntity.hpp"
#include "EngineGlobalVariables.hpp"


namespace Library
{
	const UINT Engine::lv_defaultScreenHeight = 512;
	const UINT Engine::lv_defaultScreenWidth = 1024;
	const UINT Engine::lv_defaultFrameRate = 60;
	const UINT Engine::lv_defaultMultiSamplingCount = 4;

	Engine::Engine(HINSTANCE l_instance, const std::wstring& l_windowClass,
		const std::wstring& l_windowTitle, int l_showCommand) : m_windowClass(l_windowClass),
		m_windowTitle(l_windowTitle), m_showCommand(l_showCommand) {};

	Engine::~Engine() = default;

	HINSTANCE Engine::Instance() const { return m_instance; }
	HWND Engine::WindowHandle() const { return m_windowHandle; }
	const WNDCLASSEX& Engine::Window() const { return m_window; }
	const std::wstring& Engine::WindowClass() const { return m_windowClass; }
	const std::wstring& Engine::WindowTitle() const { return m_windowTitle; }
	int Engine::ScreenWidth() const { return m_screenWidth; }
	int Engine::ScreenHeight() const { return m_screenHeight; }

	//virtual void Exit();
	

	ID3D11Device1* Engine::Direct3DDevice() const { return m_direct3DDevice; };
	ID3D11DeviceContext1* Engine::Direct3DDeviceContext() const { return m_direct3DDeviceContext; }
	bool Engine::DepthBufferEnabled() const { return m_depthStencilBufferEnabled; }
	bool Engine::IsFullScreen() const { return m_isFullScreen; }
	const std::vector<std::unique_ptr<Entity>>& Engine::GetEntities() const { return m_entities; }
	const D3D11_TEXTURE2D_DESC& Engine::BackBufferDesc() const { return m_backbufferDesc; }
	const D3D11_VIEWPORT& Engine::Viewport() const { return m_viewport; }


	void Engine::InitializeWindow()
	{
		ZeroMemory(&m_window, sizeof(m_window));
		m_window.cbSize = sizeof(WNDCLASSEX);
		m_window.style = CS_CLASSDC;
		m_window.lpfnWndProc = WndProc;
		m_window.hInstance = m_instance;
		m_window.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		m_window.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		m_window.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_window.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
		m_window.lpszClassName = m_windowClass.c_str();

		RECT lv_windowRectangle{0, 0, static_cast<LONG>(m_screenWidth), static_cast<LONG>(m_screenHeight)};
		AdjustWindowRect(&lv_windowRectangle, WS_OVERLAPPEDWINDOW,FALSE);

		RegisterClassEx(&m_window);
		POINT lv_center = CenterWindow(m_screenWidth, m_screenHeight);
		m_windowHandle = CreateWindow(m_windowClass.c_str(), m_windowTitle.c_str(),
			WS_OVERLAPPEDWINDOW, lv_center.x, lv_center.y,
			lv_windowRectangle.right-lv_windowRectangle.left,
			lv_windowRectangle.bottom-lv_windowRectangle.top,
			nullptr, nullptr, m_instance, nullptr);

		ShowWindow(m_windowHandle, m_showCommand);
		UpdateWindow(m_windowHandle);

	}

	LRESULT WINAPI Engine::WndProc(HWND l_windowHandle, UINT l_message,
		WPARAM l_wParam, LPARAM l_param)
	{
		switch (l_message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_ACTIVATEAPP:
			DirectX::Keyboard::ProcessMessage(l_message, l_wParam, l_param);
			DirectX::Mouse::ProcessMessage(l_message, l_wParam, l_param);
			break;

		case WM_ACTIVATE:
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEHOVER:
			DirectX::Mouse::ProcessMessage(l_message, l_wParam, l_param);
			break;


		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		case WM_SYSKEYDOWN:
			DirectX::Keyboard::ProcessMessage(l_message, l_wParam, l_param);
			break;
		}



		return DefWindowProc(l_windowHandle, l_message, l_wParam,
			l_param);
	}

	POINT Engine::CenterWindow(int l_windowWidth, int l_windowHeight)
	{
		int lv_screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int lv_screenHeight = GetSystemMetrics(SM_CYSCREEN);

		POINT lv_center{};
		lv_center.x = (lv_screenWidth-l_windowWidth)/2;
		lv_center.y = (lv_screenHeight-l_windowHeight) / 2;

		return lv_center;
	}

	void Engine::Run()
	{
		InitializeWindow();
		InitializeDirectX();
		Initialize();

		MSG lv_message{};
		ZeroMemory(&lv_message, sizeof(lv_message));

		m_engineClock.Reset();

		while (WM_QUIT != lv_message.message) {
			if (PeekMessage(&lv_message, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&lv_message);
				DispatchMessage(&lv_message);
			}
			else {
				m_engineClock.UpdateEngineTime(m_engineTime);
				Update(m_engineTime);
				Draw(m_engineTime);
			}
		}
		Shutdown();
	}
	

	void Engine::Initialize()
	{
		for (auto& l_entity : m_entities) {
			l_entity->Initialize();
		}
	}

	void Engine::Update(const EngineTime& l_engineTime)
	{
		EngineGlobalVariables::lv_UpdatePerFrameConstantBuffers = true;
		for (auto& l_entity : m_entities) {
			l_entity->Update(l_engineTime);
		}
	}

	void Engine::Draw(const EngineTime& l_engineTime)
	{
		for (auto& l_entity : m_entities) {
			DrawableEntity* lv_drawableEnity = l_entity->As<DrawableEntity>();
			if (nullptr != lv_drawableEnity) {
				lv_drawableEnity->Draw(l_engineTime);
			}
		}
	}


	InputEventHandler& Engine::GetInputEventHandler()
	{
		return m_inputEventHandler;
	}


	void Engine::InitializeDirectX()
	{
		HRESULT lv_hr{};
		UINT lv_createDeviceFlag{};

#if defined(DEBUG) || defined(_DEBUG)
		lv_createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		//Creating device and device context
		{
			ID3D11Device* lv_device{};
			ID3D11DeviceContext* lv_deviceContext{};
			std::array<D3D_FEATURE_LEVEL, 2> lv_featureLevels{ D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

			lv_hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
				lv_createDeviceFlag, lv_featureLevels.data(), (UINT)lv_featureLevels.size(),
				D3D11_SDK_VERSION, &lv_device, &m_featureLevel, &lv_deviceContext);
			ThrowIfFailed(lv_hr, "D3D11CreateDevice() failed.\n");

			lv_hr = lv_device->QueryInterface(__uuidof(ID3D11Device1),
				reinterpret_cast<void**>(&m_direct3DDevice));
			ThrowIfFailed(lv_hr, "QueryInterface() failed for ID3D11Device1.\n");

			lv_hr = lv_deviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1),
				reinterpret_cast<void**>(&m_direct3DDeviceContext));
			ThrowIfFailed(lv_hr, "QueryInterface() failed for ID3D11DeviceContext1.\n");

			ReleaseObject(lv_device);
			ReleaseObject(lv_deviceContext);
		}

		//Create swap chain
		{
			lv_hr = m_direct3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM,
				m_multiSamplingCount, &m_multiSamplingQualityLevels);
			ThrowIfFailed(lv_hr, "Multisampling not supported with the provided count and format.\n");
			if (0 == m_multiSamplingQualityLevels) { ThrowIfFailed(lv_hr, "Multisampling not supported with the provided count and format.\n"); }

			DXGI_SWAP_CHAIN_DESC1 lv_swapChainDes{};
			ZeroMemory(&lv_swapChainDes, sizeof(lv_swapChainDes));
			lv_swapChainDes.Width = m_screenWidth;
			lv_swapChainDes.Height = m_screenHeight;
			lv_swapChainDes.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			lv_swapChainDes.Stereo = false;
			if (m_multiSamplingEnabled) { lv_swapChainDes.SampleDesc = { m_multiSamplingCount, m_multiSamplingQualityLevels - 1 }; }
			else { lv_swapChainDes.SampleDesc = { 1, 0 }; }
			lv_swapChainDes.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			lv_swapChainDes.BufferCount = 1;
			lv_swapChainDes.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			IDXGIDevice* lv_dxgiDevice{};
			lv_hr = m_direct3DDevice->QueryInterface(__uuidof(IDXGIDevice),
				reinterpret_cast<void**>(&lv_dxgiDevice));
			ThrowIfFailed(lv_hr, "QueryInterface() failed to get reference to an IDXGIDevice object.\n");

			IDXGIAdapter* lv_dxgiAdapter{};
			lv_hr = lv_dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&lv_dxgiAdapter));
			if (FAILED(lv_hr)) {
				ReleaseObject(lv_dxgiDevice);
				throw EngineException{"Failed to get the parent object of an IDXGIDevice at initialization of directx.\n", lv_hr};
			}

			IDXGIFactory2* lv_dxgiFactory2{};
			lv_hr = lv_dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&lv_dxgiFactory2));
			if (FAILED(lv_hr)) {
				ReleaseObject(lv_dxgiDevice);
				ReleaseObject(lv_dxgiAdapter);
				throw EngineException{ "Failed to get the parent object of an IDXGIAdapter at initialization of directx.\n", lv_hr };
			}

			DXGI_SWAP_CHAIN_FULLSCREEN_DESC lv_fullScreenDes{};
			ZeroMemory(&lv_fullScreenDes, sizeof(lv_fullScreenDes));
			lv_fullScreenDes.RefreshRate = {m_frameRate, 1};
			lv_fullScreenDes.Windowed = !m_isFullScreen;
			lv_fullScreenDes.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
			
			lv_hr = lv_dxgiFactory2->CreateSwapChainForHwnd(m_direct3DDevice, m_windowHandle,
				&lv_swapChainDes, &lv_fullScreenDes, nullptr, (&m_swapChain));
			if (FAILED(lv_hr)) {
				ReleaseObject(lv_dxgiDevice);
				ReleaseObject(lv_dxgiAdapter);
				ReleaseObject(lv_dxgiFactory2);
				throw EngineException{ "Failed to create swap chain.\n", lv_hr };
			}

		}

		//Create render target and depth stencil buffer views
		{
			ID3D11Texture2D* lv_backBuffer{};
			lv_hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
				reinterpret_cast<void**>(&lv_backBuffer));
			ThrowIfFailed(lv_hr, "GetBuffer() failed to retrieve back buffer at initialization.\n");

			lv_backBuffer->GetDesc(&m_backbufferDesc);
			lv_hr = m_direct3DDevice->CreateRenderTargetView(lv_backBuffer,nullptr, &m_renderTargetView);
			if (FAILED(lv_hr)) {
				ReleaseObject(lv_backBuffer);
				throw EngineException{ "ID3D11Device::CreateRenderTargetView() failed.\n", lv_hr };
			}
			ReleaseObject(lv_backBuffer);

			D3D11_TEXTURE2D_DESC lv_texture2DDesc{};
			ZeroMemory(&lv_texture2DDesc, sizeof(lv_texture2DDesc));
			lv_texture2DDesc.Width = m_screenWidth;
			lv_texture2DDesc.Height = m_screenHeight;
			if (m_multiSamplingEnabled) {
				lv_texture2DDesc.SampleDesc.Count = m_multiSamplingCount;
				lv_texture2DDesc.SampleDesc.Quality = m_multiSamplingQualityLevels - 1;
			}
			else {
				lv_texture2DDesc.SampleDesc.Count = 1;
				lv_texture2DDesc.SampleDesc.Quality = 0;
			}
			lv_texture2DDesc.ArraySize = 1;
			lv_texture2DDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			lv_texture2DDesc.Usage = D3D11_USAGE_DEFAULT;
			lv_texture2DDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			lv_texture2DDesc.MipLevels = 1;
			lv_hr = m_direct3DDevice->CreateTexture2D(&lv_texture2DDesc, nullptr, &m_depthStencilBuffer);
			ThrowIfFailed(lv_hr, "ID3D11Device::CreateTexture2D() failed.\n");

			lv_hr = m_direct3DDevice->CreateDepthStencilView(m_depthStencilBuffer, nullptr, &m_depthStencilView);
			ThrowIfFailed(lv_hr, "ID3D11Device::CreateDepthStencilView() failed.\n");
		}

		//Attach back buffer and depth stencil buffers via their views to the OM
		{
			m_direct3DDeviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
		}

		//Initialize and set the viewport
		{
			m_viewport.Height = static_cast<float>(m_screenHeight);
			m_viewport.Width = static_cast<float>(m_screenWidth);
			m_viewport.TopLeftX = 0.f;
			m_viewport.TopLeftY = 0.f;
			m_viewport.MaxDepth = 1.f;
			m_viewport.MinDepth = 0.f;

			m_direct3DDeviceContext->RSSetViewports(1, &m_viewport);
		}
	}

	void Engine::Shutdown()
	{
		ReleaseObject(m_depthStencilView);
		ReleaseObject(m_renderTargetView);
		ReleaseObject(m_direct3DDevice);
		ReleaseObject(m_depthStencilBuffer);
		ReleaseObject(m_swapChain);

		if (nullptr != m_direct3DDeviceContext) {
			m_direct3DDeviceContext->ClearState();
		}

		ReleaseObject(m_direct3DDeviceContext);
		UnregisterClass(m_windowClass.c_str(), m_window.hInstance);
	}
}
