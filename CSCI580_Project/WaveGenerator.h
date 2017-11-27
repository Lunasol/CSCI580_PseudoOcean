#pragma once

// General Includes
#include <complex>
#include "fft.h"

struct Float3
{
	float x, y, z;
};

struct WaveVertex
{
	Float3 position, normal;
};

struct FFTData
{
	Float3 htilde0, htilde0mk;
};

inline std::complex<float> complexScalarMultiply(const std::complex<float> c, const float scalar)
{
	return std::complex<float>(c.real() * scalar, c.imag() * scalar);
}

inline double dot(Float3 A, Float3 B)
{
	return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

class WaveGenerator
{
<<<<<<< HEAD
public:
	WaveGenerator();
	~WaveGenerator();

	void GenerateGrid(int vertexResolutionX, int vertexResolutionZ, float sizeX, float sizeZ);
	const WaveVertex* GetWave();

private:
	Float3* m_pGridVertices;
	WaveVertex* m_pWaveVertices;
=======
	Float3* m_pGridVertices = nullptr;
	WaveVertex* m_pWaveVertices = nullptr;
>>>>>>> 10c56f2d2b03da484d25e061a6351955cc686c1d
	double m_time;
	double GetTime() const;

	int xRes = -1;
	int zRes = -1;

	// universal constants
	float g = 9.8f;
<<<<<<< HEAD
	float pi = 3.14159265358979323846f;
=======
>>>>>>> 10c56f2d2b03da484d25e061a6351955cc686c1d

	// Wave properties
	float Q = 0.5f;
	Float3 D = { 0.9f, .0f, 0.2f };
	float L = 100.141593f;
	float A = 0.905f;
	float W = 10.28f;
	float S = 1.f;
	float phi = 5;
<<<<<<< HEAD
=======

	// FFT variables
	FFTData* fft_data = nullptr;
	std::complex<float> *h_tilde = nullptr,
		*h_tilde_slopex = nullptr, *h_tilde_slopez = nullptr,
		*h_tilde_dx = nullptr, *h_tilde_dz = nullptr;

	FFT* fft_x = nullptr;
	FFT* fft_z = nullptr;

	// FFT functions
	std::complex<float> hTilde(float t, int n_prime, int m_prime) const;
	float dispersion(int j, int i) const;

public:
	WaveGenerator();
	~WaveGenerator();

	void GenerateGrid(int vertexResolutionX, int vertexResolutionZ, float sizeX, float sizeZ);

	const WaveVertex* GetWave();

	// New wave
	const WaveVertex* GetWaveFFT();
>>>>>>> 10c56f2d2b03da484d25e061a6351955cc686c1d
};
