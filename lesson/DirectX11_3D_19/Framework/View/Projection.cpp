#include "Framework.h"
#include "Projection.h"

Projection::Projection(float width, float height, float zn, float zf, float fov)
	: width(width), height(height), zn(zn), zf(zf), fov(fov)
{
	D3DXMatrixIdentity(&matrix);

	mode = fov == 0 ? ProjectionMode::Orthographic : ProjectionMode::Perspective;

	Set(width, height, zn, zf, fov);
}

Projection::~Projection() { }

void Projection::GetMatrix(Matrix* matrix)
{
	memcpy(matrix, &this->matrix, sizeof(Matrix));
}

void Projection::Set(float width, float height, float zn, float zf, float fov)
{
	this->width = width;
	this->height = height;
	this->zn = zn;
	this->zf = zf;
	this->fov = fov;

	switch (mode)
	{
		case ProjectionMode::Orthographic:
		{
			D3DXMatrixOrthoLH(&matrix, width, height, zn, zf);
			break;
		}
		case ProjectionMode::Perspective:
		{
			float aspect = width / height;
			D3DXMatrixPerspectiveFovLH(&matrix, fov, aspect, zn, zf);
			break;
		}
	}
}
