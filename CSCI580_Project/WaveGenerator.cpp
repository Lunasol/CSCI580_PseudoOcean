#include "./WaveGenerator.h"

WaveGenerator::WaveGenerator()
{
	m_pWaveVertices = nullptr;
	m_time = 0.f;
}

WaveGenerator::~WaveGenerator()
{
	if (m_pWaveVertices)
		free(m_pWaveVertices);
}

WaveVertex *WaveGenerator::GenerateWaveList(
	int vertexResolutionX,
	int vertexResolutionZ,
	float sizeX,
	float sizeZ
)
{
	m_pWaveVertices = EALLOC(WaveVertex, vertexResolutionX * vertexResolutionZ);

	float xOffset, zOffset;
	xOffset = sizeX / static_cast<float>(vertexResolutionX);
	zOffset = sizeZ / static_cast<float>(vertexResolutionZ);

	float xValue, zValue;

	for (int i = 0; i < vertexResolutionZ; i++)
	{
		xValue = 0.f;
		zValue = (zOffset * i);
		for (int j = 0; j < vertexResolutionX; j++)
		{
			m_pWaveVertices[i * j + j].m_x = xValue += xOffset;
			m_pWaveVertices[i * j + j].m_y = 0.f;
			m_pWaveVertices[i * j + j].m_z = zValue;
		}
	}
}