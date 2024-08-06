// Engine.cpp : Defines the entry point for the application.
//

#include <memory>

#include "framework.h"
#include "MainEntry.h"
#include "RenderingEngine.hpp"
#include "EngineException.hpp"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


#define MAX_LOADSTRING 100



LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    using namespace RenderingEngine;
    using namespace Library;


    std::unique_ptr<ZRenderingEngine> lv_renderer = std::make_unique<ZRenderingEngine>(hInstance,
        L"RenderingEngine", L"3D Rendering", nCmdShow);

    try
    {
        lv_renderer->Run();
    }
    catch (const EngineException& l_ex)
    {
        MessageBox(lv_renderer->WindowHandle(), l_ex.whatw().c_str(),
            lv_renderer->WindowTitle().c_str(), MB_ABORTRETRYIGNORE);
    }

    return 0;
}



