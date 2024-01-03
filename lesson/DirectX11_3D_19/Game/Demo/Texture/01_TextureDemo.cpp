#include "stdafx.h"
#include "01_TextureDemo.h"

void TextureDemo::Initialize()
{
	CAMERA->SetPosition(0, 0, -10.0f);

	shader = new Shader(L"04_Texture.fx");

	vertices.assign(4, VertexTexture());
	vb.resize(4);


	/*
	* �ǽ� : ����� �κ� ��� ä�����°�.
	*/
	// 1. ���� �� �׸�
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // ����
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // �»�
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // ���
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // ����

	// UV : Texture���� ����ϴ� "����" ��ǥ�� (�»�� 0,0 / ���ϴ� 1,1)
	vertices[0].Uv = Vector2(0, 2.0f); // ����
	vertices[1].Uv = Vector2(0, 0); // �»�
	vertices[2].Uv = Vector2(2.0f, 0); // ���
	vertices[3].Uv = Vector2(2.0f, 2.0f); // ����

	vb[0] = new VertexBuffer(vertices);

	// 2. ������ �� �׸�
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // ����
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // �»�
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // ���
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // ����

	vertices[0].Uv = Vector2(-1.0f, 2.0f); // ����
	vertices[1].Uv = Vector2(-1.0f, 0); // �»�
	vertices[2].Uv = Vector2(1.0f, 0); // ���
	vertices[3].Uv = Vector2(1.0f, 2.0f); // ����

	vb[1] = new VertexBuffer(vertices);

	// 3. ���� �Ʒ� �׸�
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // ����
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // �»�
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // ���
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // ����

	vertices[0].Uv = Vector2(0, 1.0f); // ����
	vertices[1].Uv = Vector2(0, -1.0f); // �»�
	vertices[2].Uv = Vector2(2.0f, -1.0f); // ���
	vertices[3].Uv = Vector2(2.0f, 1.0f); // ����

	vb[2] = new VertexBuffer(vertices);

	// 4. ���� �Ʒ� �׸�
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);  // ����
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);  // �»�
	vertices[2].Position = Vector3(0.5f, 0.5f, 0.0f);  // ���
	vertices[3].Position = Vector3(0.5f, -0.5f, 0.0f);  // ����

	vertices[0].Uv = Vector2(-1.0f, 1.0f); // ����
	vertices[1].Uv = Vector2(-1.0f, -1.0f); // �»�
	vertices[2].Uv = Vector2(1.0f, -1.0f); // ���
	vertices[3].Uv = Vector2(1.0f, 1.0f); // ����

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
