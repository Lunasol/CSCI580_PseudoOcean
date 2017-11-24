#include "./WaveGenerator.h"

WaveGenerator::WaveGenerator()
{
	m_pWaveVertices = nullptr;
	m_time = time(nullptr);
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
	if (m_pWaveVertices)
		free(m_pWaveVertices);

	m_pWaveVertices = EALLOC(WaveVertex, vertexResolutionX * vertexResolutionZ);

	m_time = time(nullptr);

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

	return m_pWaveVertices;
}

float WaveGenerator::GetDeltaTime()
{
	m_time = time(nullptr) - m_time;
	return m_time;
}