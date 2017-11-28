#pragma once
union LookAtMat4x4
{
	float m_base[16];
	float m_base4x4[4][4];
};

struct Camera {
	Camera()
	{

	}

	~Camera()
	{
	
	}

	void CalculateLookAt(float *values)
	{
		float x, y, z, lx, ly, lz, ux, uy, uz;
		x = values[0];
		y = values[1];
		z = values[2];
		lx = values[3];
		ly = values[4];
		lz = values[5];
		ux = uz = 0;
		uy = 1.f;

		float rx, ry, rz;
		rx = ly * uz - lz * uy;
		ry = lz * ux - lx * uz;
		rz = lx * uy - ly * uz;

		ux = ry * lz - rz * ly;
		uy = rz * ux - rx * uz;
		uz = rx * ly - ry * ly;



	}

	LookAtMat4x4 m_lookAtMatrix;
};