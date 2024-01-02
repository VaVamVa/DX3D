#pragma once

class Context : public Singleton<Context>
{
public:
	friend Singleton<Context>;

	void ResizeScreen();

	void Update();
	void Render();

	D3DXMATRIX View();
	D3DXMATRIX GetProjectionMatrix();

	class Projection* GetProjection() { return projection; }
	class Viewport* GetViewport() { return viewport; }
	class Camera* GetCamera() { return camera; }

private:
	Context();
	~Context();

private:
	class Projection* projection;
	class Viewport* viewport;

	/*
	* camera·Î
	D3DXVECTOR3 position;
	D3DXMATRIX view;
	*/
	class Camera* camera;
};