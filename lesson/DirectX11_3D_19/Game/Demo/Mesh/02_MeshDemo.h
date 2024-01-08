#pragma once

class MeshDemo : public IExecute
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

	Vector3 lightDirection = Vector3(-1, -1, -1);
	ID3DX11EffectVectorVariable* sLightDirection;

	Quad* quad;
	Cube* cube;
	Grid* grid;
	Sphere* sphere;
	Cylinder* cylinder;

	float revolution = 0.0f;
	float time = 0.0f;
};