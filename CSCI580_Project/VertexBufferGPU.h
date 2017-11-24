#pragma once

// Inter-Engine
#include "./ID3D11Renderer.h"

// Vertex Buffer Includes
#include "VertexBufferLayout.h"

struct VertexBufferGPU
{
	VertexBufferGPU();
	~VertexBufferGPU();

	void InitBuffer(int bufferFormat);

private:
	int m_layout;
	ID3D11Buffer *m_pVBuffer;
};

