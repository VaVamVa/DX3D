#include "Framework.h"
#include "Cylinder.h"

void Cylinder::Create()
{
	float verticalStep = height / (float)stackCount;
	float radiusStep = (topRadius - bottomRadius) / (float)stackCount;  // ����

	uint ringCount = stackCount + 1;

	for (uint i = 0; i < ringCount; i++)
	{
		float y = -0.5f * height + i * verticalStep;	// (�ʱⰪ)�߾Ӻ��� �� �Ʒ�������� ����
		float r = bottomRadius + i * radiusStep;		// �� �Ʒ������ ������ ������

		float horizontalStep = Math::PI * 2.0f / (float)sliceCount;

		for (uint j = 0; j <= sliceCount; j++)
		{
			float x = cosf(j * horizontalStep);
			float z = sinf(j * horizontalStep);

			MeshVertex vertex;
			vertex.Position = Vector3(r * x, y, r * z);

			vertex.Uv = Vector2((float)j / (float)sliceCount, 1.0f - (float)i / float(stackCount));

			Vector3 tangent = Vector3(-z, 0.0f, x);
			float dr = bottomRadius - topRadius;
			Vector3 biTangent = Vector3(dr * x, -height, dr * z);

			D3DXVec3Cross(&vertex.Normal, &tangent, &biTangent);
			D3DXVec3Normalize(&vertex.Normal, &vertex.Normal);

			vertices.push_back(vertex);
		}
	}

	uint ringVertexCount = sliceCount + 1;
	for (uint y = 0; y < stackCount; y++)
	{
		for (uint x = 0; x < sliceCount; x++)
		{
			indices.push_back(y * ringVertexCount + x);
			indices.push_back((y + 1) * ringVertexCount + x);
			indices.push_back((y + 1) * ringVertexCount + x + 1);

			indices.push_back(y * ringVertexCount + x);
			indices.push_back((y + 1) * ringVertexCount + x + 1);
			indices.push_back(y * ringVertexCount + x + 1);
		}
	}

	BuildTopCap();
	BuildBottomCap();
}

void Cylinder::BuildTopCap()
{
	float y = 0.5f * height;
	float horizontalStep = Math::PI * 2.0f / (float)sliceCount;

	for (uint i = 0; i <= sliceCount; i++)
	{
		float x = topRadius * cosf(i * horizontalStep);
		float z = topRadius * sinf(i * horizontalStep);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertices.push_back(MeshVertex(x, y, z, u, v, 0, 1, 0));
	}
	vertices.push_back(MeshVertex(0, y, 0, 0.5f, 0.5f, 0, 1, 0));	// �� �߽�

	uint baseIndex = vertices.size() - sliceCount - 2;
	uint centerIndex = vertices.size() - 1;

	for (uint i = 0; i < sliceCount; i++)
	{
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i + 1);
		indices.push_back(baseIndex + i);
	}
}

void Cylinder::BuildBottomCap()
{
	float y = -0.5f * height;
	float horizontalStep = Math::PI * 2.0f / (float)sliceCount;

	for (uint i = 0; i <= sliceCount; i++)
	{
		float x = bottomRadius * cosf(i * horizontalStep);
		float z = bottomRadius * sinf(i * horizontalStep);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertices.push_back(MeshVertex(x, y, z, u, v, 0, -1, 0));
	}
	vertices.push_back(MeshVertex(0, y, 0, 0.5f, 0.5f, 0, -1, 0));	// �� �߽�

	uint baseIndex = vertices.size() - sliceCount - 2;
	uint centerIndex = vertices.size() - 1;

	for (uint i = 0; i < sliceCount; i++)
	{
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}
}
