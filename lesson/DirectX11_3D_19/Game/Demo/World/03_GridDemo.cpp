#include "stdafx.h"
#include "03_GridDemo.h"

void GridDemo::Initialize()
{
	shader = new Shader(L"03_World.fx");

	uint vertexCount = (width + 1) * (height + 1);  // 4 * 4 그리드에서 점의 갯수는 각각 +1
	// 각 행 혹은 열의 사각형의 갯수 + 1가 점의 갯수
	vertices.assign(vertexCount, Vertex());

	for (uint y = 0; y <= height; y++)  // 실제 점은 ?
	{
		for (uint x = 0; x <= width; x++)
		{
			uint i = (width + 1) * y + x;  // greed 의 각 점(index)

			vertices[i].Position.x = static_cast<float>(x);
			vertices[i].Position.y = static_cast<float>(y);
			vertices[i].Position.z = 0.0f;
		}
	}

	vb = new VertexBuffer(vertices);

	uint indexCount = (width * height) * 6;
	indices.resize(indexCount);

	uint index = 0;
	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			indices[index + 0] = (width + 1) * y + x;
			indices[index + 1] = (width + 1) * (y + 1) + x; //indices[index + 0] + width
			indices[index + 2] = (width + 1) * y + x + 1; //indices[index + 0] + 1

			indices[index + 3] = (width + 1) * y + x + 1; //indices[index + 2]
			indices[index + 4] = (width + 1) * (y + 1) + x; //indices[index + 1]
			indices[index + 5] = (width + 1) * (y + 1) + x + 1; //indices[index + 1] + 1

			index += 6;  // 사각형 하나당 점 6개 == index 6개
		}
	}

	ib = new IndexBuffer(indices);

	D3DXMatrixIdentity(&world);  // scale을 1로 초기화
}

void GridDemo::Destroy()
{
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void GridDemo::Update()
{

}

void GridDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(VIEW);
	shader->AsMatrix("Projection")->SetMatrix(PROJECTION);

	vb->SetIA();
	ib->SetIA();

	TRIANGLE_LIST;

	static int pass = 0;
	ImGui::InputInt("Pass", &pass);
	pass = pass > 0 ? pass % 2 : (-1 * pass) % 2;

	shader->DrawIndexed(0, pass, indices.size());
}
