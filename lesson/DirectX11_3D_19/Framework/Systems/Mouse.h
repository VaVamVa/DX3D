#pragma once

#define MAX_INPUT_MOUSE 8

class Mouse : public Singleton<Mouse>
{
public:
	friend Singleton<Mouse>;

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);
	void Update();

	void SetHandle(HWND handle)	{ this->handle = handle; }

	bool Down(DWORD button)		   { return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN;	}
	bool Up(DWORD button)		   { return buttonMap[button] == BUTTON_INPUT_STATUS_UP; }
	bool Press(DWORD button)	   { return buttonMap[button] == BUTTON_INPUT_STATUS_PRESS; }
	bool DoubleClick(DWORD button) { return buttonMap[button] == BUTTON_INPUT_STATUS_DBLCLK; }

	D3DXVECTOR3 GetMoveValue() { return wheelMoveValue; }
	D3DXVECTOR3 GetPosition()  { return position; }

private:
	Mouse();
	~Mouse();

	static Mouse* instance;

	HWND handle;
	D3DXVECTOR3 position; //마우스 위치

	byte buttonStatus[MAX_INPUT_MOUSE];
	byte buttonOldStatus[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];

	D3DXVECTOR3 wheelStatus;
	D3DXVECTOR3 wheelOldStatus;
	D3DXVECTOR3 wheelMoveValue;

	DWORD timeDblClk;
	ULONGLONG startDblClk[MAX_INPUT_MOUSE];
	int buttonCount[MAX_INPUT_MOUSE];

public:
	enum
	{
		MOUSE_INPUT_LBUTTON = 0,
		MOUSE_INPUT_RBUTTON,
		MOUSE_INPUT_MBUTTON,
	};

	enum
	{
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_DBLCLK
	};
};
