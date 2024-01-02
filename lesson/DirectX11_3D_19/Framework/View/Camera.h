#pragma once

class Camera
{
private:


public:
	Camera();
	virtual ~Camera();

	virtual void Update() = 0;

public:
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 pos);

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 rot);

	void SetRotationDegree(float x, float y, float z);
	void SetRotationDegree(Vector3 rotDegree);

	Vector3 GetPosition() { return position; }
	void GetPosition(Vector3* outPosition);


	Vector3 GetRotation() { return rotation; }
	void GetRotation(Vector3* outRotation);

	Vector3 GetRotationDegree() { return rotation * 57.2977957f; }
	void GetRotationDegree(Vector3* outRotation);

	Matrix GetMatrix();
	void GetMatrix(Matrix* view);

	Vector3 GetForwardVec() { return forward; }
	Vector3 GetUpVec() { return up; }
	Vector3 GetRightVec() { return right; }

protected:
	virtual void Rotation();
	virtual void Move();

	void UpdateViewMatrix();

protected:
	Vector3 position = Vector3(0, 0, 0);
	Vector3 rotation = Vector3(0, 0, 0);

	Vector3 forward = Vector3(0, 0, 1);
	Vector3 up = Vector3(0, 1, 0);
	Vector3 right = Vector3(1, 0, 0);

	Matrix matRotation;		// 회전 행렬
	Matrix matView;			// 뷰 행렬
};