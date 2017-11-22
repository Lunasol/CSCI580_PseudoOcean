#pragma once

// General Includes
#include <stdlib.h>

#include "./PreprocessorDefinitions.h"

struct WaveVertex {
	float m_x;
	float m_y;
	float m_z;
};

struct WaveGenerator
{
	WaveGenerator();
	~WaveGenerator();

	WaveVertex *GenerateWaveList(
		int vertexResolutionX,
		int vertexResolutionZ,
		float sizeX,
		float sizeZ
	);

private:
	WaveVertex *m_pWaveVertices;
	float m_time;
};

