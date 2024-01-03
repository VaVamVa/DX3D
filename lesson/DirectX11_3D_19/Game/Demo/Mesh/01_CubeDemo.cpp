#include "stdafx.h"
#include "01_CubeDemo.h"

void CubeDemo::Initialize()
{
	shader = new Shader(L"06_Cube.fx");

	float width = 0.5f, height = 0.5f, depth = 0.5f;

	// 4 * 6¸éÃ¼
	vertices.assign(24, Vertex());

	// Front
	vertices[0].Position = Vector3(-width, -height, -depth);
	vertices[1].Position = Vector3(-width, +height, -depth);
	vertices[2].Position = Vector3(+width, +height, -depth);
	vertices[3].Position = Vector3(+width, -height, -depth);

	// Back
	vertices[4].Position = Vector3(-width, -height, +depth);
	vertices[5].Position = Vector3(+width, -height, +depth);
	vertices[6].Position = Vector3(+width, +height, +depth);
	vertices[7].Position = Vector3(-width, +height, +depth);

	// Right
	vertices[8].Position = Vector3(+width, -height, -depth);
	vertices[9].Position = Vector3(+width, +height, -depth);
	vertices[10].Position = Vector3(+width, +height, +depth);
	vertices[11].Position = Vector3(+width, -height, +depth);

	// Left
	vertices[12].Position = Vector3(-width, -height, +depth);
	vertices[13].Position = Vector3(-width, +height, +depth);
	vertices[14].Position = Vector3(-width, +height, -depth);
	vertices[15].Position = Vector3(-width, -height, -depth);

	// Up
	vertices[16].Position = Vector3(-width, +height, -depth);
	vertices[17].Position = Vector3(-width, +height, +depth);
	vertices[18].Position = Vector3(+width, +height, +depth);
	vertices[19].Position = Vector3(+width, +height, -depth);

	// Down
	vertices[20].Position = Vector3(-width, -height, +depth);
	vertices[21].Position = Vector3(-width, -height, -depth);
	vertices[22].Position = Vector3(+width, -height, -depth);
	vertices[23].Position = Vector3(+width, -height, +depth);

	vb = new VertexBuffer(vertices);

	indices =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	ib = new IndexBuffer(indices);

	D3DXMatrixIdentity(&world);
}

void CubeDemo::Destroy()
{
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void CubeDemo::Update()
{
}

void CubeDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(VIEW);
	shader->AsMatrix("Projection")->SetMatrix(PROJECTION);
	shader->AsVector("Color")->SetFloatVector(color);

	vb->SetIA();
	ib->SetIA();
	TRIANGLE_LIST;

	shader->DrawIndexed(0, 1, indices.size());
}
