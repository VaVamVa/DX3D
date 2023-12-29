#include "stdafx.h"
#include "02_IndexBufferDemo.h"

void IndexBufferDemo::Initialize()
{
	shader = new Shader(L"03_World.fx");

	vertices.assign(4, Vertex());

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);

	vb = new VertexBuffer(vertices);

	D3DXMatrixIdentity(&world);

	indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	ib = new IndexBuffer(indices);
	
}

void IndexBufferDemo::Destroy()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void IndexBufferDemo::Update()
{
}

void IndexBufferDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->GetProjectionMatrix());

	vb->SetIA();
	ib->SetIA();
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->DrawIndexed(0, 1, indices.size());
}
