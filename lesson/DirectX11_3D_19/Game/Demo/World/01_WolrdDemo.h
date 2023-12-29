#pragma once

/*
wolrd : 게임 세계를 표현.
위치, 회전, 크기를 가진 행렬.
*/
class WorldDemo : public IExecute
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
	VertexBuffer* vb = nullptr;

	vector<Vertex> vertices;

	Matrix world;
	Matrix world2;
};