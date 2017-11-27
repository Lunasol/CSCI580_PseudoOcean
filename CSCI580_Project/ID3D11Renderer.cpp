#include "ID3D11Renderer.h"
#include "SingletonMacros.h"

// Static Instance Pointer and Instance() Defintion Macro
DEFINE_SINGLETON_INSTANCE(ID3D11Renderer);

// Generic Constructors and Destructors
ID3D11Renderer::ID3D11Renderer()
{
}


ID3D11Renderer::~ID3D11Renderer()
{
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT ID3D11Renderer::InitDevice(HWND *g_hWnd)
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(*g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Set up the swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = *g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice, &m_featureLevel, &m_pDeviceContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetsView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetsView, NULL);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);

	// Init Constant buffer
	VS_CONSTANT_BUFFER vsConstBufferData;
	PS_CONSTANT_BUFFER psConstBufferData;

	// Create buffer description
	D3D11_BUFFER_DESC vsCBufferDesc;
	vsCBufferDesc.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
	vsCBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vsCBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vsCBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vsCBufferDesc.MiscFlags = 0;
	vsCBufferDesc.StructureByteStride = 0;

	D3D11_BUFFER_DESC psCBufferDesc;
	psCBufferDesc.ByteWidth = sizeof(PS_CONSTANT_BUFFER);
	psCBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	psCBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	psCBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	psCBufferDesc.MiscFlags = 0;
	psCBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;


	return S_OK;
}


//--------------------------------------------------------------------------------------
// Render the frame
//--------------------------------------------------------------------------------------
/**
*	Render()
*
*	Perform the render commands sent to the swap chain.
*
*/
void ID3D11Renderer::Render()
{
	// Just clear the backbuffer
	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetsView, ClearColor);
	m_pSwapChain->Present(0, 0);
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void ID3D11Renderer::CleanupDevice()
{
	if (m_pDeviceContext) m_pDeviceContext->ClearState();

	if (m_pRenderTargetsView) m_pRenderTargetsView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pDeviceContext) m_pDeviceContext->Release();
	if (m_pDevice) m_pDevice->Release();
}

void ID3D11Renderer::UpdateConstantBuffer()
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ID3D11Renderer *pRenderer = ID3D11Renderer::Instance();

	if (m_VSConstantBuffer)
	{
		//result = 
	}
}

/**
* HRESULT CompileShaderFromFile()
*
* Compile the passed shader into the Output blob
*/
HRESULT ID3D11Renderer::CompileShaderFromFile(
	_In_ LPCWSTR srcFile,
	_In_ LPCSTR entryPoint,
	_In_ LPCSTR profile,
	_Outptr_ ID3DBlob** blob
)
{
	ID3DBlob* errorBlob = nullptr;

	HRESULT res = D3DX11CompileFromFile
	(
		srcFile,	// File to compile shader from
		0,			// D3D10_SHADER_MACRO to be honest I have no idea what this does
		0,			// LPD3D10INCLUDE Again no idea what this is for
		entryPoint, // The starting function of the shader (ideally would be main)
		profile,	// The profile for this shader
		0,			// UINT Flags Another one I have no idea how to use.
		0,			// More flags
		0,			// ID3DX11ThreadPump I am guessing this has some control over wavefronts
		blob,		// The blob that is to contain the compiled shader code
		&errorBlob,	// ID3D10Blob ErrorMessage this blob contains any errors
		0			// HRESULT* stores the result of compiling the shader.
	);
	if (FAILED(res))
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	return res;
}

// Getters
ID3D11Device *ID3D11Renderer::getDevicePtr() { return m_pDevice; }

ID3D11DeviceContext * ID3D11Renderer::getDeviceContextPtr()
{
	return m_pDeviceContext;
}
