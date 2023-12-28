#include "Framework.h"
#include "Window.h"

IExecute* Window::mainExecute = NULL;
HINSTANCE instance;

Window::Window(GRAPHICS_DESC desc)
{
	WNDCLASSEX wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.Instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	desc.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(),
		desc.AppName.c_str(),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		desc.Instance,
		NULL
	);

	Graphics::SetDesc(desc);

	RECT rect = { 0, 0, (LONG)desc.Width, (LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.Height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//x, y, width, height
	MoveWindow
	(
		desc.Handle,
		centerX, centerY,
		rect.right - rect.left, rect.bottom - rect.top,
		true
	);

	ShowWindow(desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.Handle);
	SetFocus(desc.Handle);

	ShowCursor(true);

	::instance = desc.Instance;
}

Window::~Window()
{
	auto desc = Graphics::GetDesc();
	DestroyWindow(desc.Handle);
	UnregisterClass(desc.AppName.c_str(), desc.Instance);
}

WPARAM Window::Run(IExecute* main)
{
	mainExecute = main;

	Graphics::Create();
	Mouse::Create();
	Keyboard::Create();

	Time::Create();
	Time::Get()->Start();

	GUI::Create();
	Context::Create();

	mainExecute->Initialize();

	MSG msg = { 0 };
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainRender();
		}
	}
	mainExecute->Destroy();

	Context::Delete();
	GUI::Delete();

	Time::Delete();

	Keyboard::Delete();
	Mouse::Delete();
	Graphics::Delete();

	return msg.wParam;
}

HWND handle;
LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->InputProc(message, wParam, lParam);
	GUI::Get()->MsgProc(handle, message, wParam, lParam);

	if (message == WM_CREATE) ::handle = handle;

	if (message == WM_SIZE)
	{
		if (mainExecute != NULL)
		{
			float width = (float)LOWORD(lParam);
			float height = (float)HIWORD(lParam);

			if (Graphics::Get() != NULL)
				Graphics::Get()->ResizeScreen(width, height);

			if (Context::Get() != NULL)
				Context::Get()->ResizeScreen();

			mainExecute->ResizeScreen();
		}
	}

	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void Window::MainRender()
{
	Time::Get()->Update();

	if (ImGui::IsMouseHoveringAnyWindow() == false)
	{
		Keyboard::Get()->Update();
		Mouse::Get()->Update();
	}

	GUI::Get()->Update();
	Context::Get()->Update();
	mainExecute->Update();

	mainExecute->PreRender();

	GRAPHICS_DESC desc = Graphics::GetDesc();

	Graphics::Get()->SetRenderTarget();
	Graphics::Get()->Clear(desc.Background);
	{
		Context::Get()->Render();

		mainExecute->Render();

		mainExecute->PostRender();
		GUI::Get()->Render();
	}
	Graphics::Get()->Present();
}
