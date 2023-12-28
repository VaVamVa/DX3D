#include "stdafx.h"
#include "Main.h"
#include "Systems/Window.h"

#pragma region include Demo

#pragma endregion

void Main::Initialize()
{
	
}

void Main::Ready()
{

}

void Main::Destroy()
{
	for (IExecute* exe : executes)
	{
		exe->Destroy();
		SAFE_DELETE(exe);
	}
}

void Main::Update()
{
	for (IExecute* exe : executes)
		exe->Update();
}

void Main::PreRender()
{
	for (IExecute* exe : executes)
		exe->PreRender();
}

void Main::Render()
{
	for (IExecute* exe : executes)
		exe->Render();
}

void Main::PostRender()
{
	for (IExecute* exe : executes)
		exe->PostRender();
}

void Main::ResizeScreen()
{
	for (IExecute* exe : executes)
		exe->ResizeScreen();
}

void Main::Push(IExecute* execute)
{
	executes.push_back(execute);
	execute->Initialize();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	GRAPHICS_DESC desc;
	desc.AppName = L"DirectX11 3D";
	desc.Instance = instance;
	desc.bWindowed = true;
	desc.bVsync = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;
	desc.Background = DEFAULT_COLOR;
	Graphics::SetDesc(desc);

	Main* main = new Main();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(main);

	SAFE_DELETE(window);
	SAFE_DELETE(main);

	return wParam;
}