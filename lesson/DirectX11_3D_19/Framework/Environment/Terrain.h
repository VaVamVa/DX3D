#pragma once

class Terrain
{
public:
	typedef VertexNormal TerrainVertex;

public:
	Terrain(Shader* shader, wstring heightFile);
	~Terrain();

	void Update();
	void Render();

	void Pass(uint value) { pass = value; }

	/*
	* 1
	Terrain은 정사각형들의 집합이기 때문에,
	캐릭터의 좌표에 따라 서있는 사각형(더 구체적으로 polygon)의 위치를 특정 가능하다.
	 -------
	|	   /|
	|	/	|
	|/	  o |
	v-------
	시작점 x에 대해서 캐릭터의 위치 o를 안다면,
	v의 위치에 대한 비율을 알 수 있기에 이를 이용해 높이값을 구한다.
	*/
	float GetHeight(Vector3 position);
	/*
	* 2
	dx에서 기본적으로 제공해주는 레이져 쏘는 방법.
	*/
	float GetVerticalRaycast(Vector3 position);

private:
	uint pass = 0;
	Shader* shader;

	Texture* heightMap = nullptr;

	uint width = 0, height = 0;

	vector<TerrainVertex> vertices;
	VertexBuffer* vb;

	vector<uint> indices;
	IndexBuffer* ib;

};