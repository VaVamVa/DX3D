#pragma once
#define MAX_DEBUG_LINE 150000

class DebugLine : public Singleton<DebugLine>
{
public:
	friend Singleton<DebugLine>;

private:
	DebugLine();
	~DebugLine();

public:
	void RenderLine(Vector3 start, Vector3 end);
	void RenderLine(Vector3 start, Vector3 end, float r, float g, float b);
	void RenderLine(Vector3 start, Vector3 end, Color color);

	void RenderLine(float x, float y, float z, float x2, float y2, float z2);
	void RenderLine(float x, float y, float z, float x2, float y2, float z2, float r, float g, float b);
	void RenderLine(float x, float y, float z, float x2, float y2, float z2, Color color);

public:
	void Update();
	void Render();

private:
	Shader* shader;

	class VertexBuffer* vb = nullptr;

	vector<VertexColor> vertices;
	
	uint drawCount = 0;
};