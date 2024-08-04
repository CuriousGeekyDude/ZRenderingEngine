#pragma once 


#include <Windows.h>
#include <memory>
#include <string>
#include <vector>
#include <d3d11_1.h>
#include "EngineClock.hpp"
#include "EngineTime.hpp"
#include "ServiceProvider.hpp"
#include "Component.hpp"

namespace Library
{
	class Component;

	class Engine
	{
	public:

		Engine(HINSTANCE l_instance, const std::wstring& l_windowClass,
			const std::wstring& l_windowTitle, int l_showCommand);
		Engine(const Engine& l_rhs) = delete;
		Engine& operator=(const Engine& l_rhs)=delete;


		virtual ~Engine();

		HINSTANCE Instance() const;
		HWND WindowHandle() const;
		const WNDCLASSEX& Window() const;
		const std::wstring& WindowClass() const;
		const std::wstring& WindowTitle() const;
		int ScreenWidth() const;
		int ScreenHeight() const;

		virtual void Run();
		virtual void Initialize();
		virtual void Update(const EngineTime& l_engineTime);
		virtual void Draw(const EngineTime& l_engineTime);

		ID3D11Device1* Direct3DDevice() const;
		ID3D11DeviceContext1* Direct3DDeviceContext() const;
		bool DepthBufferEnabled() const;
		bool IsFullScreen() const;
		const std::vector<std::unique_ptr<Component>>& GetComponents() const;
		const D3D11_TEXTURE2D_DESC& BackBufferDesc() const;
		const D3D11_VIEWPORT& Viewport() const;
		const ServiceProvider& GetServiceProvider() const;

	protected:
		virtual void InitializeWindow();
		virtual void InitializeDirectX();
		virtual void Shutdown();

		Engine* GetEngine() { return this; }

		static const UINT lv_defaultScreenWidth;
		static const UINT lv_defaultScreenHeight;
		static const UINT lv_defaultFrameRate;
		static const UINT lv_defaultMultiSamplingCount;

		D3D_FEATURE_LEVEL m_featureLevel{D3D_FEATURE_LEVEL_11_0};
		ID3D11Device1* m_direct3DDevice{};
		ID3D11DeviceContext1* m_direct3DDeviceContext{};
		IDXGISwapChain1* m_swapChain{};

		UINT m_frameRate{lv_defaultFrameRate};
		bool m_isFullScreen{false};
		bool m_depthStencilBufferEnabled{false};
		bool m_multiSamplingEnabled{false};
		UINT m_multiSamplingCount{lv_defaultMultiSamplingCount};
		UINT m_multiSamplingQualityLevels{};

		ID3D11Texture2D* m_depthStencilBuffer{};
		D3D11_TEXTURE2D_DESC m_backbufferDesc{};
		ID3D11RenderTargetView* m_renderTargetView{};
		ID3D11DepthStencilView* m_depthStencilView{};
		D3D11_VIEWPORT m_viewport{};

		HINSTANCE m_instance{};
		std::wstring m_windowClass{};
		std::wstring m_windowTitle{};
		int m_showCommand{};

		HWND m_windowHandle{};
		WNDCLASSEX m_window{};

		UINT m_screenWidth{lv_defaultScreenWidth};
		UINT m_screenHeight{lv_defaultScreenHeight};


		EngineClock m_engineClock{};
		EngineTime m_engineTime{};


		std::vector<std::unique_ptr<Component>> m_components{};

		ServiceProvider m_serviceProvider{};

	private:
		POINT CenterWindow(int l_windowWidth, int l_windowHeight);
		static LRESULT WINAPI WndProc(HWND l_windowHandle, UINT l_message,
			WPARAM, LPARAM l_param);
	};
}