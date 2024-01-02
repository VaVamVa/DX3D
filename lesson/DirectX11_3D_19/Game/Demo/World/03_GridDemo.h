#pragma once

class GridDemo : public IExecute
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
	Matrix world;
	uint width = 256, height = 256;

	vector<Vertex> vertices;
	VertexBuffer* vb;

	vector<uint> indices;
	IndexBuffer* ib;

};