#include "Framework.h"
#include "Context.h"
#include "View/Viewport.h"
#include "View/Projection.h"

Context::Context()
{
	GRAPHICS_DESC desc = Graphics::GetDesc();

	projection = new Projection(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);

	/*
	* camera에서 만드는 view 행렬
	position = D3DXVECTOR3(0, 0, -10);
	D3DXVECTOR3 forward(0, 0, 1);
	D3DXVECTOR3 right(1, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXVECTOR3 at = position + forward;

	D3DXMatrixLookAtLH(&view, &position, &at, &up);
	*/
	camera = new Freedom();

}

Context::~Context()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(projection);
	SAFE_DELETE(viewport);
}

void Context::ResizeScreen()
{
	projection->Set(Graphics::Width(), Graphics::Height());
	viewport->Set(Graphics::Width(), Graphics::Height());
}

void Context::Update()
{
	camera->Update();
}

void Context::Render()
{
	viewport->RSSetViewport();

	string str = string("FrameRate : ") + to_string(ImGui::GetIO().Framerate);
	// 위치, 글자색, 글
	GUI::Get()->RenderText(5, 5, 1, 1, 1, str);

	Vector3 R = camera->GetRotationDegree();
	Vector3 P = camera->GetPosition();

	str = "Camera Rotation : ";
	str += to_string((int)R.x % 360) + ", "
		+ to_string((int)R.y % 360) + ", "
		+ to_string((int)R.z % 360);
	GUI::Get()->RenderText(5, 20, 1, 1, 1, str);

	str = "Camera Position : ";
	str += to_string((int)P.x) + ", "
		+ to_string((int)P.y) + ", "
		+ to_string((int)P.z);
	GUI::Get()->RenderText(5, 35, 1, 1, 1, str);
}

D3DXMATRIX Context::View()
{
	return camera->GetMatrix();
}

D3DXMATRIX Context::GetProjectionMatrix()
{
	D3DXMATRIX proj;
	projection->GetMatrix(&proj);

	return proj;
}
