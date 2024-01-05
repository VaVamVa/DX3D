#include "Framework.h"
#include "Quad.h"

void Quad::Create()
{
	float w = 0.5f, h = 0.5f;

	vertices.assign(4, MeshVertex());

	vertices[0].Position = Vector3(-w, -h, 0);
	vertices[1].Position = Vector3(-w, +h, 0);
	vertices[2].Position = Vector3(+w, +h, 0);
	vertices[3].Position = Vector3(+w, -h, 0);

	vertices[0].Uv = Vector2(0, 1.0f);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(1.0f, 0);
	vertices[3].Uv = Vector2(1.0f, 1.0f);

	vertices[0].Normal = Vector3(0, 0, -1.0f);
	vertices[1].Normal = Vector3(0, 0, -1.0f);
	vertices[2].Normal = Vector3(0, 0, -1.0f);
	vertices[3].Normal = Vector3(0, 0, -1.0f);

	indices = { 0, 1, 2, 2, 3, 0 };
}
