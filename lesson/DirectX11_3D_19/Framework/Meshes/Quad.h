#pragma once

class Quad : public Mesh
{
public:
	Quad(Shader* shader)
		: Mesh(shader) {}
	~Quad() = default;

private:
	virtual void Create() override;
};