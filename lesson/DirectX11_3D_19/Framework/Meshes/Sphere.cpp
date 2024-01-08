#include "Framework.h"
#include "Sphere.h"

void Sphere::Create()
{
	// north pole
	vertices.push_back(MeshVertex(0, radius, 0, 0, 0, 0, 1, 0));

	float verticalStep = Math::PI / stackStep;  // �ѹ��� �������� ����
	float horizontalStep = Math::PI * 2 / sliceStep;  // ȸ������ �ѹ��� �̵��ϴ� ����

	for (uint i = 1; i <= stackStep - 1; i++)  // north pole ����
	{
		// ���� : latitude
		float latitude = i * verticalStep;

		for (uint k = 0; k <= sliceStep; k++)
		{
			// �浵 : longtitude
			float longitude = k * horizontalStep;

			Vector3 position = Vector3
			(
				(radius * sinf(latitude) * cosf(longitude)),
				(radius * cosf(latitude)),
				(radius * sinf(latitude) * sinf(longitude))
			);

			Vector3 normal;
			D3DXVec3Normalize(&normal, &position);

			Vector2 uv = Vector2(longitude / (Math::PI * 2), latitude / Math::PI);

			vertices.push_back(MeshVertex(position.x, position.y, position.z, uv.x, uv.y, normal.x, normal.y, normal.z));
		}
	}

	// south pole
	vertices.push_back(MeshVertex(0, -radius, 0, 0, 0, 0, -1, 0));

	// north pole
	for (uint i = 1; i <= sliceStep; i++)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	uint baseIndex = 1;
	uint ringVertexCount = sliceStep + 1;  // �� �������� ������.

	for (uint i = 0; i < stackStep - 2; i++)
	{
		for (uint j = 0; j < sliceStep; j++)
		{
			indices.push_back(baseIndex + i * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	uint southPoleIndex = vertices.size() - 1;  // ���� �������� ������ ��
	baseIndex = southPoleIndex - ringVertexCount;  // ������ �������� �ε��� ���
	for (uint i = 0; i < sliceStep; i++)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}
}
