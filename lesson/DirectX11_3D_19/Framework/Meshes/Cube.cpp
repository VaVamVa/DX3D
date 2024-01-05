#include "Framework.h"
#include "Cube.h"

void Cube::Create()
{
	float width = 0.5f, height = 0.5f, depth = 0.5f;

	// 4 * 6∏È√º
	vertices.assign(24, MeshVertex());

	Vector2 LB(0, 1);
	Vector2 LT(0, 0);
	Vector2 RT(1, 0);
	Vector2 RB(1, 1);

	// Front
	vertices[0].Position = Vector3(-width, -height, -depth);
	vertices[1].Position = Vector3(-width, +height, -depth);
	vertices[2].Position = Vector3(+width, +height, -depth);
	vertices[3].Position = Vector3(+width, -height, -depth);

	vertices[0].Uv = LB;
	vertices[1].Uv = LT;
	vertices[2].Uv = RT;
	vertices[3].Uv = RB;

	vertices[0].Normal = Vector3(0, 0, -1);
	vertices[1].Normal = Vector3(0, 0, -1);
	vertices[2].Normal = Vector3(0, 0, -1);
	vertices[3].Normal = Vector3(0, 0, -1);

	// Back
	vertices[4].Position = Vector3(-width, -height, +depth);
	vertices[5].Position = Vector3(+width, -height, +depth);
	vertices[6].Position = Vector3(+width, +height, +depth);
	vertices[7].Position = Vector3(-width, +height, +depth);

	vertices[4].Uv = LB;
	vertices[5].Uv = LT;
	vertices[6].Uv = RT;
	vertices[7].Uv = RB;

	vertices[4].Normal = Vector3(0, 0, +1);
	vertices[5].Normal = Vector3(0, 0, +1);
	vertices[6].Normal = Vector3(0, 0, +1);
	vertices[7].Normal = Vector3(0, 0, +1);

	// Right
	vertices[8].Position = Vector3(+width, -height, -depth);
	vertices[9].Position = Vector3(+width, +height, -depth);
	vertices[10].Position = Vector3(+width, +height, +depth);
	vertices[11].Position = Vector3(+width, -height, +depth);

	vertices[8].Uv = LB;
	vertices[9].Uv = LT;
	vertices[10].Uv = RT;
	vertices[11].Uv = RB;

	vertices[8].Normal = Vector3(+1, 0, 0);
	vertices[9].Normal = Vector3(+1, 0, 0);
	vertices[10].Normal = Vector3(+1, 0, 0);
	vertices[11].Normal = Vector3(+1, 0, 0);

	// Left
	vertices[12].Position = Vector3(-width, -height, +depth);
	vertices[13].Position = Vector3(-width, +height, +depth);
	vertices[14].Position = Vector3(-width, +height, -depth);
	vertices[15].Position = Vector3(-width, -height, -depth);

	vertices[12].Uv = LB;
	vertices[13].Uv = LT;
	vertices[14].Uv = RT;
	vertices[15].Uv = RB;

	vertices[12].Normal = Vector3(-1, 0, 0);
	vertices[13].Normal = Vector3(-1, 0, 0);
	vertices[14].Normal = Vector3(-1, 0, 0);
	vertices[15].Normal = Vector3(-1, 0, 0);

	// Up
	vertices[16].Position = Vector3(-width, +height, -depth);
	vertices[17].Position = Vector3(-width, +height, +depth);
	vertices[18].Position = Vector3(+width, +height, +depth);
	vertices[19].Position = Vector3(+width, +height, -depth);

	vertices[16].Uv = LB;
	vertices[17].Uv = LT;
	vertices[18].Uv = RT;
	vertices[19].Uv = RB;

	vertices[16].Normal = Vector3(0, +1, 0);
	vertices[17].Normal = Vector3(0, +1, 0);
	vertices[18].Normal = Vector3(0, +1, 0);
	vertices[19].Normal = Vector3(0, +1, 0);

	// Down
	vertices[20].Position = Vector3(-width, -height, +depth);
	vertices[21].Position = Vector3(-width, -height, -depth);
	vertices[22].Position = Vector3(+width, -height, -depth);
	vertices[23].Position = Vector3(+width, -height, +depth);

	vertices[20].Uv = LB;
	vertices[21].Uv = LT;
	vertices[22].Uv = RT;
	vertices[23].Uv = RB;

	vertices[20].Normal = Vector3(0, -1, 0);
	vertices[21].Normal = Vector3(0, -1, 0);
	vertices[22].Normal = Vector3(0, -1, 0);
	vertices[23].Normal = Vector3(0, -1, 0);

	indices =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};
}
