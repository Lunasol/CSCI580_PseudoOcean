#include "./WaveGenerator.h"
#include "./VertexBufferGPU.h"
#include "./VertexStructs.h"

#define NUMINDICES(x, y) (x - 1) * (y - 1) * 6
// (x - 1) * (y - 1) * 2

/// DEBUGGING
struct testVert {
	FLOAT pos[3];
	FLOAT color[4];
	//FLOAT norm[3];
};
/// DEBUGGING END

// Index Buffer Struct
struct QuadIndex
{
	unsigned long quad[6];
};

VertexBufferGPU::VertexBufferGPU() 
{
	m_pVBuffer = NULL;
	m_pIBuffer = NULL;
}

VertexBufferGPU::~VertexBufferGPU() 
{
	
}

void VertexBufferGPU::InitBuffer(int bufferLayout, int vertexCount, int xIndexCount, int yIndexCount)
{
	WaveVertex *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vBufferDesc, iBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	int numIndices = NUMINDICES(xIndexCount, yIndexCount);
	int indexCount = 0;
	QuadIndex curIndex;
	HRESULT result;

	if (vertexCount > 0)
	{
		vertices = EALLOC(WaveVertex, vertexCount);
	}
	

	switch (bufferLayout)
	{
		case VertexFormatLayout_CPUTerrain_B0_P0f3_TC0f2_N0f3_B1_I0i3:
		{
			// TODO
			if (xIndexCount * yIndexCount > 0)
			{
				indices = EALLOC(unsigned long, numIndices);
			}
			m_numVerts = vertexCount;
			m_numIndices = numIndices;
			for (int i = 0; i < yIndexCount - 1; i++)
			{
				for (int j = 0; j < xIndexCount - 1; j++)
				{
					// Do per quad
					curIndex = {
						(unsigned long)(i * xIndexCount + j), // Triangle 1
						(unsigned long)((i + 1) * xIndexCount + j),
						(unsigned long)(i * xIndexCount + j + 1),
						(unsigned long)((i + 1) * xIndexCount + j), // Triangle 2
						(unsigned long)((i + 1) * xIndexCount + 1 + j),
						(unsigned long)(i * xIndexCount + j + 1)
					};

					for (int k = 0; k < 6; k++)
					{
						indices[indexCount++] = curIndex.quad[k];
					}
				}
			}
			assert(indexCount == numIndices, "We didn't come out with the same amount of indices");

			vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vBufferDesc.ByteWidth = sizeof(WaveVertex) * m_numVerts;
			vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vBufferDesc.CPUAccessFlags = 0;
			vBufferDesc.MiscFlags = 0;
			vBufferDesc.StructureByteStride = 0;

			//vertexData.pSysMem = ;// passed in vertices
			//vertexData.SysMemPitch = 0;
			//vertexData.SysMemSlicePitch = 0;

			result = ID3D11Renderer::Instance()->getDevicePtr()->CreateBuffer(&vBufferDesc, &vertexData, &m_pVBuffer);
			if (FAILED(result))
				exit(EXIT_FAILURE);

			iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			iBufferDesc.ByteWidth = sizeof(unsigned long) * m_numIndices;
			iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			iBufferDesc.CPUAccessFlags = 0;
			iBufferDesc.MiscFlags = 0;
			iBufferDesc.StructureByteStride = 0;

			//indexData.pSysMem = ;// passed in vertices
			//indexData.SysMemPitch = 0;
			//indexData.SysMemSlicePitch = 0;

			result = ID3D11Renderer::Instance()->getDevicePtr()->CreateBuffer(&iBufferDesc, &indexData, &m_pIBuffer);
			if (FAILED(result))
				exit(EXIT_FAILURE);

			break;
		}
	
	}
	if (vertices)
		free(vertices);
	if (indices)
		free(indices);
}