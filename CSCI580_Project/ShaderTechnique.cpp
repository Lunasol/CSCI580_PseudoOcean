/**
* ShaderTechnique.h
*
* This struct is a container for compiled shader blobs.  It allows for simple
* shader compilation and binding to the GPU pipeline.  Can contain several
* shaders (VS, GS, PS, CS)!
*/
#include "ShaderTechnique.h"

#define VERTEXSHADERDESC 0

// Generic Constructor
ShaderTechnique::ShaderTechnique()
{
	m_pVertexShader = nullptr;
	m_pGeometryShader = nullptr;
	m_pPixelShader = nullptr;
	m_pComputeShader = nullptr;
	/// Set up Constant buffer?
}

// ShaderTechnique Destructor
ShaderTechnique::~ShaderTechnique()
{
	// TODO
	if (m_pVertexShader)
		m_pVertexShader->Release();
	if (m_pGeometryShader)
		m_pGeometryShader->Release();
	if (m_pPixelShader)
		m_pPixelShader->Release();
	if (m_pComputeShader)
		m_pComputeShader->Release();
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

	// Compile the given shader files
	if (vsSrcFile) 
	{
		m_bitMask.m_mask += ShaderTechniqueMasks::VS;
		vsResult = pRenderer->CompileShaderFromFile(
			vsSrcFile, vsEntryPoint, VSPROFILE, &m_pVSBlob
		);
		if (FAILED(vsResult)) 
		{
			// TODO PRINT DEBUGGING INFO
			exit(EXIT_FAILURE);
		}
		pRenderer->getDevicePtr()->CreateVertexShader(
			m_pVSBlob->GetBufferPointer(), 
			m_pVSBlob->GetBufferSize(),
			NULL, 
			&m_pVertexShader
		);
		inputLayout = EALLOC(D3D11_INPUT_ELEMENT_DESC, 3); // Needs to be changed
		// Now create the input for the vertex shaders
		GenerateInputLayout(inputBufLayout, inputLayout);

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
		pRenderer->getDevicePtr()->CreatePixelShader(
			m_pPSBlob->GetBufferPointer(),
			m_pPSBlob->GetBufferSize(),
			NULL,
			&m_pPixelShader
		);
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

	//return finalResult;
}

// This is going to be a big function
void ShaderTechnique::GenerateInputLayout(int inputLayout, D3D11_INPUT_ELEMENT_DESC * elementDescs)
{
	switch (inputLayout)
	{
		case VertexFormatLayout_CPUTerrain_B0_P0f3_TC0f2_N0f3_B1_I0i3:
		{
			// Element 0
			elementDescs[0].SemanticName = "POSITION";
			elementDescs[0].SemanticIndex = 0;
			elementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			elementDescs[0].InputSlot = 0;
			elementDescs[0].AlignedByteOffset = 0;
			elementDescs[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDescs[0].InstanceDataStepRate = 0;

			// Element 1
			elementDescs[1].SemanticName = "NORMAL";
			elementDescs[1].SemanticIndex = 0;
			elementDescs[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			elementDescs[1].InputSlot = 0;
			elementDescs[1].AlignedByteOffset = 0;
			elementDescs[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDescs[1].InstanceDataStepRate = 0;

			// Element 2
			elementDescs[2].SemanticName = "COLOR";
			elementDescs[2].SemanticIndex = 0;
			elementDescs[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			elementDescs[2].InputSlot = 0;
			elementDescs[2].AlignedByteOffset = 0;
			elementDescs[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDescs[2].InstanceDataStepRate = 0;

			break;
		}
	}
}

