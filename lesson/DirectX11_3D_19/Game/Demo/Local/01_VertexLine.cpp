#include "stdafx.h"
#include "01_VertexLine.h"

void VertexLine::Initialize()
{
	shader = new Shader(L"01_Vertex.fx");

	vertices.assign(2, Vertex());

	vertices[0].Position = Vector3(0, 0, 0);
	vertices[1].Position = Vector3(1, 0, 0);

	vb = new VertexBuffer();
	vb->Create(vertices);
}

void VertexLine::Destroy()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void VertexLine::Update()
{
}

void VertexLine::Render()
{
	vb->SetIA();
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->Draw(0, 0, 2);
}
