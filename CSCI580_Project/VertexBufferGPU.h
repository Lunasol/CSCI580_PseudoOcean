#pragma once

// Inter-Engine
#include "./ID3D11Renderer.h"

// Vertex Buffer Includes
#include "VertexBufferLayout.h"
#include "WaveGenerator.h"

struct VertexBufferGPU
{
	VertexBufferGPU();
	~VertexBufferGPU();

	void InitBuffer(
		int bufferLayout,
		int vertexCount,
		int xVertexCount,
		int yVertexCount,
		WaveVertex *vertices
	);

private:
	int m_layout;
	unsigned long m_numVerts, m_numIndices;
	ID3D11Buffer *m_pVBuffer, *m_pIBuffer;
};

