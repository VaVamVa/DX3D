#pragma once

class TextureSamplerDemo : public IExecute
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

	vector<VertexTexture> vertices;
	VertexBuffer* vb;

	vector<uint> indices;
	IndexBuffer* ib;

	Matrix world;
	ID3D11ShaderResourceView* srv;  // Texture�� �޾Ƽ� shader�� �����Ѵ�. �����ϰ� "image"
};