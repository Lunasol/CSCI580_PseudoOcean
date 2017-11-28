/**
* ShaderTechnique.h
*
* This struct is a container for compiled shader blobs.  It allows for simple
* shader compilation and binding to the GPU pipeline.  Can contain several
* shaders (VS, GS, PS, CS)!
*/
#include "ShaderTechnique.h"

#define VERTEX 0
#define GEOMETRY 1
#define PIXEL 2
#define COMPUTE 3

// Generic Constructor
ShaderTechnique::ShaderTechnique()
{
	m_pVertexShader = nullptr;
	m_pGeometryShader = nullptr;
	m_pPixelShader = nullptr;
	m_pComputeShader = nullptr;
	m_pVLayout = nullptr;
	/// Set up Constant buffer?
}

// ShaderTechnique Destructor
ShaderTechnique::~ShaderTechnique()
{
	// TODO
	if (m_pVertexShader) {
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}
	if (m_pGeometryShader) {
		m_pGeometryShader->Release();
		m_pGeometryShader = nullptr;
	}
	if (m_pPixelShader) {
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}
	if (m_pComputeShader) {
		m_pComputeShader->Release();
		m_pComputeShader = nullptr;
	}
	if (m_pVLayout){
		m_pVLayout->Release();
		m_pVLayout = nullptr;
	}
}

/**
* BindTechnique()
*
* Description:
* Bind this technique's shaders.  Very simplified form since we don't have
* any additional shaders.
*/
void ShaderTechnique::BindTechnique()
{
	ID3D11Renderer *pRenderer = ID3D11Renderer::Instance();

	pRenderer->getDeviceContextPtr()->IASetInputLayout(m_pVLayout);

	if (m_pVertexShader) {
		pRenderer->getDeviceContextPtr()->VSSetShader(m_pVertexShader, NULL, 0);
		if (m_pPixelShader)
			pRenderer->getDeviceContextPtr()->PSSetShader(m_pPixelShader, NULL, 0);
		else
			exit(EXIT_FAILURE);
	}
	else {
		exit(EXIT_FAILURE);
	}
}

