#pragma once

#include "../Common.h"
#include "../Callback/masCallback.h"

MAS_DECLARE_CALLBACK_RET(TWndProcCallback, LRESULT, HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class masWindow
{
private:
	HWND       Handle;
	HINSTANCE  Instance;
	MSG        Msg;
	u32        Width;
	u32        Height;
	wchar_t   *Title;
	wchar_t   *WndClassName;
	bool       IsClosedFlag;


public:
	static TWndProcCallback WndProc;


public:
	MAS_CLASS_DISABLE_COPY_AND_MOVE_SEMANTIC(masWindow);

	masWindow(const wchar_t* title, u32 w, u32 h);
	~masWindow();

	bool IsClosed();
	void DispatchEvents();

	HWND           GetHandle();
	u32            GetWidth();
	u32            GetHeight();
	const wchar_t* GetTitle();
};