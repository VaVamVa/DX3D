#pragma once

enum class ProjectionMode
{
	Orthographic = 0,
	Perspective
};

class Projection
{
public:
	Projection(float width, float height, float zn = 0.1f, float zf = 1000.0f, float fov = (float)D3DX_PI * 0.25f);
	~Projection();

	void GetMatrix(Matrix* matrix);
	
	void Set(float width, float height, float zn = 0.1f, float zf = 1000.0f, float fov = (float)D3DX_PI * 0.25f);

protected:
	float width, height;
	float zn, zf;
	float fov;

	Matrix matrix;

	ProjectionMode mode;
};