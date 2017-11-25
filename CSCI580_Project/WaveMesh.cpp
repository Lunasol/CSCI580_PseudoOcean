#include "WaveMesh.h"


WaveMesh::WaveMesh()
{
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
	//m_ShaderTech.LoadTechnique(
	//	VSNAME, main,
	//	nullptr, nullptr,
	//	PSNAME, main,
	//	nullptr, nullptr,
	//	VertexFormatLayout_CPUTerrain_B0_P0f3_TC0f2_N0f3_B1_I0i3
	//);
}



WaveMesh::~WaveMesh()
{
}

///////////////////////////////////////////////////////
// Draw Calls
///////////////////////////////////////////////////////
void WaveMesh::Draw()
{
	// TODO
}