#include "stdafx.h"
#include "01_TextureDemo.h"

void TextureDemo::Initialize()
{
	CAMERA->SetPosition(0, 0, -10.0f);

	shader = new Shader(L"04_Texture.fx");

	vertices.assign(4, VertexTexture());
	vb.resize(4);


	/*
	* 실습 : 비워진 부분 어떻게 채워지는가.
	*/
	// 1. 왼쪽 위 그림
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // 좌하
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // 좌상
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // 우상
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // 우하

	// UV : Texture에서 사용하는 "비율" 좌표계 (좌상단 0,0 / 우하단 1,1)
	vertices[0].Uv = Vector2(0, 2.0f); // 좌하
	vertices[1].Uv = Vector2(0, 0); // 좌상
	vertices[2].Uv = Vector2(2.0f, 0); // 우상
	vertices[3].Uv = Vector2(2.0f, 2.0f); // 우하

	vb[0] = new VertexBuffer(vertices);

	// 2. 오른쪽 위 그림
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // 좌하
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // 좌상
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // 우상
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // 우하

	vertices[0].Uv = Vector2(-1.0f, 2.0f); // 좌하
	vertices[1].Uv = Vector2(-1.0f, 0); // 좌상
	vertices[2].Uv = Vector2(1.0f, 0); // 우상
	vertices[3].Uv = Vector2(1.0f, 2.0f); // 우하

	vb[1] = new VertexBuffer(vertices);

	// 3. 왼쪽 아래 그림
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // 좌하
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // 좌상
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // 우상
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // 우하

	vertices[0].Uv = Vector2(0, 1.0f); // 좌하
	vertices[1].Uv = Vector2(0, -1.0f); // 좌상
	vertices[2].Uv = Vector2(2.0f, -1.0f); // 우상
	vertices[3].Uv = Vector2(2.0f, 1.0f); // 우하

	vb[2] = new VertexBuffer(vertices);

	// 4. 왼쪽 아래 그림
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // 좌하
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // 좌상
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // 우상
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // 우하

	vertices[0].Uv = Vector2(-1.0f, 1.0f); // 좌하
	vertices[1].Uv = Vector2(-1.0f, -1.0f); // 좌상
	vertices[2].Uv = Vector2(1.0f, -1.0f); // 우상
	vertices[3].Uv = Vector2(1.0f, 1.0f); // 우하

	vb[3] = new VertexBuffer(vertices);


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

void TextureDemo::Destroy()
{
	SAFE_RELEASE(srv);
	SAFE_DELETE(ib);
	for (auto& v : vb) SAFE_DELETE(v);
	SAFE_DELETE(shader);
}

void TextureDemo::Update()
{

}

void TextureDemo::Render()
{
	D3DXMatrixIdentity(&world);

	shader->AsMatrix("World")->SetMatrix(world);

	vb[0]->SetIA();

	shader->DrawIndexed(0, 0, indices.size());

	world._41 += 1.0f;

	shader->AsMatrix("World")->SetMatrix(world);

	vb[1]->SetIA();

	shader->DrawIndexed(0, 0, indices.size());

	world._41 -= 1.0f;
	world._42 -= 1.0f;
	

	shader->AsMatrix("World")->SetMatrix(world);

	vb[2]->SetIA();

	shader->DrawIndexed(0, 0, indices.size());

	world._41 += 1.0f;

	shader->AsMatrix("World")->SetMatrix(world);

	vb[3]->SetIA();

	shader->DrawIndexed(0, 0, indices.size());


	shader->AsMatrix("View")->SetMatrix(VIEW);
	shader->AsMatrix("Projection")->SetMatrix(PROJECTION);
	shader->AsSRV("Map")->SetResource(srv);

	ib->SetIA();

	TRIANGLE_LIST;
}
