#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const char CLASS_NAME[] = "WindowsWindowClass";

	WNDCLASS wc = {
		.lpfnWndProc = WindowProc,
		.hInstance = hInstance,
		.lpszClassName = CLASS_NAME,
		.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
		.hCursor = LoadCursor(NULL, IDC_ARROW)};

	if (!RegisterClass(&wc))
		return 1;

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		"Windows Window",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

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
