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
	Terrain�� ���簢������ �����̱� ������,
	ĳ������ ��ǥ�� ���� ���ִ� �簢��(�� ��ü������ polygon)�� ��ġ�� Ư�� �����ϴ�.
	 -------
	|	   /|
	|	/	|
	|/	  o |
	v-------
	������ x�� ���ؼ� ĳ������ ��ġ o�� �ȴٸ�,
	v�� ��ġ�� ���� ������ �� �� �ֱ⿡ �̸� �̿��� ���̰��� ���Ѵ�.
	*/
	float GetHeight(Vector3 position);
	/*
	* 2
	dx���� �⺻������ �������ִ� ������ ��� ���.
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