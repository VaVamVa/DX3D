#include "stdafx.h"
#include "02_SolarSystemHW.h"

#include <fstream>

void SolarSystemHW::Initialize()
{
	shader = new Shader(L"07_Mesh.fx");
	sLightDirection = shader->AsVector("LightDirection");

	planetsAttributes.insert({ "Free", vector<float>()});

	CreateStars();
}

void SolarSystemHW::Destroy()
{
	SAFE_DELETE(sun);
	for (pair<string, Sphere*> planet : planets)
		SAFE_DELETE(planet.second);
	planets.clear();
	SAFE_DELETE(shader);
}

void SolarSystemHW::Update()
{
	time += Time::Delta();

	sun->Update();

	// Planets Rotation
	{
		sun->SetRotation(0, time * rotationFactor * planetsAttributes["sun"][ROTATION], 0);

		for (pair<string, Sphere*> planet : planets)
		{
			planet.second->SetPosition(
				cosf(time * revolutionFactor / planetsAttributes[planet.first][REVOLUTION]) * planetsAttributes[planet.first][AU] * distanceFactor + sun->GetPosition().x,
				sun->GetPosition().y,
				sinf(time * revolutionFactor / planetsAttributes[planet.first][REVOLUTION]) * planetsAttributes[planet.first][AU] * distanceFactor + sun->GetPosition().z
			);

			Matrix axisM;
			Vector3 axis = planet.second->GetUpVector();
			float rotationValue = time * rotationFactor * planetsAttributes[planet.first][ROTATION];
			D3DXMatrixRotationAxis(&axisM, &axis, rotationValue);

			planet.second->MulRoationMatrix(axisM);
			planet.second->Update();
		}
	}

	// Change Camera Target
	{
		if (target == "sun")
		{
			CAMERA->SetPosition(sun->GetPosition().x, sun->GetPosition().y + 30.0f, sun->GetPosition().z - 100.0f);
			CAMERA->SetRotation(2 * tanf(abs(CAMERA->GetPosition().z / CAMERA->GetPosition().y)), 0, 0);
		}
		else if (target != "Free")
		{
			float radian = atan2f(planets[target]->GetPosition().z, planets[target]->GetPosition().x);
			float distance = planetsAttributes[target][AU] * distanceFactor - planetsAttributes[target][RADIUS] * 5.0f;
			CAMERA->SetPosition(cosf(radian) * distance, 0, sinf(radian) * distance);
			Vector3 camDirection = planets[target]->GetPosition() - CAMERA->GetPosition();
		
			CAMERA->SetRotation(0, atan2f(camDirection.x, camDirection.z), 0);
		}
	}
}

void SolarSystemHW::Render()
{
	//lightDirection = sun->GetPosition() - CAMERA->GetPosition();
	//sLightDirection->SetFloatVector(lightDirection);
	sun->Render();

	for (pair<string, Sphere*> planet : planets)
	{
		lightDirection = planet.second->GetPosition() - sun->GetPosition();
		sLightDirection->SetFloatVector(lightDirection);
		planet.second->Render();
	}

	ImGui::SliderFloat("Rotation factor", &rotationFactor, 0.0f, 2.0f);
	ImGui::SliderFloat("Revolution factor", &revolutionFactor, 0.0f, 200.0f);
	ImGui::SliderFloat("AU distance", &distanceFactor, 0.0f, 100.0f);
	for (unordered_map<string, vector<float>>::iterator iter = planetsAttributes.begin(); iter != planetsAttributes.end(); iter++)
		if (ImGui::Selectable(iter->first.c_str(), iter->first.c_str() == target))
		{
			target = iter->first.c_str();
		}
	
}

// https://astro.kasi.re.kr/learning/pageView/5116
// https://kr.calc-time.com/index.php#sec5
void SolarSystemHW::CreateStars()
{
	string fileName = "../_DataTable/Solar_System.tsv";
	ifstream file;
	try
	{
		file.open(fileName, std::ios::in);
		if (file.fail()) throw std::runtime_error{ " Unable to open file " };
	}
	catch (const std::runtime_error& e)
	{
		OutputDebugStringA(e.what());
		return;
	}

	int columnSize = 7;
	string buffer;

	for (int i = 0; i < columnSize; i++)
		file >> buffer;

	string name = "";

	// slope, rotation, revolution

	while (true)
	{
		file >> buffer; // key

		if (file.eof())
			break;

		vector<float> attributes(5);
		file >> name 
			>> attributes[AU] >> attributes[RADIUS] 
			>> attributes[SLOPE] >> attributes[ROTATION] >> attributes[REVOLUTION];
		attributes[SLOPE] *= Math::PI / 180.0f;
		wstring name_w;
		name_w.assign(name.begin(), name.end());

		planetsAttributes[name] = attributes;

		if (name == "sun")
		{
			sun = new Sphere(shader, attributes[RADIUS], 30, 30);
			sun->SetDiffuseMap(L"../_Textures/SolarSystem/" + name_w + L".jpg");

			CAMERA->SetPosition(sun->GetPosition().x, sun->GetPosition().y + 30.0f, sun->GetPosition().z - 100.0f);
			// cotan(Cam) = tan(1 / (abs(CamPos.y / CamPos.z)))
			CAMERA->SetRotation(2 * tanf(abs(CAMERA->GetPosition().z / CAMERA->GetPosition().y)), 0, 0);
			sun->SetPass(2);
		}
		else
		{
			planets[name] = new Sphere(shader, attributes[RADIUS], 30, 30);
			planets[name]->SetDiffuseMap(L"../_Textures/SolarSystem/" + name_w + L".jpg");
			planets[name]->SetPosition(sun->GetPosition().x + attributes[AU] * distanceFactor, sun->GetPosition().y, sun->GetPosition().z);
			planets[name]->SetRotation(0, 0, attributes[SLOPE]);
		}
	}

	file.close();
}
