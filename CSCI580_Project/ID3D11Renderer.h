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

// SINGLETON
struct ID3D11Renderer
{
	static ID3D11Renderer *Instance();

	HRESULT InitDevice(HWND *g_hWnd);
	HRESULT CompileShaderFromFile(
		_In_ LPCWSTR srcFile, 
		_In_ LPCSTR entryPoint, 
		_In_ LPCSTR profile, 
		_Outptr_ ID3DBlob** blob
	);
	void CleanupDevice();
	void Render();

	ID3D11Device * getDevicePtr();

private:
	static ID3D11Renderer *m_pInstance;

	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pDevice = NULL;
	ID3D11DeviceContext*    m_pDeviceContext = NULL;
	IDXGISwapChain*         m_pSwapChain = NULL;
	ID3D11RenderTargetView* m_pRenderTargetsView = NULL;

	// Private Constructor and Destructor
	ID3D11Renderer();
	~ID3D11Renderer();
};

