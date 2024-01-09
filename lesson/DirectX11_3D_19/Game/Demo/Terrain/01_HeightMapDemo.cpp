#include "stdafx.h"
#include "01_HeightMapDemo.h"

void HeightMapDemo::Initialize()
{
	CAMERA->SetPosition(0, 30, -10);
	CAMERA->SetRotationDegree(30, 0, 0);

	shader = new Shader(L"08_Terrain.fx");

	terrain = new Terrain(shader, L"height_map.jpg");
	terrain->Pass(0);
}

void HeightMapDemo::Destroy()
{
	SAFE_DELETE(terrain);
	SAFE_DELETE(shader);
}

void HeightMapDemo::Update()
{
	static uint pass = 0;
	ImGui::InputInt("Pass", (int*)&pass);
	pass %= 2;
	terrain->Pass(pass);

	terrain->Update();
}

void HeightMapDemo::Render()
{
	terrain->Render();
}
