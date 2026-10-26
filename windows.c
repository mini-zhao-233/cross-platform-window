#include <windows.h>
#include "mini_window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//mini_window_t *
void mini_win_open(char *title, uint32_t height, uint32_t width)
{
	const char CLASS_NAME[] = "WindowsWindowClass";

	WNDCLASS wc = {
		.lpfnWndProc = WindowProc,
		.lpszClassName = CLASS_NAME,
		.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
		.hCursor = LoadCursor(NULL, IDC_ARROW)};

	if (!RegisterClass(&wc))
		return 1;

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		title,
		WS_OVERLAPPEDWINDOW,
		100, 100,
		height, width,
		NULL,
		NULL,
		NULL,
		NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, SW_NORMAL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

/* int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
} */

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
