#pragma once

class Freedom : public Camera
{
public:
	Freedom() : Camera() {}
	~Freedom() {}

	void Update() override;

	void SetSpeed(float move, float rotation = 2.0f);

private:
	float moveSpeed = 20.0f;
	float rotationSpeed = 2.0f;
};