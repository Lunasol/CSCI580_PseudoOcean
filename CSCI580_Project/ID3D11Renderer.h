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
#include <d3dcompiler.h>
#include "./Resource.h"

// Renderer Stuff
#include "./VertexBufferGPU.h"
#include "./VertexBufferLayout.h"

#pragma comment (lib, "d3d11.lib") 
#pragma comment (lib, "d3dx11.lib")

// Constant Buffer Struct
struct VS_CONSTANT_BUFFER
{
	float m_WorldViewProjMat[16];
	float m_time; // If needed
};

struct PS_CONSTANT_BUFFER_MEMBER
{
	FLOAT g_LightPos[4]; // The Last Element of 
	FLOAT g_LightDir[4];
	FLOAT g_LightColor[4];
	FLOAT g_LightTerms[4]; // Using 4 floats makes this aligned
	// KD, KS, KA, Packing
};

// This is a union that allows you to pack variables either defined or individually
union PS_CONSTANT_BUFFER
{
	PS_CONSTANT_BUFFER_MEMBER m_variables;
	float g_floats[12];
};

// Renderer
// SINGLETON
struct ID3D11Renderer
{
	static ID3D11Renderer *Instance();

	HRESULT InitDevice(HWND *g_hWnd);
	void PreRender();
	HRESULT CompileShaderFromFile(
		_In_ LPCWSTR srcFile,
		_In_ LPCSTR entryPoint,
		_In_ LPCSTR profile,
		_Outptr_ ID3DBlob** blob
	);
	void CleanupDevice();
	void UpdateConstantBuffer();
	void Render();

	ID3D11Device * getDevicePtr();
	ID3D11DeviceContext * getDeviceContextPtr();

private:
	static ID3D11Renderer *m_pInstance;

	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pDevice = nullptr;
	ID3D11DeviceContext*    m_pDeviceContext = nullptr;
	IDXGISwapChain*         m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetsView = nullptr;

	ID3D11Buffer			*m_VSConstantBuffer = nullptr;
	ID3D11Buffer			*m_GSConstantBuffer = nullptr;
	ID3D11Buffer			*m_PSConstantBuffer = nullptr;
	ID3D11Buffer			*m_CSConstantBuffer = nullptr;

	// Private Constructor and Destructor
	ID3D11Renderer();
	~ID3D11Renderer();
};

