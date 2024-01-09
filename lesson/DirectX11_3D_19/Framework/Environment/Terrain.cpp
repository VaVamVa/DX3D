#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Shader* shader, wstring heightFile)
	:shader(shader)
{
	heightMap = new Texture(heightFile);

	/*
	height Map�� ����̱� ������
	�Ѱ��� �� ���� �������� ������ ���� �� �Ӽ��鵵 �� �� �ִ�.
	*/
	vector<Color> heights;
	heightMap->ReadPixel(DXGI_FORMAT_R8G8B8A8_UNORM, &heights);

	width = heightMap->GetWidth();		// ���� ���� ����
	height = heightMap->GetHeight();	// ���� ���� ����

	indices.assign((width - 1) * (height - 1) * 6, uint());
	uint index = 0;
	for (uint y = 0; y < height - 1; y++)
	{
		for (uint x = 0; x < width - 1; x++)
		{
			indices[index + 0] = width * y + x;
			indices[index + 1] = width * (y + 1) + x;
			indices[index + 2] = width * y + x + 1;
			indices[index + 3] = width * y + x + 1;
			indices[index + 4] = width * (y + 1) + x;
			indices[index + 5] = width * (y + 1) + x + 1;

			index += 6;
		}
	}

	vertices.assign(width * height, TerrainVertex());
	for (uint z = 0; z < height; z++)
	{
		for (uint x = 0; x < width; x++)
		{
			uint index = width * z + x;
			uint pixel = width * (height - 1 - z) + x;

			vertices[index].Position.x = (float)x;
			// ������ : ���(1) -> ������(0) ������ ���� ���´�.
			vertices[index].Position.y = heights[pixel].r * 255.0f * 0.3f;  // �������� �� ���̱� ���� ������.
			vertices[index].Position.z = (float)z;
		}
	}

	/*
	1. �ﰢ�� �����￡�� �� ���� ���� ���⿡ ������ 3
	2. ó���� �簢���� Polygon�������� ����
	*/
	for (uint i = 0; i < indices.size() / 3; i++)
	{
		uint indexTarget = indices[i * 3 + 0];
		uint adjacentIndexOne = indices[i * 3 + 1];
		uint adjacentIndexTwo = indices[i * 3 + 2];

		TerrainVertex vTarget = vertices[indexTarget];
		TerrainVertex vAdjacentOne = vertices[adjacentIndexOne];
		TerrainVertex vAdjacentTwo = vertices[adjacentIndexTwo];

		Vector3 targetToAdjacentOne = vAdjacentOne.Position - vTarget.Position;
		Vector3 targetToAdjacentTwo = vAdjacentTwo.Position - vTarget.Position;
		
		Vector3 normal;
		// ���簢���� �̷�� polygon�� ������ �� vertex�� ���ϴ� �� ���͸� �����ϸ� �������Ͱ� ���´�.
		D3DXVec3Cross(&normal, &targetToAdjacentOne, &targetToAdjacentTwo);
		/*
		�� �鿡 ���� ���� vertex�� �� �ƴ϶�,
		�ٸ� ������ vertex�鿡 ���ؼ��� ������ �ޱ⿡,
		���������μ� �� ������ ǥ���Ѵ�.
		*/
		vertices[indexTarget].Normal += normal;
		vertices[adjacentIndexOne].Normal += normal;
		vertices[adjacentIndexTwo].Normal += normal;
	}

	for (uint i = 0; i < vertices.size(); i++)
		D3DXVec3Normalize(&vertices[i].Normal, &vertices[i].Normal);

	vb = new VertexBuffer(vertices);
	ib = new IndexBuffer(indices);
}

Terrain::~Terrain()
{
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);

	SAFE_DELETE(heightMap);
}

void Terrain::Update()
{
	static Vector3 lightDirection = Vector3(0, -1, 0);
	ImGui::SliderFloat3("Light Direction", lightDirection, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(lightDirection);

	Matrix world;
	D3DXMatrixIdentity(&world);

	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(VIEW);
	shader->AsMatrix("Projection")->SetMatrix(PROJECTION);
}

void Terrain::Render()
{
	vb->SetIA();
	ib->SetIA();

	TRIANGLE_LIST;

	shader->DrawIndexed(0, pass, indices.size());
}

float Terrain::GetHeight(Vector3 position)  // ĳ������ ��ġ
{
	// float->int ������ ����� �ش� tile�� �������� ����
	uint x = (uint)position.x;
	uint z = (uint)position.z;

	if (x < 0 || x > width) return FLT_MIN;  // tile Map�� ���
	if (z < 0 || z > height) return FLT_MIN;

	uint index[4];
	index[0] = width * z + x;
	index[1] = width * (z + 1) + x;
	index[2] = width * z + x + 1;
	index[3] = width * (z + 1) + x + 1;

	Vector3 v[4];
	for (int i = 0; i < 4; i++)
	{
		v[i] = vertices[index[i]].Position;
	}

	float ddx = (position.x - v[0].x);
	float ddz = (position.z - v[0].z);

	Vector3 result;
	// tile ����� 1�̱� ������ ������ ���̴�.
	if (ddx + ddz <= 1.0f)
	{
		/*
		1. x�࿡ �翵��Ű�� : v[0] -> v[2] vector * ddx (��� = ���� ��)
		2. z�� ���ؼ��� �Ȱ���.
		3. + v[0] : v[0] ��ġ���� �����ϴ� toX, toZ ���� ���� ����.
		4. �� ���� y ���� ����.

		�� ���� �ٽ� �����ϱ�.
		*/
		result = v[0] + (v[2] - v[0]) * ddx + (v[1] - v[0]) * ddz;
	}
	else
	{
		// ���� �����ϳ�, �� �簢�� ���� �ݴ��� polygon���� �۾���
		ddx = 1.0f - ddx;
		ddz = 1.0f - ddz;

		result = v[3] + (v[1] - v[3]) * ddx + (v[2] - v[3]) * ddz;
	}

	return result.y;
}

float Terrain::GetVerticalRaycast(Vector3 position)
{
	// float->int ������ ����� �ش� tile�� �������� ����
	uint x = (uint)position.x;
	uint z = (uint)position.z;

	if (x < 0 || x > width) return FLT_MIN;  // tile Map�� ���
	if (z < 0 || z > height) return FLT_MIN;

	uint index[4];
	index[0] = width * z + x;
	index[1] = width * (z + 1) + x;
	index[2] = width * z + x + 1;
	index[3] = width * (z + 1) + x + 1;

	Vector3 p[4];
	for (int i = 0; i < 4; i++)
	{
		p[i] = vertices[index[i]].Position;
	}

	// ������ ray ���� ��ǥ (������ Ÿ�ϸ� ���� �˾ƾ���.)  //46��
	Vector3 start = { position.x, 255.0f * 0.4f, position.z };  // ���� ������ ����
	Vector3 direction = { 0, -1, 0 };  // ray ���� (�Ʒ���)

	float u, v, distance;  // �� �޴� ����
	Vector3 result = { -1, FLT_MIN, -1 };  // ���� ���޴´ٸ� �״�� return�� ��.

	if (D3DXIntersectTri(&p[0], &p[1], &p[2], &start, &direction, &u, &v, &distance))
	{
		result = p[0] + (p[2] - p[0]) * u + (p[1] - p[0]) * v;
	}
	if (D3DXIntersectTri(&p[3], &p[1], &p[2], &start, &direction, &u, &v, &distance))
	{
		result = p[3] + (p[1] - p[3]) * u + (p[2] - p[3]) * v;
	}

	return result.y;
}
