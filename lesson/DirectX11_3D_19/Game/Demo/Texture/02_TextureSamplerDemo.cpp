#include "stdafx.h"
#include "02_TextureSamplerDemo.h"

void TextureSamplerDemo::Initialize()
{
	CAMERA->SetPosition(0, 0, -10.0f);

	shader = new Shader(L"04_Texture.fx");

	D3DXMatrixIdentity(&world);

	vertices.assign(4, VertexTexture());

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);

	/* Á¤»ó±×¸²
	vertices[0].Uv = Vector2(0, 1.0f); // ÁÂÇÏ
	vertices[1].Uv = Vector2(0, 0); // ÁÂ»ó
	vertices[2].Uv = Vector2(1.0f, 0); // ¿ì»ó
	vertices[3].Uv = Vector2(1.0f, 1.0f); // ¿ìÇÏ
	*/

	vertices[0].Uv = Vector2(0, 2.0f); // ÁÂÇÏ
	vertices[1].Uv = Vector2(0, 0); // ÁÂ»ó
	vertices[2].Uv = Vector2(2.0f, 0); // ¿ì»ó
	vertices[3].Uv = Vector2(2.0f, 2.0f); // ¿ìÇÏ

	vb = new VertexBuffer(vertices);

	indices = { 0, 1, 2, 2, 3, 0 };

	ib = new IndexBuffer(indices);

	Check
	(
		D3DX11CreateShaderResourceViewFromFile
		(
			DEVICE, L"../_Textures/2024NewYear.jpg", nullptr, nullptr, &srv, nullptr
		)
	);
}

void TextureSamplerDemo::Destroy()
{
	SAFE_RELEASE(srv);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void TextureSamplerDemo::Update()
{
	static UINT filter = 0;
	ImGui::InputInt("Filter", (int*)&filter);
	filter %= 2;

	shader->AsScalar("Filter")->SetInt(filter);

	static UINT address = 0;
	ImGui::InputInt("Address", (int*)&address);
	filter %= 4;

	shader->AsScalar("Address")->SetInt(address);
}

void TextureSamplerDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(VIEW);
	shader->AsMatrix("Projection")->SetMatrix(PROJECTION);
	shader->AsSRV("Map")->SetResource(srv);

	vb->SetIA();
	ib->SetIA();
	TRIANGLE_LIST;

	static uint pass = 0;
	ImGui::InputInt("Pass", (int*)&pass);
	pass %= 3;
	shader->DrawIndexed(0, pass, indices.size());
}
