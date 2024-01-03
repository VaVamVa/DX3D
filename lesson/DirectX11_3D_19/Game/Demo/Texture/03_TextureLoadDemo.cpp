#include "stdafx.h"
#include "03_TextureLoadDemo.h"

void TextureLoadDemo::Initialize()
{
	CAMERA->SetPosition(0, 0, -10.0f);

	shader = new Shader(L"04_Texture.fx");

	vertices.assign(4, VertexTexture());

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);

	vertices[0].Uv = Vector2(0, 1.0f); // 좌하
	vertices[1].Uv = Vector2(0, 0); // 좌상
	vertices[2].Uv = Vector2(1.0f, 0); // 우상
	vertices[3].Uv = Vector2(1.0f, 1.0f); // 우하

	vb = new VertexBuffer(vertices);

	indices = { 0, 1, 2, 2, 3, 0 };

	ib = new IndexBuffer(indices);

	D3DXMatrixIdentity(&world);
}

void TextureLoadDemo::Destroy()
{
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void TextureLoadDemo::Update()
{
	if (ImGui::Button("Open Image") == true)
	{
		function<void(wstring)> func =
			bind(&TextureLoadDemo::LoadTexture, this, placeholders::_1);

		GRAPHICS_DESC desc = Graphics::GetDesc();
		/*
		파일 불러오기 창 만드는 함수.
		1. 파일명
		2. 이미지 확장자
		3. 초기 이미지 파일 경로,
		4. 어떤 행동을 해줄지 정해주는 함수 포인터
		5. 불러오기 창 핸들
		*/
		Path::OpenFileDialog(L"", Path::ImageFilter, L"../_Textures/", func, desc.Handle);
	}
}

void TextureLoadDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(VIEW);
	shader->AsMatrix("Projection")->SetMatrix(PROJECTION);

	if (texture != nullptr)
		shader->AsSRV("Map")->SetResource(texture->SRV());

	vb->SetIA();
	ib->SetIA();
	TRIANGLE_LIST;

	shader->DrawIndexed(0, 0, indices.size());
}

void TextureLoadDemo::LoadTexture(wstring file)
{
	SAFE_DELETE(texture);
	texture = new Texture(file);
}
