/**
* ShaderTechnique.h
*
* This struct is a container for compiled shader blobs.  It allows for simple
* shader compilation and binding to the GPU pipeline.  Can contain several
* shaders (VS, GS, PS, CS)!
*/
#include "ShaderTechnique.h"

// Generic Constructor
ShaderTechnique::ShaderTechnique()
{
}

// ShaderTechnique Destructor
ShaderTechnique::~ShaderTechnique()
{
	// TODO
}

/**
*/
HRESULT ShaderTechnique::LoadTechnique(
	LPCWSTR vsSrcFile, LPCSTR vsEntryPoint,
	LPCWSTR gsSrcFile, LPCSTR gsEntryPoint,
	LPCWSTR psSrcFile, LPCSTR psEntryPoint,
	LPCWSTR csSrcFile, LPCSTR csEntryPoint
	)
{
	HRESULT vsResult, psResult, gsResult, csResult;
	ID3D11Renderer *pRenderer = ID3D11Renderer::Instance();
	ID3DBlob *m_pVSBlob, *m_pGSBlob, *m_pPSBlob, *m_pCSBlob;
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
	}
	if (psSrcFile)
	{
		assert(
			m_bitMask.m_mask & ShaderTechniqueMasks::VS, 
			"Pixel Shaders must be compiled alongside a vertex shader"
		);
		m_bitMask.m_mask += ShaderTechniqueMasks::PS;
		psResult = pRenderer->CompileShaderFromFile(
			psSrcFile, psEntryPoint, VSPROFILE, &m_pVSBlob
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
	}
	if (csSrcFile)
	{
		assert(
			m_bitMask.m_mask == 0, 
			"Compute Shaders must be compiled with no other shaders!"
		);
		m_bitMask.m_mask += ShaderTechniqueMasks::CS;
		csResult = pRenderer->CompileShaderFromFile(
			gsSrcFile, gsEntryPoint, GSPROFILE, &m_pGSBlob
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
	}

	//return finalResult;
}

