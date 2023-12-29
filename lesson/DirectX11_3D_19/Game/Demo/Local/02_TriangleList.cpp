#include "stdafx.h"
#include "02_TriangleList.h"

void TriangleList::Initialize()
{
	shader = new Shader(L"02_Triangle.fx");

	vertices.assign(6, Vertex());

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);

	vertices[3].Position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[4].Position = Vector3(0.5f, -0.5f, 0.0f);
	vertices[5].Position = Vector3(-0.5f, -0.5f, 0.0f);


	vb = new VertexBuffer(vertices);
}

void TriangleList::Destroy()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void TriangleList::Update()
{
}

void TriangleList::Render()
{
	vb->SetIA();
	// 면의 최소 단위 = 삼각형
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->Draw(0, 0, vertices.size() / 2);
	shader->Draw(0, 2, vertices.size() / 2, vertices.size() / 2);

}
