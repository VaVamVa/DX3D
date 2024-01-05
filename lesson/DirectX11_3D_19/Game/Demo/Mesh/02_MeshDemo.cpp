#include "stdafx.h"
#include "02_MeshDemo.h"

void MeshDemo::Initialize()
{
	CAMERA->SetRotationDegree(20, 0, 0);
	CAMERA->SetPosition(0, 10.0f, -5.0f);

	shader = new Shader(L"07_Mesh.fx");
	sLightDirection = shader->AsVector("LightDirection");
	
	/* trash bin
	*/
	quad = new Quad(shader);
	quad->SetDiffuseMap(L"../_Textures/2024NewYear.jpg");
	quad->SetPosition(0, 4.0f, 0);
	quad->SetScale(3, 1, 1);

	cube = new Cube(shader);
	cube->SetDiffuseMap(L"../_Textures/box.jpg");
	cube->SetPosition(0, 1.5f, 0);
	cube->SetScale(5, 3, 5);

	grid = new Grid(shader, 10, 10);
	grid->SetDiffuseMap(L"../_Textures/floor.jpg");
	grid->SetScale(9, 1, 9);

	sphere = new Sphere(shader, 1);
	sphere->SetDiffuseMap(L"../_Textures/earth.jpg");
	sphere->SetPosition(0, 10.0f, 0);
	sphere->SetScale(5, 5, 5);
}

void MeshDemo::Destroy()
{
	SAFE_DELETE(quad);
	SAFE_DELETE(cube);
	SAFE_DELETE(grid);
	SAFE_DELETE(sphere);

	SAFE_DELETE(shader);
}

void MeshDemo::Update()
{
	quad->Update();
	cube->Update();
	grid->Update();
	sphere->Update();
}

void MeshDemo::Render()
{
	ImGui::SliderFloat3("Light Direction", lightDirection, -1, 1);
	sLightDirection->SetFloatVector(lightDirection);

	quad->Render();
	cube->Render();
	grid->Render();
	sphere->Render();
}
