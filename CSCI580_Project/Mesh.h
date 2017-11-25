/**
* Mesh
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

struct Mesh
{
	Mesh();
	~Mesh();

	// Member Methods
	void Draw();

private:
	VertexBufferGPU m_VertexBuffer;
	ShaderTechnique m_ShaderTech;
	
};

