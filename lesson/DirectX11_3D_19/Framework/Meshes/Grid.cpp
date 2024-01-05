#include "Framework.h"
#include "Grid.h"

void Grid::Create()
{
	uint countX = 11;
	uint countZ = 11;

	// grid¿« ¡ﬂæ”¡°
	float w = ((float)countX - 1) * 0.5f;
	float h = ((float)countZ - 1) * 0.5f;

	for (uint z = 0; z < countZ; z++)
	{
		for (uint x = 0; x < countX; x++)
		{
			MeshVertex vertex;

			vertex.Position = Vector3((float)x - w, 0, (float)z - h);

			vertex.Normal = Vector3(0, 1, 0);
			vertex.Uv.x = (float)x / (float)(countX - 1) * offsetU;
			vertex.Uv.y = (float)z / (float)(countZ - 1) * offsetV;
			
			vertices.push_back(vertex);
		}
	}

	for (uint z = 0; z < countZ - 1; z++)
	{
		for (uint x = 0; x < countX - 1; x++)
		{
			indices.push_back(countX * z + x);
			indices.push_back(countX * (z + 1) + x);
			indices.push_back(countX * z + x + 1);

			indices.push_back(countX * z + x + 1);
			indices.push_back(countX * (z + 1) + x);
			indices.push_back(countX * (z + 1) + x + 1);
		}
	}
}