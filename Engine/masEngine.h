#pragma once

#include "../Core/Common.h"
#include "../Core/Windows/masWindow.h"

class masEngine
{
private:
	masWindow Window;

private:
	LRESULT Internal_AppWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	MAS_CLASS_DISABLE_COPY_AND_MOVE_SEMANTIC(masEngine);

	masEngine(const wchar_t* title, u32 w, u32 h);
	~masEngine();

	void Run();

	// Input Functionality
	void OnKeyEvent(u32 vk_code, bool is_pressed);
};