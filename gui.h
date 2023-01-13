#pragma once


#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <iostream>
#include <string>

class Renderer 
{
public:
    static Renderer* Instance();

    void render(void(*callBack)());
private:
	Renderer();

    ~Renderer();
    static Renderer* instance;
	// Data
	static ID3D11Device* g_pd3dDevice;
	static ID3D11DeviceContext* g_pd3dDeviceContext;
	static IDXGISwapChain* g_pSwapChain;
	static ID3D11RenderTargetView* g_mainRenderTargetView;

	// Forward declarations of helper functions
	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
    static bool show_demo_window;
    static ImVec4 clear_color;

    static WNDCLASSEXW wc;
    static HWND hwnd;
};







