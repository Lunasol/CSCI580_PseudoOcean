#include "./WaveGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#undef _USE_MATH_DEFINES

#define INDEX i * xRes + j
#define H_INDEX i * (xRes - 1) + j

WaveGenerator::WaveGenerator()
{
	m_time = time(nullptr);
}

WaveGenerator::~WaveGenerator()
{
	if (m_pGridVertices)
		delete[] m_pGridVertices;
	if (m_pWaveVertices)
		delete[] m_pWaveVertices;

	m_pGridVertices = nullptr;
	m_pWaveVertices = nullptr;

	// Free fft related variables
	if (fft_data)
		delete[] fft_data;
	if (h_tilde)
		delete[] h_tilde;
	if (h_tilde_slopex)
		delete[] h_tilde_slopex;
	if (h_tilde_slopez)
		delete[] h_tilde_slopez;
	if (h_tilde_dx)
		delete[] h_tilde_dx;
	if (h_tilde_dz)
		delete[] h_tilde_dz;

	delete fft_x;
	delete fft_z;

	fft_data = nullptr;
	h_tilde = nullptr;
	h_tilde_slopex = nullptr;
	h_tilde_slopez = nullptr;
	h_tilde_dx = nullptr;
	h_tilde_dz = nullptr;

	FFT* fft_x = nullptr;
	FFT* fft_z = nullptr;
}

void WaveGenerator::GenerateGrid(int vertexResolutionX, int vertexResolutionZ, float sizeX, float sizeZ)
{
	if (m_pGridVertices)
		free(m_pGridVertices);

	xRes = vertexResolutionX;
	zRes = vertexResolutionZ;
	int xResMinus1 = xRes - 1;
	int zResMinus1 = zRes - 1;

	// FFT data initialization
	fft_x = new FFT(xResMinus1);
	fft_z = new FFT(zResMinus1);
	h_tilde = new std::complex<float>[xResMinus1 * zResMinus1];
	h_tilde_slopex = new std::complex<float>[xResMinus1 * zResMinus1];
	h_tilde_slopez = new std::complex<float>[xResMinus1 * zResMinus1];
	h_tilde_dx = new std::complex<float>[xResMinus1 * zResMinus1];
	h_tilde_dz = new std::complex<float>[xResMinus1 * zResMinus1];
	fft_data = new FFTData[xRes * zRes];

	m_pGridVertices = new Float3[xRes * zRes];
	m_pWaveVertices = new WaveVertex[xRes * zRes];

	m_time = time(nullptr);

	float xOffset = sizeX / static_cast<float>(vertexResolutionX);
	float zOffset = sizeZ / static_cast<float>(vertexResolutionZ);

	for (int i = 0; i < vertexResolutionZ; i++)
	{
		float xValue = 0.f;
		float zValue = (zOffset * i);
		for (int j = 0; j < vertexResolutionX; j++)
		{
			m_pGridVertices[INDEX].x = m_pWaveVertices[INDEX].position.x = xValue += xOffset;
			m_pGridVertices[INDEX].y = m_pWaveVertices[INDEX].position.y = 0.f;
			m_pGridVertices[INDEX].z = m_pWaveVertices[INDEX].position.z = zValue;
		}
	}
}

double WaveGenerator::GetTime() const
{
	return time(nullptr) - m_time;
}

const WaveVertex* WaveGenerator::GetWave()
{
	if (!m_pGridVertices || !m_pWaveVertices)
		return nullptr;

	double t = GetTime();

	for (int i = 0; i < xRes; ++i)
	{
		for (int j = 0; j < zRes; ++j)
		{
			float x_input = m_pGridVertices[INDEX].x;
			float z_input = m_pGridVertices[INDEX].z;

			Float3 x_dir = {x_input, 0, 0};
			Float3 z_dir = {0, 0, z_input};
			double cos_sin_arg_input = (dot(D, m_pGridVertices[INDEX]) * W) + (phi * t);

			m_pWaveVertices[INDEX].position.x = x_input + (Q * A + (dot(D, x_dir) * cos(cos_sin_arg_input)));
			m_pWaveVertices[INDEX].position.y = A * sin(cos_sin_arg_input);
			m_pWaveVertices[INDEX].position.z = z_input + (Q * A + (dot(D, z_dir) * cos(cos_sin_arg_input)));

			double cos_sin_arg_normal = (dot(D, m_pWaveVertices[INDEX].position) * W) + (phi * t);
			m_pWaveVertices[INDEX].normal.x = - (dot(D, x_dir) * W * A * cos(cos_sin_arg_normal));
			m_pWaveVertices[INDEX].normal.y = 1 - (Q * W * A * sin(cos_sin_arg_normal));
			m_pWaveVertices[INDEX].normal.z = - (dot(D, z_dir) * W * A * cos(cos_sin_arg_normal));
		}
	}
	return m_pWaveVertices;
}

