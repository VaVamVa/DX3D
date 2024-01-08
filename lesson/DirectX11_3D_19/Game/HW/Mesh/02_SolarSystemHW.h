#pragma once

class SolarSystemHW : public IExecute
{
private:
	enum Attribute
	{
		AU,
		RADIUS,
		SLOPE,
		ROTATION,
		REVOLUTION
	};

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
	void CreateStars();

private:
	Shader* shader;

	Vector3 lightDirection = Vector3(-1, -1, -1);
	ID3DX11EffectVectorVariable* sLightDirection;

	unordered_map<string, Sphere*> planets;
	unordered_map<string, vector<float>> planetsAttributes;
	Sphere* sun;

	float time = 0.0f;
	float revolutionFactor = 100.0f;
	float distanceFactor = 50.0f;
	float rotationFactor = 1.0f;

	string target = "Free";
};