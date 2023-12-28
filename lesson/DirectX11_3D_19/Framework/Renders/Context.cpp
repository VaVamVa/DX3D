#include "Framework.h"
#include "Context.h"
#include "View/Viewport.h"
#include "View/Projection.h"

Context::Context()
{
	GRAPHICS_DESC desc = Graphics::GetDesc();

	projection = new Projection(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);

	position = D3DXVECTOR3(0, 0, -10);
	D3DXVECTOR3 forward(0, 0, 1);
	D3DXVECTOR3 right(1, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXVECTOR3 at = position + forward;

	D3DXMatrixLookAtLH(&view, &position, &at, &up);
}

Context::~Context()
{
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
	
}

void Context::Render()
{
	viewport->RSSetViewport();
}

D3DXMATRIX Context::GetProjectionMatrix()
{
	D3DXMATRIX proj;
	projection->GetMatrix(&proj);

	return proj;
}
