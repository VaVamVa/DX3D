#pragma once

class TextureLoadDemo : public IExecute
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
	void LoadTexture(wstring file);


private:
	Shader* shader;

	vector<VertexTexture> vertices;
	VertexBuffer* vb;

	vector<uint> indices;
	IndexBuffer* ib;

	Matrix world;

	Texture* texture;
};