const WaveVertex* WaveGenerator::GetWaveFFT()
{
	if (!m_pGridVertices || !m_pWaveVertices)
		return nullptr;

	double t = GetTime();

	float lambda = -1.0f;

	int zResMinus1 = zRes - 1;
	int xResMinus1 = xRes - 1;

	for (int i = 0; i < zResMinus1; ++i)
	{
		float kz = M_PI * (2 * i - zResMinus1) / L;
		for (int j = 0; j < xResMinus1; ++j)
		{
			float kx = M_PI * (2 * j - xResMinus1) / L;
			float len = sqrt(kx * kx + kz * kz);

			h_tilde[H_INDEX] = hTilde(t, j, i);
			h_tilde_slopex[H_INDEX] = h_tilde[H_INDEX] * std::complex<float>(0, kx);
			h_tilde_slopez[H_INDEX] = h_tilde[H_INDEX] * std::complex<float>(0, kz);
			if (len < 0.000001f)
			{
				h_tilde_dx[H_INDEX] = std::complex<float>(0.0f, 0.0f);
				h_tilde_dz[H_INDEX] = std::complex<float>(0.0f, 0.0f);
			}
			else
			{
				h_tilde_dx[H_INDEX] = h_tilde[H_INDEX] * std::complex<float>(0, -kx / len);
				h_tilde_dz[H_INDEX] = h_tilde[H_INDEX] * std::complex<float>(0, -kz / len);
			}
		}
	}

	for (int i = 0; i < zResMinus1; ++i)
	{
		fft_z->fft(h_tilde, h_tilde, 1, i * zResMinus1);
		fft_z->fft(h_tilde_slopex, h_tilde_slopex, 1, i * zResMinus1);
		fft_z->fft(h_tilde_slopez, h_tilde_slopez, 1, i * zResMinus1);
		fft_z->fft(h_tilde_dx, h_tilde_dx, 1, i * zResMinus1);
		fft_z->fft(h_tilde_dz, h_tilde_dz, 1, i * zResMinus1);
	}

	for (int j = 0; j < xResMinus1; ++j)
	{
		fft_x->fft(h_tilde, h_tilde, xResMinus1, j);
		fft_x->fft(h_tilde_slopex, h_tilde_slopex, xResMinus1, j);
		fft_x->fft(h_tilde_slopez, h_tilde_slopez, xResMinus1, j);
		fft_x->fft(h_tilde_dx, h_tilde_dx, xResMinus1, j);
		fft_x->fft(h_tilde_dz, h_tilde_dz, xResMinus1, j);
	}

	float signs[] = {1.0f, -1.0f};
	for (int i = 0; i < zResMinus1; i++)
	{
		for (int j = 0; j < xResMinus1; j++)
		{
			int sign = signs[(j + i) & 1];

			h_tilde[H_INDEX] = complexScalarMultiply(h_tilde[H_INDEX], sign);

			// height
			m_pWaveVertices[INDEX].position.y = h_tilde[H_INDEX].real();

			// displacement
			h_tilde_dx[H_INDEX] = complexScalarMultiply(h_tilde_dx[H_INDEX], sign);
			h_tilde_dz[H_INDEX] = complexScalarMultiply(h_tilde_dz[H_INDEX], sign);
			m_pWaveVertices[INDEX].position.x = m_pGridVertices[INDEX].x + h_tilde_dx[H_INDEX].real() * lambda;
			m_pWaveVertices[INDEX].position.z = m_pGridVertices[INDEX].z + h_tilde_dz[H_INDEX].real() * lambda;

			// normal
			h_tilde_slopex[H_INDEX] = complexScalarMultiply(h_tilde_slopex[H_INDEX], sign);
			h_tilde_slopez[H_INDEX] = complexScalarMultiply(h_tilde_slopez[H_INDEX], sign);
			Float3 n = {0.0f - h_tilde_slopex[H_INDEX].real(), 1.0f, 0.0f - h_tilde_slopez[H_INDEX].real()};
			//.unit();
			m_pWaveVertices[INDEX].normal.x = n.x;
			m_pWaveVertices[INDEX].normal.y = n.y;
			m_pWaveVertices[INDEX].normal.z = n.z;

			// for tiling
			if (j == 0 && i == 0)
			{
				// xRes = Nplus1
				// xRes
				int tilingIndex = INDEX + xResMinus1 + xRes * zResMinus1;
				m_pWaveVertices[tilingIndex].position.y = h_tilde[H_INDEX].real();
				m_pWaveVertices[tilingIndex].position.x = m_pGridVertices[tilingIndex].x + h_tilde_dx[H_INDEX].real() * lambda;
				m_pWaveVertices[tilingIndex].position.z = m_pGridVertices[tilingIndex].z + h_tilde_dz[H_INDEX].real() * lambda;

				m_pWaveVertices[tilingIndex].normal.x = n.x;
				m_pWaveVertices[tilingIndex].normal.y = n.y;
				m_pWaveVertices[tilingIndex].normal.z = n.z;
			}
			if (j == 0)
			{
				int tilingIndex = INDEX + xResMinus1;
				m_pWaveVertices[tilingIndex].position.y = h_tilde[H_INDEX].real();
				m_pWaveVertices[tilingIndex].position.x = m_pGridVertices[tilingIndex].x + h_tilde_dx[H_INDEX].real() * lambda;
				m_pWaveVertices[tilingIndex].position.z = m_pGridVertices[tilingIndex].z + h_tilde_dz[H_INDEX].real() * lambda;

				m_pWaveVertices[tilingIndex].normal.x = n.x;
				m_pWaveVertices[tilingIndex].normal.y = n.y;
				m_pWaveVertices[tilingIndex].normal.z = n.z;
			}
			if (i == 0)
			{
				int tilingIndex = INDEX + xRes * zResMinus1;
				m_pWaveVertices[tilingIndex].position.y = h_tilde[H_INDEX].real();
				m_pWaveVertices[tilingIndex].position.x = m_pGridVertices[tilingIndex].x + h_tilde_dx[H_INDEX].real() * lambda;
				m_pWaveVertices[tilingIndex].position.z = m_pGridVertices[tilingIndex].z + h_tilde_dz[H_INDEX].real() * lambda;

				m_pWaveVertices[tilingIndex].normal.x = n.x;
				m_pWaveVertices[tilingIndex].normal.y = n.y;
				m_pWaveVertices[tilingIndex].normal.z = n.z;
			}
		}
	}

	return m_pWaveVertices;
}

std::complex<float> WaveGenerator::hTilde(float t, int j, int i) const
{
	std::complex<float> htilde0(fft_data[INDEX].htilde0.x, fft_data[INDEX].htilde0mk.y);
	std::complex<float> htilde0mkconj(fft_data[INDEX].htilde0mk.x, fft_data[INDEX].htilde0mk.y);

	float omegat = dispersion(j, i) * t;

	float cos_ = cos(omegat);
	float sin_ = sin(omegat);

	std::complex<float> c0(cos_, sin_);
	std::complex<float> c1(cos_, -sin_);

	return htilde0 * c0 + htilde0mkconj * c1;
}

float WaveGenerator::dispersion(int n_prime, int m_prime) const
{
	float w_0 = 2.0f * M_PI / 200.0f;
	float kx = M_PI * (2 * n_prime - xRes + 1) / L;
	float kz = M_PI * (2 * m_prime - zRes + 1) / L;
	return floor(sqrt(g * sqrt(kx * kx + kz * kz)) / w_0) * w_0;
}
