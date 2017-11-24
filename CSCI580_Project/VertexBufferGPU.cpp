#include "VertexBufferGPU.h"

struct testVert {
	FLOAT pos[3];
	FLOAT color[4];
	//FLOAT norm[3];
};

VertexBufferGPU::VertexBufferGPU() {}

//VertexBufferGPU::VertexBufferGPU(int size)
//{
//
//}

VertexBufferGPU::~VertexBufferGPU() {}

void VertexBufferGPU::InitBuffer(int bufferLayout)
{
	/// DEBUGGING
	testVert testVerts[] =
	{
		{0.f, 0.5f, 0.f, 1.0, 0.f, 0.f, 0.f},
		{ 0.f, 0.5f, 0.f, 1.0, 0.f, 0.f, 0.f },
		{ 0.f, 0.5f, 0.f, 1.0, 0.f, 0.f, 0.f },
	};
	/// DEBUGGING

	D3D11_BUFFER_DESC bufDesc;
	ZeroMemory(&bufDesc, sizeof(bufDesc));

	bufDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufDesc.ByteWidth = sizeof(testVert) * 3;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	ID3D11Device *pDevice = ID3D11Renderer::Instance()->getDevicePtr();
	pDevice->CreateBuffer(&bufDesc, nullptr, &m_pVBuffer);

	ID3D11DeviceContext *pDevContext = ID3D11Renderer::Instance()->getDeviceContextPtr();
	D3D11_MAPPED_SUBRESOURCE ms;

	/// DEBUGGING
	pDevContext->Map(
		m_pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms
	);
	memcpy(ms.pData, testVerts, sizeof(testVerts));
	pDevContext->Unmap(m_pVBuffer, NULL);
	/// DEBUGGING
}