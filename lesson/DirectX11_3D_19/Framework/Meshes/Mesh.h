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
	1. A : 환경광. 주변광에 영향으로 바뀌는 색
	2. D : 고유색. 물체가 가진 고유의 색 (음영 포함)
	3. S : 반사광. 금속재질이나 물처럼 허옇게 반사되는 부분
	4. E : 방출광. 외곽선을 표현하기 위해 빛을 냄
	빛은 원래의 색을 상쇄시킴.

	빛 계산(램퍼트 식) : 각 vertex에 법선벡터와 빛의 방향에 반대방향 사이의 각도(내적)을 구해
	Sampler State에서 Pixel의 색에 곱해줌
	-> 빛의 반대방향에서는 0에 수렴하게 될것임.
	*/
	void SetDiffuseMap(wstring file);
	
protected:
	// vertex에 대한 정보 외에는 모두 같은 정보. vertex setting만 순수 가상함수로
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