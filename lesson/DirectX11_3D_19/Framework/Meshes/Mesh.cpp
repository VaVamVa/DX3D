#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh(Shader* shader)
	:shader(shader)
{
	D3DXMatrixIdentity(&world);

	// 미리 받아오기.
	sWorld = shader->AsMatrix("World");
	sView = shader->AsMatrix("View");
	sProjection = shader->AsMatrix("Projection");

	sDiffuseMap = shader->AsSRV("DiffuseMap");
}

Mesh::~Mesh()
{
	SAFE_DELETE(diffuseMap);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void Mesh::Update()
{
}

void Mesh::Render()
{
	if (vb == nullptr || ib == nullptr)
	{
		Create();  // vertices & indices 만들기
		CreateBuffer();  // ib & vb 생성
	}
	vb->SetIA();
	ib->SetIA();

	TRIANGLE_LIST;

	sWorld->SetMatrix(world);
	sView->SetMatrix(VIEW);
	sProjection->SetMatrix(PROJECTION);

	if (diffuseMap)
		sDiffuseMap->SetResource(diffuseMap->SRV());

	shader->DrawIndexed(0, pass, indices.size());
}

void Mesh::SetShader(Shader* shader)
{
	this->shader = shader;

	sWorld = this->shader->AsMatrix("World");
	sView = this->shader->AsMatrix("View");
	sProjection = this->shader->AsMatrix("Projection");

	sDiffuseMap = this->shader->AsSRV("DiffuseMap");
}

void Mesh::SetPosition(Vector3 pos)
{
	position = pos;
	UpdateWorld();
}

void Mesh::SetPosition(float x, float y, float z)
{
	SetPosition(Vector3(x, y, z));
}

void Mesh::SetRotation(Vector3 rot)
{
	rotation = rot;
	UpdateWorld();
}

void Mesh::SetRotation(float x, float y, float z)
{
	SetRotation(Vector3(x, y, z));
}

void Mesh::SetRotationDegree(Vector3 rot)
{
	rotation = rot * Math::PI / 180.0f;
	UpdateWorld();
}

void Mesh::SetRotationDegree(float x, float y, float z)
{
	SetRotationDegree(Vector3(x, y, z));
}

void Mesh::MulRoationMatrix(Matrix mulR)
{
	Matrix S, R, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * mulR * T;
}

void Mesh::SetScale(Vector3 size)
{
	scale = size;
	UpdateWorld();
}

void Mesh::SetScale(float x, float y, float z)
{
	SetScale(Vector3(x, y, z));
}

void Mesh::SetDiffuseMap(wstring file)
{
	SAFE_DELETE(diffuseMap);
	diffuseMap = new Texture(file);
}

void Mesh::CreateBuffer()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(ib);

	vb = new VertexBuffer(vertices);
	ib = new IndexBuffer(indices);
}

void Mesh::UpdateWorld()
{
	Matrix S, R, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
}
