#pragma once

/*
wolrd : ���� ���踦 ǥ��.
��ġ, ȸ��, ũ�⸦ ���� ���.
*/
class WorldDemo : public IExecute
{
public:
	// IExecute��(��) ���� ��ӵ�
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
	VertexBuffer* vb = nullptr;

	vector<Vertex> vertices;

	Matrix world;
	Matrix world2;
};