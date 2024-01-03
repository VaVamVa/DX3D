#pragma once

class TextureSamplerDemo : public IExecute
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

	vector<VertexTexture> vertices;
	VertexBuffer* vb;

	vector<uint> indices;
	IndexBuffer* ib;

	Matrix world;
	ID3D11ShaderResourceView* srv;  // Texture를 받아서 shader에 전달한다. 간단하게 "image"
};