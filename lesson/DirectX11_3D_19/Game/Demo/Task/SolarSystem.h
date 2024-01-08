#pragma once

enum PLANET_NAME
{
	SUN,
	MERCURY,
	VENUS,
	EARTH,
	MARS,
	JUPITTER,
	SATURN,
	URANUS,
	NEPTUNE
};

struct Planet
{
	Planet() {}
	Planet(Shader* shader, wstring fileName, 
		float radius, float rotationSpeed, float orbitalSpeed, float axialTilt
	);
	~Planet();

	Sphere* planet;

	wstring fileName;

	float radius;
	float rotationSpeed;
	float orbitalSpeed;

	Vector3 axisOfRotation;
	float axialTilt;

	float orbitalStack;
	float rotationStack;
};

class SolarSystem : public IExecute
{
public:
	// IExecute을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Ready() {}
	virtual void PreRender() {}
	virtual void PostRender() {}
	virtual void ResizeScreen() {}

private:
	Shader* shader;
	Shader* sunShader;

	vector<Planet*> planets;
	Vector3 direction;
	ID3DX11EffectVectorVariable* sDirection;
};