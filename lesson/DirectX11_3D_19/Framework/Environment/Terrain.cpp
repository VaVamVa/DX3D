#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Shader* shader, wstring heightFile)
	:shader(shader)
{
	heightMap = new Texture(heightFile);

	/*
	height Map은 흑백이기 때문에
	한개의 색 값만 가져오면 나머지 색상 빛 속성들도 알 수 있다.
	*/
	vector<Color> heights;
	heightMap->ReadPixel(DXGI_FORMAT_R8G8B8A8_UNORM, &heights);

	width = heightMap->GetWidth();		// 가로 점의 갯수
	height = heightMap->GetHeight();	// 세로 점의 갯수

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
			// 높낮이 : 흰색(1) -> 검은색(0) 사이의 값이 나온다.
			vertices[index].Position.y = heights[pixel].r * 255.0f * 0.3f;  // 지형차를 좀 줄이기 위한 나누기.
			vertices[index].Position.z = (float)z;
		}
	}

	/*
	1. 삼각형 폴리곤에서 양 옆의 점을 보기에 나누기 3
	2. 처음의 사각형의 Polygon에서부터 시작
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
		// 정사각형을 이루는 polygon의 인접한 두 vertex로 향하는 두 벡터를 내적하면 법선벡터가 나온다.
		D3DXVec3Cross(&normal, &targetToAdjacentOne, &targetToAdjacentTwo);
		/*
		한 면에 대한 인접 vertex들 뿐 아니라,
		다른 인접한 vertex들에 대해서도 영향을 받기에,
		더해줌으로서 그 영향을 표기한다.
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

float Terrain::GetHeight(Vector3 position)  // 캐릭터의 위치
{
	// float->int 정수만 남기면 해당 tile의 시작점만 남음
	uint x = (uint)position.x;
	uint z = (uint)position.z;

	if (x < 0 || x > width) return FLT_MIN;  // tile Map을 벗어남
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
	// tile 사이즈가 1이기 때문에 가능한 식이다.
	if (ddx + ddz <= 1.0f)
	{
		/*
		1. x축에 사영시키기 : v[0] -> v[2] vector * ddx (결과 = 비율 값)
		2. z에 대해서도 똑같이.
		3. + v[0] : v[0] 위치에서 시작하는 toX, toZ 벡터 비율 나옴.
		4. 이 점의 y 값이 높이.

		이 연산 다시 공부하기.
		*/
		result = v[0] + (v[2] - v[0]) * ddx + (v[1] - v[0]) * ddz;
	}
	else
	{
		// 위와 동일하나, 한 사각형 내에 반대편 polygon에서 작업중
		ddx = 1.0f - ddx;
		ddz = 1.0f - ddz;

		result = v[3] + (v[1] - v[3]) * ddx + (v[2] - v[3]) * ddz;
	}

	return result.y;
}

float Terrain::GetVerticalRaycast(Vector3 position)
{
	// float->int 정수만 남기면 해당 tile의 시작점만 남음
	uint x = (uint)position.x;
	uint z = (uint)position.z;

	if (x < 0 || x > width) return FLT_MIN;  // tile Map을 벗어남
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

	// 임의의 ray 높이 좌표 (이전에 타일맵 비율 알아야함.)  //46줄
	Vector3 start = { position.x, 255.0f * 0.4f, position.z };  // 추후 변수로 빼자
	Vector3 direction = { 0, -1, 0 };  // ray 방향 (아래로)

	float u, v, distance;  // 값 받는 변수
	Vector3 result = { -1, FLT_MIN, -1 };  // 만약 못받는다면 그대로 return될 값.

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
