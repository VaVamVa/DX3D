#pragma once

class Context : public Singleton<Context>
{
public:
	friend Singleton<Context>;

	void ResizeScreen();

	void Update();
	void Render();

	D3DXMATRIX View() { return view; }
	D3DXMATRIX GetProjectionMatrix();

	class Projection* GetProjection() { return projection; }
	class Viewport* GetViewport() { return viewport; }

private:
	Context();
	~Context();

private:
	class Projection* projection;
	class Viewport* viewport;

	D3DXVECTOR3 position;
	D3DXMATRIX view;
};