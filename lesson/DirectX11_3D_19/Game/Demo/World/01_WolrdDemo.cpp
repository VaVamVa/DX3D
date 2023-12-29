#include "stdafx.h"
#include "01_WolrdDemo.h"

void WorldDemo::Initialize()
{
	shader = new Shader(L"03_World.fx");

	vertices.assign(6, Vertex());

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);

	vertices[3].Position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[4].Position = Vector3(0.5f, -0.5f, 0.0f);
	vertices[5].Position = Vector3(-0.5f, -0.5f, 0.0f);

	vb = new VertexBuffer(vertices);

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&world2);
	
}

void WorldDemo::Destroy()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
	
}

void WorldDemo::Update()
{
	if (Keyboard::Get()->Press('W'))
	{
		world._42 += 3.0f * Time::Delta();
	}
	if (Keyboard::Get()->Press('S'))
	{
		world._42 -= 3.0f * Time::Delta();
	}
	if (Keyboard::Get()->Press('D'))
	{
		world._41 += 3.0f * Time::Delta();
	}
	if (Keyboard::Get()->Press('A'))
	{
		world._41 -= 3.0f * Time::Delta();
	}

	if (Keyboard::Get()->Press(VK_UP))
	{
		world._22 += 3.0f * Time::Delta();
	}
	if (Keyboard::Get()->Press(VK_DOWN))
	{
		world._22 -= 3.0f * Time::Delta();
	}
	if (Keyboard::Get()->Press(VK_RIGHT))
	{
		world._11 += 3.0f * Time::Delta();
	}
	if (Keyboard::Get()->Press(VK_LEFT))
	{
		world._11 -= 3.0f * Time::Delta();
	}

}

void WorldDemo::Render()
{
	// AsMatrix -> 쉐이더의 "string"에 접근해서 무언갈 할거야.
	// SetMatrix -> 뒤의 행렬을 Shader에 적용시켜 줄거야.
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->GetProjectionMatrix());

	vb->SetIA();
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 1, vertices.size());

	shader->AsMatrix("World")->SetMatrix(world2);

	shader->Draw(0, 0, vertices.size());
}
