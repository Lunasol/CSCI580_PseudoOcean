#pragma once

// General Includes
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "./PreprocessorDefinitions.h"
#include <complex>

#define INDEX i * j + j

struct Float3
{
	float x, y, z;
};

struct WaveVertex
{
	Float3 position, normal;
};

struct WaveGenVertex
{
	WaveVertex waveVertex;
	Float3 a, b, c; // htilde0
	Float3 _a, _b, _c; // htilde0mk conjugate
	Float3 ox, oy, oz; // original position
};

struct Complex
{
	float r, i;
};

struct ComplexVectorNormal
{
	Complex h;
	Float3 D, n;
};

class WaveGenerator
{
	Float3* m_pGridVertices;
	WaveVertex* m_pWaveVertices;
	double m_time;
	double GetDeltaTime();

	double dot(Float3 A, Float3 B)
	{
		return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
	}

	int xRes = -1;
	int zRes = -1;

	// Wave properties
	float g = 9.8f;
	float pi = 3.14159265358979323846f;
	float Q = 0.5f;
	Float3 D = {0.9f, .0f, 0.2f};
	float L = 100.141593f;
	float A = 0.905f;
	float W = 10.28f;
	float S = 1.f;
	float phi = 5;




public:
	WaveGenerator();
	~WaveGenerator();

	void GenerateGrid(int vertexResolutionX, int vertexResolutionZ, float sizeX, float sizeZ);
	const WaveVertex* GetWave() const;

	// New wave
	const WaveVertex* GetWaves2() const;
};
