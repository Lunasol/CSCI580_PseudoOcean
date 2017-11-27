/**
* ShaderTechnique.h
*
* This struct is a container for compiled shader blobs.  It allows for simple 
* shader compilation and binding to the GPU pipeline.  Can contain several 
* shaders (VS, GS, PS, CS)!
*/
#pragma once
// General includes
#include <assert.h>

// Preprocessor Definition Includes
#include "PreprocessorDefinitions.h"

// Include the renderer object
#include "ID3D11Renderer.h"

enum ShaderTechniqueMasks {
	VS = 1,
	GS = 2,
	PS = 4,
	CS = 8,
	VSPS = VS + PS,
	VSGSPS = VS + GS + PS
};

union ShaderBitmask{
	ShaderBitmask() { m_mask = 0; }
	~ShaderBitmask() {}

	__int16 m_mask;
	char m_byteMask[2];
};

struct ShaderTechnique
{
	ShaderTechnique();
	~ShaderTechnique();


	HRESULT LoadTechnique(LPCWSTR vsSrcFile, LPCSTR vsEntryPoint, LPCWSTR gsSrcFile, LPCSTR gsEntryPoint, LPCWSTR psSrcFile, LPCSTR psEntryPoint, LPCWSTR csSrcFile, LPCSTR csEntryPoint, int vertexBufType);

	void BindTechnique();

private:

	void GenerateInputLayout(int inputLayout, int shaderType, D3D11_INPUT_ELEMENT_DESC * elementDescs);

	ShaderBitmask m_bitMask;

	// The shader pointers in this technique
	ID3D11VertexShader *m_pVertexShader;
	ID3D11GeometryShader *m_pGeometryShader;
	ID3D11PixelShader *m_pPixelShader;
	ID3D11ComputeShader *m_pComputeShader;

	ID3D11InputLayout *m_pVLayout, *m_pGLayout, *m_pCLayout;
};