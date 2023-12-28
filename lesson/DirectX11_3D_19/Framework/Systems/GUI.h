#pragma once

struct GUI_TEXT
{
	GUI_TEXT() {}

	Vector2 Position;
	D3DXCOLOR Color;
	string Content;
};

class GUI : public Singleton<GUI>
{
public:
	friend Singleton<GUI>;

	LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void Update();
	void Render();

	void AddWidget(class Widget* widget);

	void RenderText(GUI_TEXT& text);
	void RenderText(float x, float y, string content);
	void RenderText(float x, float y, float r, float g, float b, string content);
	void RenderText(D3DXVECTOR2 position, D3DXCOLOR color, string content);

private:
	GUI();
	~GUI();

	void ApplyStyle();

private:
	vector<class Widget*> widgets;
	vector<GUI_TEXT> texts;
};