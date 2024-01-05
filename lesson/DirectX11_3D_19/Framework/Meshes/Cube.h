#pragma once

class Cube : public Mesh
{
public:
	Cube(Shader* shader)
		:Mesh(shader) {}
	~Cube() = default;

private:
	virtual void Create() override;
};