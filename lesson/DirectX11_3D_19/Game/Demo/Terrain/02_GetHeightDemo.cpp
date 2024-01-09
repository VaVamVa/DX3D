#include "stdafx.h"
#include "02_GetHeightDemo.h"

void GetHeightDemo::Initialize()
{
	CAMERA->SetPosition(0, 30, -10);
	CAMERA->SetRotationDegree(30, 0, 0);

	shader = new Shader(L"08_Terrain.fx");

	terrain = new Terrain(shader, L"height_map.jpg");
	terrain->Pass(0);

	triShader = new Shader(L"03_World.fx");

	vector<Vertex> vertices;
	vertices.assign(3, Vertex());
	vertices[0].Position = Vector3(0, -1, 0);
	vertices[1].Position = Vector3(-1, 0, 0);
	vertices[2].Position = Vector3(1, 0, 0);

	vb = new VertexBuffer(vertices);
}

void GetHeightDemo::Destroy()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(triShader);

	SAFE_DELETE(terrain);
	SAFE_DELETE(shader);
}

void GetHeightDemo::Update()
{
	static uint pass = 0;
	ImGui::InputInt("Pass", (int*)&pass);
	pass %= 2;
	terrain->Pass(pass);

	terrain->Update();


	auto* k = Keyboard::Get();
	float speed = 20.0f * Time::Delta();

	if (k->Press(VK_RIGHT))
		position.x += speed;
	if (k->Press(VK_LEFT))
		position.x -= speed;
	if (k->Press(VK_UP))
		position.z += speed;
	if (k->Press(VK_DOWN))
		position.z -= speed;

	//position.y = terrain->GetHeight(position) + 1;
	position.y = terrain->GetVerticalRaycast(position) + 1.0f;
	Vector3 start(position.x, 50, position.z);
	Vector3 end(position.x, 0, position.z);

	DebugLine::Get()->RenderLine(start, end, Color(1, 0, 0, 1));

	Matrix T;
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	triShader->AsMatrix("World")->SetMatrix(T);
	triShader->AsMatrix("View")->SetMatrix(VIEW);
	triShader->AsMatrix("Projection")->SetMatrix(PROJECTION);
}

void GetHeightDemo::Render()
{
	terrain->Render();

	vb->SetIA();
	TRIANGLE_LIST;
	triShader->Draw(0, 0, 3);

	string str = to_string(position.x) + ", " + to_string(position.y) + ", " + to_string(position.z);
	GUI::Get()->RenderText(5, 60, str);
}
