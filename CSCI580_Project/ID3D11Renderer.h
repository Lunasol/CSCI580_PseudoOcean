/**
* ID3D11Renderer.h
*
* This is the adaption of the d3d11 tutorial file.  This struct is representative of
* the D3D11 Render Target.  All shaders must be compiled here and all geometry must be
* sent here as well.
*/

#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include "./Resource.h"

struct ID3D11Renderer
{
	ID3D11Renderer();
	~ID3D11Renderer();

	HRESULT InitDevice(HWND *g_hWnd);
	HRESULT CompileShader(
		_In_ LPCWSTR srcFile, 
		_In_ LPCSTR entryPoint, 
		_In_ LPCSTR profile, 
		_Outptr_ ID3DBlob** blob
	);
	void CleanupDevice();
	void Render();


	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           g_pd3dDevice = NULL;
	ID3D11DeviceContext*    g_pImmediateContext = NULL;
	IDXGISwapChain*         g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;

};

