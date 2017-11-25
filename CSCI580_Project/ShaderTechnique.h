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

	void GenerateInputLayout(int inputLayout, D3D11_INPUT_ELEMENT_DESC *elementDescs);

	////static void BindTechnique(ShaderTechnique *tech);
	//
	//HRESULT LoadTechnique(
	//	_In_ LPCWSTR vsSrcFile, _In_ LPCSTR vsEntryPoint,
	//	_In_ LPCWSTR gsSrcFile, _In_ LPCSTR gsEntryPoint,
	//	_In_ LPCWSTR psSrcFile, _In_ LPCSTR psEntryPoint,
	//	_In_ LPCWSTR csSrcFile, _In_ LPCSTR csEntryPoint
	//);

private:
	ShaderBitmask m_bitMask;

	// The shader pointers in this technique
	ID3D11VertexShader *m_pVertexShader;
	ID3D11GeometryShader *m_pGeometryShader;
	ID3D11PixelShader *m_pPixelShader;
	ID3D11ComputeShader *m_pComputeShader;
};

