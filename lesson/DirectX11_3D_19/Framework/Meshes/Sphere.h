#pragma once

class Sphere : public Mesh
{
public:
	Sphere(Shader* shader, float radius, uint stackStep = 20, uint sliceStep = 20)
		:Mesh(shader), radius(radius), stackStep(stackStep), sliceStep(sliceStep)
	{}
	~Sphere() = default;

private:
	virtual void Create() override;

private:
	float radius;
	uint stackStep, sliceStep;
};