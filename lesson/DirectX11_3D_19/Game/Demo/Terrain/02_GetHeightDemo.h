#pragma once

class GetHeightDemo : public IExecute
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

	Terrain* terrain;

	Vector3 position = Vector3(0, 0, 0);

	Shader* triShader = nullptr;
	VertexBuffer* vb = nullptr;
};