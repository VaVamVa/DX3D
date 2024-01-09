#pragma once

class Mesh
{
public:
	typedef VertexTextureNormal MeshVertex;

public:
	Mesh(Shader* shader);
	virtual ~Mesh();

	void Update();
	void Render();

public:
	void SetShader(Shader* shader);
	void SetPass(uint value) { pass = value; }

	void SetPosition(Vector3 pos);
	void SetPosition(float x, float y, float z);
	Vector3 GetPosition() { return position; }
	
	void SetRotation(Vector3 rot);
	void SetRotation(float x, float y, float z);
	Vector3 GetRotation() { return rotation; }

	void SetRotationDegree(Vector3 rot);
	void SetRotationDegree(float x, float y, float z);
	Vector3 GetRotationDegree() { return rotation * Math::PI / 180.0f; }

	void MulAxisRoation(Vector3 *pAxis, float rotationAngleSpeed);

	void SetScale(Vector3 size);
	void SetScale(float x, float y, float z);
	Vector3 GetScale() { return scale; }

	Matrix& GetWorld() { return world; }

	Vector3 GetForwardVector() { return Vector3(world._31, world._32, world._33); }
	Vector3 GetUpVector() { return Vector3(world._21, world._22, world._23); }
	Vector3 GetRigthVector() { return Vector3(world._11, world._12, world._13); }

	/*
	1. A : ȯ�汤. �ֺ����� �������� �ٲ�� ��
	2. D : ������. ��ü�� ���� ������ �� (���� ����)
	3. S : �ݻ籤. �ݼ������̳� ��ó�� �㿸�� �ݻ�Ǵ� �κ�
	4. E : ���Ɽ. �ܰ����� ǥ���ϱ� ���� ���� ��
	���� ������ ���� ����Ŵ.

	�� ���(����Ʈ ��) : �� vertex�� �������Ϳ� ���� ���⿡ �ݴ���� ������ ����(����)�� ����
	Sampler State���� Pixel�� ���� ������
	-> ���� �ݴ���⿡���� 0�� �����ϰ� �ɰ���.
	*/
	void SetDiffuseMap(wstring file);
	
protected:
	// vertex�� ���� ���� �ܿ��� ��� ���� ����. vertex setting�� ���� �����Լ���
	virtual void Create() = 0;
	void CreateBuffer();

private:
	void UpdateWorld();

protected:
	vector<MeshVertex> vertices;
	vector<uint> indices;

	Vector3 position = Vector3(0, 0, 0);
	Vector3 rotation = Vector3(0, 0, 0);
	Vector3 scale = Vector3(1, 1, 1);

private:
	Shader* shader;

	uint pass = 0;
	VertexBuffer* vb = nullptr;
	IndexBuffer* ib = nullptr;

	Texture* diffuseMap = nullptr;

	Matrix world;

	ID3DX11EffectMatrixVariable* sWorld, * sView, * sProjection;
	ID3DX11EffectShaderResourceVariable* sDiffuseMap;
};