#include "masWindow.h"

TWndProcCallback masWindow::WndProc;

static LRESULT CALLBACK Internal_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(masWindow::WndProc.IsBound())
	    return masWindow::WndProc.Exec(hwnd, msg, wparam, lparam);

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

masWindow::masWindow(const wchar_t* title, u32 w, u32 h)
{
	// SET TITLE BUFFER
	u32 title_len = lstrlenW(title);
	if(title_len)
		title_len++; // null terminator
	u64 title_size_in_byte = sizeof(wchar_t) * title_len;
	Title = (wchar_t*)malloc(title_size_in_byte);
	if(Title)
	{
		memset(Title, 0, title_size_in_byte);
		memcpy(Title, title, title_size_in_byte);
	}

	// SET WINDOW CLASS NAME BUFFER
	u32 postfix_len = lstrlenW(L"_WndClass");
	u64 postfix_size_in_byte = sizeof(wchar_t) * postfix_len;
	WndClassName = (wchar_t*)malloc(title_size_in_byte + postfix_size_in_byte);
	if(WndClassName)
	{
		memset(WndClassName, 0, title_size_in_byte + postfix_size_in_byte);
		memcpy(WndClassName, title, title_size_in_byte);
		memcpy(WndClassName + (title_len - 1), L"_WndClass", postfix_size_in_byte);
	}

	// INITIALIZE DATA MEMBERS
	memset(&Msg, 0, sizeof(MSG));
	Width        = w;
	Height       = h;
	Instance     = GetModuleHandle(NULL);
	IsClosedFlag = false;

	// WINDOW INSTANCE CLASS
	WNDCLASS wnd = { };
	wnd.lpfnWndProc   = &Internal_WndProc;
	wnd.hInstance     = Instance;
	wnd.lpszClassName = WndClassName;


	if(RegisterClass(&wnd) == 0)
		printf("%ls window couldn't be registered\n", WndClassName);

	Handle = CreateWindow(WndClassName, Title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, Width, Height, NULL, NULL, Instance, NULL);

	if(!Handle)
		printf("failed to create window %ls\n", Title);
	else
		ShowWindow(Handle, true);
}

masWindow::~masWindow()
{
	UnregisterClass(WndClassName, Instance);
	DestroyWindow(Handle);
	free(Title);
	free(WndClassName);

	Title        = NULL;
	WndClassName = NULL;
	Handle       = NULL;
	Instance     = NULL;
}

bool masWindow::IsClosed()
{
	return IsClosedFlag;
}

void masWindow::DispatchEvents()
{
	while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		if(Msg.message == WM_QUIT)
			IsClosedFlag = true;

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

HWND           masWindow::GetHandle() { return Handle; }
u32            masWindow::GetWidth()  { return Width;  }
u32            masWindow::GetHeight() { return Height; }
const wchar_t *masWindow::GetTitle()  { return Title;  }