/**
*/
HRESULT ShaderTechnique::LoadTechnique(
	LPCWSTR vsSrcFile, LPCSTR vsEntryPoint,
	LPCWSTR gsSrcFile, LPCSTR gsEntryPoint,
	LPCWSTR psSrcFile, LPCSTR psEntryPoint,
	LPCWSTR csSrcFile, LPCSTR csEntryPoint,
	int inputBufLayout
	)
{
	HRESULT vsResult, psResult, gsResult, csResult;
	ID3D11Renderer *pRenderer = ID3D11Renderer::Instance();
	ID3DBlob *m_pVSBlob, *m_pGSBlob, *m_pPSBlob, *m_pCSBlob;
	D3D11_INPUT_ELEMENT_DESC *inputLayout;
	m_pVSBlob = m_pGSBlob = m_pPSBlob = m_pCSBlob = NULL;
	int inputLayoutSize;

	// Compile the given shader files
	if (vsSrcFile) 
	{
		m_bitMask.m_mask += ShaderTechniqueMasks::VS;
		vsResult = pRenderer->CompileShaderFromFile(
			vsSrcFile, vsEntryPoint, VSPROFILE, &m_pVSBlob
		);
		if (FAILED(vsResult))
			exit(EXIT_FAILURE);

		vsResult = pRenderer->getDevicePtr()->CreateVertexShader(
			m_pVSBlob->GetBufferPointer(), 
			m_pVSBlob->GetBufferSize(),
			NULL, 
			&m_pVertexShader
		);

		if (FAILED(vsResult))
			exit(EXIT_FAILURE);

		// Now create the input for the vertex shaders
		inputLayout = EALLOC(D3D11_INPUT_ELEMENT_DESC, 2);
		GenerateInputLayout(inputBufLayout, VERTEX, inputLayout);
		vsResult = pRenderer->getDevicePtr()->CreateInputLayout(
			inputLayout, 
			2, 
			m_pVSBlob->GetBufferPointer(),
			m_pVSBlob->GetBufferSize(), 
			&m_pVLayout
		);
		if (FAILED(vsResult))
			exit(EXIT_FAILURE);
		free(inputLayout);

		m_pVSBlob->Release();
	}
	if (gsSrcFile)
	{
		assert(
			m_bitMask.m_mask & ShaderTechniqueMasks::VS,
			"Geometry Shaders must be compiled alongside a vertex shader"
		);
		m_bitMask.m_mask += ShaderTechniqueMasks::GS;
		gsResult = pRenderer->CompileShaderFromFile(
			gsSrcFile, gsEntryPoint, GSPROFILE, &m_pGSBlob
		);
		if (FAILED(gsResult))
		{
			// TODO PRINT DEBUGGING INFO
			exit(EXIT_FAILURE);
		}
		pRenderer->getDevicePtr()->CreateGeometryShader(
			m_pGSBlob->GetBufferPointer(),
			m_pGSBlob->GetBufferSize(),
			NULL,
			&m_pGeometryShader
		);
		m_pGSBlob->Release();
	}
	if (psSrcFile)
	{
		assert(
			m_bitMask.m_mask & ShaderTechniqueMasks::VS, 
			"Pixel Shaders must be compiled alongside a vertex shader"
		);
		m_bitMask.m_mask += ShaderTechniqueMasks::PS;
		psResult = pRenderer->CompileShaderFromFile(
			psSrcFile, psEntryPoint, PSPROFILE, &m_pPSBlob
		);
		if (FAILED(psResult))
		{
			// TODO PRINT DEBUGGING INFO
			exit(EXIT_FAILURE);
		}
		psResult = pRenderer->getDevicePtr()->CreatePixelShader(
			m_pPSBlob->GetBufferPointer(),
			m_pPSBlob->GetBufferSize(),
			NULL,
			&m_pPixelShader
		);
		if (FAILED(psResult))
		{
			// TODO PRINT DEBUGGING INFO
			exit(EXIT_FAILURE);
		}
		m_pPSBlob->Release();
	}
	if (csSrcFile)
	{
		assert(
			m_bitMask.m_mask == 0, 
			"Compute Shaders must be compiled with no other shaders!"
		);
		m_bitMask.m_mask += ShaderTechniqueMasks::CS;
		csResult = pRenderer->CompileShaderFromFile(
			gsSrcFile, gsEntryPoint, CSPROFILE, &m_pCSBlob
		);
		if (FAILED(csResult))
		{
			// TODO PRINT DEBUGGING INFO
			exit(EXIT_FAILURE);
		}
		pRenderer->getDevicePtr()->CreateComputeShader(
			m_pPSBlob->GetBufferPointer(),
			m_pPSBlob->GetBufferSize(),
			NULL,
			&m_pComputeShader
		);
		m_pCSBlob->Release();
	}

}

// This is going to be a big function
void ShaderTechnique::GenerateInputLayout(int inputLayout, int shaderType, D3D11_INPUT_ELEMENT_DESC * elementDescs)
{
	switch (inputLayout)
	{
		case VertexFormatLayout_CPUTerrain_B0_P0f3_TC0f2_N0f3_B1_I0i3:
		{
			switch (shaderType) 
			{
			case VERTEX:
				// Element 0
				elementDescs[0].SemanticName = "POSITION";
				elementDescs[0].SemanticIndex = 0;
				elementDescs[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				elementDescs[0].InputSlot = 0;
				elementDescs[0].AlignedByteOffset = 0;
				elementDescs[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				elementDescs[0].InstanceDataStepRate = 0;

				// Element 1
				elementDescs[1].SemanticName = "NORMAL";
				elementDescs[1].SemanticIndex = 0;
				elementDescs[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				elementDescs[1].InputSlot = 0;
				elementDescs[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				elementDescs[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				elementDescs[1].InstanceDataStepRate = 0;

				// Element 2
				/*elementDescs[2].SemanticName = "COLOR";
				elementDescs[2].SemanticIndex = 0;
				elementDescs[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				elementDescs[2].InputSlot = 0;
				elementDescs[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				elementDescs[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				elementDescs[2].InstanceDataStepRate = 0;*/
				break;

			case GEOMETRY:

				break;

			case PIXEL:

				break;

			case COMPUTE:

				break;
			}

			break;
		}
	}
}

