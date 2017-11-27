#include "WaveMesh.h"


WaveMesh::WaveMesh()
{
}

WaveMesh::WaveMesh(VertexBufferGPU vbuffer, ShaderTechnique shadertech)
{
	m_VertexBuffer = vbuffer;
	m_ShaderTech = shadertech;
}

void WaveMesh::InitWaveMesh(int numVerts, int xVertexCount, int yVertexCount, WaveVertex * verts)
{
	m_VertexBuffer.InitBuffer(
		VertexFormatLayout_CPUTerrain_B0_P0f3_TC0f2_N0f3_B1_I0i3,
		numVerts,
		xVertexCount,
		yVertexCount,
		verts
	);
	// Test shader
	m_ShaderTech.LoadTechnique(
		L"./GPUPrograms/Wave_DebugShader_VS.hlsl", "main",
		nullptr, nullptr,
		L"./GPUPrograms/Wave_DebugShader_PS.hlsl", "main",
		nullptr, nullptr,
		VertexFormatLayout_CPUTerrain_B0_P0f3_TC0f2_N0f3_B1_I0i3
	);
}

WaveMesh::~WaveMesh()
{
}

///////////////////////////////////////////////////////
// Draw Calls
///////////////////////////////////////////////////////
void WaveMesh::Draw()
{
	ID3D11Renderer *pRenderer = ID3D11Renderer::Instance();
	unsigned int stride = sizeof(WaveVertex);
	unsigned int offset = 0;

	// Set shaders
	m_ShaderTech.BindTechnique();

	pRenderer->getDeviceContextPtr()->IASetVertexBuffers(0, 1, m_VertexBuffer.getVertexBuffer(), &stride, &offset);
	pRenderer->getDeviceContextPtr()->IASetIndexBuffer(m_VertexBuffer.getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	pRenderer->getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pRenderer->getDeviceContextPtr()->DrawIndexed(m_VertexBuffer.getNumberOfIndices(), 0, 1);
}