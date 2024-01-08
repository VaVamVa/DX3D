#include "stdafx.h"
#include "SolarSystem.h"

#include <iostream>
#include <fstream>
#include <sstream>

Planet::Planet(Shader* shader, wstring fileName, float radius, float rotationSpeed, float orbitalSpeed, float axialTilt)
	:fileName(fileName), radius(radius), rotationSpeed(rotationSpeed), orbitalSpeed(orbitalSpeed), axialTilt(axialTilt)
{
	planet = new Sphere(shader, radius);

	wstring texturePath = L"../_Textures/SolarSystem/" + fileName;
	planet->SetDiffuseMap(texturePath);

	planet->SetRotationDegree(axialTilt, 0, 0);
	axisOfRotation = planet->GetUpVector();

	orbitalStack = 0.0f;
	rotationStack = 0.0f;
}

Planet::~Planet()
{
	SAFE_DELETE(planet);
}

void SolarSystem::Initialize()
{
	CAMERA->SetPosition(0, 0, -250);

	shader = new Shader(L"07_Mesh.fx");
	sunShader = new Shader(L"07_Sun.fx");

	sDirection = shader->AsVector("LightDirection");

	// read csv file
	{
		ifstream file("../_Files/SolarSystem.csv");

		if (!file.is_open())
			assert(false);
		else
		{
			string line;
			while (getline(file, line))
			{
				stringstream ss(line);
				string field;
				vector<string> row;

				while (getline(ss, field, ','))
				{
					row.push_back(field);
				}

				wstring fileName = String::ToWString(row[0]);

				float radius = stof(row[1]);
				float rotationSpeed = stof(row[2]);
				float orbitalSpeed = stof(row[3]);
				float axialTilt = stof(row[4]);

				planets.push_back(new Planet(
					shader,
					fileName,
					radius, rotationSpeed, orbitalSpeed, axialTilt
				));
			}

			file.close();
		}
	}

	planets[SUN]->planet->SetShader(sunShader);

	for (int i = 0; i < planets.size(); i++)
	{
		planets[i]->planet->SetPosition(i * 20, 0, 0);
	}
}

void SolarSystem::Destroy()
{
	for (auto& p : planets)
		SAFE_DELETE(p);
	SAFE_DELETE(shader);
	SAFE_DELETE(sunShader);
}

void SolarSystem::Update()
{
	static float orbitalSpeedRatio = 0.1f;
	static float rotationSpeedRatio = 1.0f;
	if (ImGui::TreeNode("Planet Speed"))
	{
		ImGui::InputFloat("Orbital Speed ratio", &orbitalSpeedRatio, 0.01f);
		ImGui::InputFloat("Rotation Speed ratio", &rotationSpeedRatio, 0.01f);

		ImGui::TreePop();
	}

	Sphere* sun = planets[SUN]->planet;

	for (auto& p : planets)
	{
		Matrix S, R, T;
		D3DXMatrixIdentity(&S);
		D3DXMatrixIdentity(&R);
		D3DXMatrixIdentity(&T);

		// revolve
		{
			p->orbitalStack += p->orbitalSpeed * orbitalSpeedRatio * Time::Delta();

			Vector3 v = p->planet->GetPosition() - sun->GetPosition();
			float length = fabsf(D3DXVec3Length(&v));

			Vector3 position;
			position.x = cosf(p->orbitalStack) * length;
			position.y = 0.0f;
			position.z = sinf(p->orbitalStack) * length;

			D3DXMatrixTranslation(&T, position.x, position.y, position.z);
		}

		// rotation
		{
			p->rotationStack += p->rotationSpeed * rotationSpeedRatio * Time::Delta();

			D3DXMatrixRotationAxis(&R, &p->axisOfRotation, p->rotationStack);

		}

		p->planet->GetWorld() = S * R * T;
		p->planet->Update();
	}
}

void SolarSystem::Render()
{
	Vector3 cp = CAMERA->GetPosition();
	ImGui::InputFloat3("Camera Position", cp, 2);
	CAMERA->SetPosition(cp);

	Sphere* sun = planets[SUN]->planet;

	for (auto& p : planets)
	{
		Matrix world = p->planet->GetWorld();
		Vector3 position = Vector3(world._41, world._42, world._43);

		direction = position - sun->GetPosition();
		D3DXVec3Normalize(&direction, &direction);

		sDirection->SetFloatVector(direction);

		p->planet->Render();
	}
}
