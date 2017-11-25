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
<<<<<<< HEAD
			m_pGridVertices[INDEX].x = m_pWaveVertices[INDEX].position.x = xValue += xOffset;
			m_pGridVertices[INDEX].y = m_pWaveVertices[INDEX].position.y = 0.f;
			m_pGridVertices[INDEX].z = m_pWaveVertices[INDEX].position.z = zValue;
=======
			m_pGridVertices[INDEX].x = m_pWaveVertices[INDEX].Position.x = xValue += xOffset;
			m_pGridVertices[INDEX].y = m_pWaveVertices[INDEX].Position.y = 0.f;
			m_pGridVertices[INDEX].z = m_pWaveVertices[INDEX].Position.z = zValue;
>>>>>>> master
		}
	}
}

double WaveGenerator::GetDeltaTime()
{
	m_time = time(nullptr) - m_time;
	return m_time;
}

const WaveVertex* WaveGenerator::GetWave() 
{
	if (!m_pGridVertices || !m_pWaveVertices)
		return nullptr;

	for (int i = 0; i < xRes; ++i)
	{
		for (int j = 0; j < zRes; ++j)
		{
			float x_input = m_pGridVertices[INDEX].x;
			float y_input = m_pGridVertices[INDEX].y;
			float z_input = m_pGridVertices[INDEX].z;

			Float3 x_dir = { x_input, 0, 0 };
			Float3 z_dir = { 0, 0, z_input };
			double cos_sin_arg_input = (dot(D, m_pGridVertices[INDEX]) * W) + (phi * m_time);

			m_pWaveVertices[INDEX].Position.x = x_input + (Q*A + (dot(D, x_dir) * cos(cos_sin_arg_input)));
			m_pWaveVertices[INDEX].Position.y = A * sin(cos_sin_arg_input);
			m_pWaveVertices[INDEX].Position.z = z_input + (Q*A + (dot(D, z_dir) * cos(cos_sin_arg_input)));

			double cos_sin_arg_normal = (dot(D, m_pWaveVertices[INDEX].Position) * W) + (phi * m_time);
			m_pWaveVertices[INDEX].Normal.x = - (dot(D, x_dir) * W * A * cos(cos_sin_arg_normal));
			m_pWaveVertices[INDEX].Normal.y = 1 - (Q * W * A * sin(cos_sin_arg_normal));
			m_pWaveVertices[INDEX].Normal.z = - (dot(D, z_dir) * W * A * cos(cos_sin_arg_normal));
		}
	}
	return m_pWaveVertices;
}
