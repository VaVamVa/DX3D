#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matView);

	Rotation();
	Move();
}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	SetPosition(Vector3(x, y, z));
}

void Camera::SetPosition(Vector3 pos)
{
	position = pos;
	Move();
}

void Camera::SetRotation(float x, float y, float z)
{
	SetRotation(Vector3(x, y, z));
}

void Camera::SetRotation(Vector3 rot)
{
	rotation = rot;
	Rotation();
}

void Camera::SetRotationDegree(float x, float y, float z)
{
	SetRotationDegree(Vector3(x, y, z));
}

void Camera::SetRotationDegree(Vector3 rotDegree)
{
	// PI(3.141592) / 180.0f
	rotation = rotDegree * 0.01745328f;
	Rotation();
}

void Camera::GetPosition(Vector3* outPosition)
{
	*outPosition = position;
}

void Camera::GetRotation(Vector3* outRotation)
{
	*outRotation = rotation;
}

void Camera::GetRotationDegree(Vector3* outRotation)
{
	// 180.0f / PI(3.141592)
	*outRotation = rotation * 57.2977957f;
}

Matrix Camera::GetMatrix()
{
	return matView;
}

void Camera::GetMatrix(Matrix* view)
{
	memcpy(view, &matView, sizeof(Matrix));
	//*view = matView;
}

void Camera::Rotation()
{
	/*
	Matrix X, Y, Z;

	D3DXMatrixRotationX(&X, rotation.x);
	D3DXMatrixRotationY(&Y, rotation.y);
	D3DXMatrixRotationZ(&Z, rotation.z);
	*/
	//matRotation = X * Y * Z;
	
	// 왼손좌표계 => 엄지 : Pitch(X), 중지 : Roll(Z), 검지 : Yaw(Y)
	D3DXMatrixRotationYawPitchRoll(&matRotation, rotation.y, rotation.x, rotation.z);

	Vector3 forward = Vector3(0, 0, 1);
	Vector3 up = Vector3(0, 1, 0);
	Vector3 right = Vector3(1, 0, 0);

	D3DXVec3TransformNormal(&this->forward, &forward, &matRotation);
	D3DXVec3TransformNormal(&this->up, &up, &matRotation);
	D3DXVec3TransformNormal(&this->right, &right, &matRotation);

	UpdateViewMatrix();
}

void Camera::Move()
{
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	Vector3 at = position + forward;  // 카메라의 위치에 따라서 z 방향 바라보기

	D3DXMatrixLookAtLH(&matView, &position, &at, &up);
}
