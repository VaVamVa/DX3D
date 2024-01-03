#pragma once

class CubeDemo : public IExecute
{
public:
	// IExecute을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Ready() {}
	virtual void PreRender() {}
	virtual void PostRender() {}
	virtual void ResizeScreen() {}

private:
	Shader* shader;

	vector<Vertex> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	Vector3 position = { 0, 0, 0 };
	Vector3 rotation = { 0, 0, 0 };

	Matrix world;

	Color color = Color(0, 0, 1, 1);
};