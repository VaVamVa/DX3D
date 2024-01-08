#pragma once

class Cylinder : public Mesh
{
public:
	Cylinder(Shader* shader, float radius, float height, uint stackCount, uint sliceCount)
		:Mesh(shader), topRadius(radius), bottomRadius(radius), height(height), stackCount(stackCount), sliceCount(sliceCount)
	{}
	Cylinder(Shader* shader, float topRadius, float bottomRadius, float height, uint stackCount, uint sliceCount)
		:Mesh(shader), topRadius(topRadius), bottomRadius(bottomRadius), height(height), stackCount(stackCount), sliceCount(sliceCount)
	{}
	~Cylinder() = default;

private:
	virtual void Create() override;

private:
	void BuildTopCap();
	void BuildBottomCap();

private:
	float topRadius, bottomRadius, height;

	uint stackCount, sliceCount;
	
};