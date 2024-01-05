#pragma once

class Grid : public Mesh
{
public:
	Grid(Shader* shader, float offsetU = 1.0f, float offsetV = 1.0f)
		:Mesh(shader), offsetU(offsetU), offsetV(offsetV) {}
	~Grid() = default;

private:
	virtual void Create() override;

private:
	float offsetU, offsetV;
};