#include "masEngine.h"



masEngine::masEngine(const wchar_t* title, u32 w, u32 h) :
	Window(title, w, h)
{
	Window.WndProc.BindMethod(this, &masEngine::Internal_AppWndProc);
}

masEngine::~masEngine()
{
}

void masEngine::Run()
{
	while(!Window.IsClosed())
	{
		Window.DispatchEvents();
	}
}

void masEngine::OnKeyEvent(u32 vk_code, bool is_pressed)
{
	printf("%u - %s\n", vk_code, is_pressed ? "TRUE" : "FALSE");
}

LRESULT masEngine::Internal_AppWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_KEYUP:
		OnKeyEvent(wparam, false);
		break;
	case WM_KEYDOWN:
		OnKeyEvent(wparam, true);
		break;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}
