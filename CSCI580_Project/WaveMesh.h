/**
* WaveMesh
*
* Description
* This is the final Graphics object.  We created a shader technique,
* an input layout, a vertex buffer format, and a index buffer.  Now
* we need some sort of object that handles the collection of this info
* and renders the actual object.
*/
#pragma once
// Render Object includes
#include "./ID3D11Renderer.h"
#include "./ShaderTechnique.h"
#include "./VertexBufferLayout.h"
#include "./VertexBufferGPU.h"
#include "./WaveGenerator.h"

struct WaveMesh
{
	WaveMesh();
	~WaveMesh();

	// Member Methods
	void InitWaveMesh(int numVerts, int xVertexCount, int yVertexCount, WaveVertex * verts);

	void Draw();

private:
	VertexBufferGPU m_VertexBuffer;
	ShaderTechnique m_ShaderTech;
	
};

