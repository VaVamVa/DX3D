#include "Framework.h"
#include "Freedom.h"

void Freedom::Update()
{
	if (Mouse::Get()->Press(Mouse::MOUSE_INPUT_RBUTTON) == false) return;

	// move
	{
		if (Keyboard::Get()->Press('W'))
			position += forward * moveSpeed * Time::Delta();
		if (Keyboard::Get()->Press('S'))
			position -= forward * moveSpeed * Time::Delta();

		if (Keyboard::Get()->Press('D'))
			position += right * moveSpeed * Time::Delta();
		if (Keyboard::Get()->Press('A'))
			position -= right * moveSpeed * Time::Delta();

		if (Keyboard::Get()->Press(VK_SPACE))
			position += up * moveSpeed * Time::Delta();
		if (Keyboard::Get()->Press(VK_CONTROL))
			position -= up * moveSpeed * Time::Delta();

		Move();
	}

	// rotation
	{
		Vector3 value = Mouse::Get()->GetMoveValue();
		rotation.x += value.y * rotationSpeed * Time::Delta();
		rotation.y += value.x * rotationSpeed * Time::Delta();
		rotation.z = 0.0f;

		Rotation();
	}
}

void Freedom::SetSpeed(float move, float rotation)
{
	this->moveSpeed = move;
	this->rotationSpeed = rotation;
}
