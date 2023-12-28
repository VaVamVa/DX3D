#pragma once

class Window
{
public:
	Window(GRAPHICS_DESC desc);
	~Window();

	WPARAM Run(class IExecute* main);

private:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	static void MainRender();

private:
	static class IExecute* mainExecute;
};