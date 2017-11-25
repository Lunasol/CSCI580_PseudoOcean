#include "./WaveGenerator.h"

WaveGenerator::WaveGenerator()
{
	m_pGridVertices = nullptr;
	m_pWaveVertices = nullptr;
	m_time = time(nullptr);
}

WaveGenerator::~WaveGenerator()
{
	if (m_pGridVertices)
		free(m_pGridVertices);
	if (m_pWaveVertices)
		free(m_pWaveVertices);

	m_pGridVertices = nullptr;
	m_pWaveVertices = nullptr;
}

void WaveGenerator::GenerateGrid(int vertexResolutionX, int vertexResolutionZ, float sizeX, float sizeZ)
{
	if (m_pGridVertices)
		free(m_pGridVertices);

	m_pGridVertices = EALLOC(Float3, vertexResolutionX * vertexResolutionZ);
	m_pWaveVertices = EALLOC(WaveVertex, vertexResolutionX * vertexResolutionZ);
	xRes = vertexResolutionX;
	zRes = vertexResolutionZ;

	m_time = time(nullptr);

	float xOffset = sizeX / static_cast<float>(vertexResolutionX);
	float zOffset = sizeZ / static_cast<float>(vertexResolutionZ);

	float xValue, zValue;

	for (int i = 0; i < vertexResolutionZ; i++)
	{
		xValue = 0.f;
		zValue = (zOffset * i);
		for (int j = 0; j < vertexResolutionX; j++)
		{
			m_pGridVertices[INDEX].x = m_pWaveVertices[INDEX].position.x = xValue += xOffset;
			m_pGridVertices[INDEX].y = m_pWaveVertices[INDEX].position.y = 0.f;
			m_pGridVertices[INDEX].z = m_pWaveVertices[INDEX].position.z = zValue;
		}
	}
}

double WaveGenerator::GetDeltaTime()
{
	m_time = time(nullptr) - m_time;
	return m_time;
}

const WaveVertex* WaveGenerator::GetWave() const
{
	if (!m_pGridVertices || !m_pWaveVertices)
		return nullptr;

	for (int i = 0; i < xRes; ++i)
	{
		for (int j = 0; j < zRes; ++j)
		{

		}
	}


	return m_pWaveVertices;
}
