#include<windows.h>

static TCHAR szClassName[] = TEXT("clear");
static TCHAR szWindowName[] = TEXT("Clear");

LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);
static void OnCreate(HWND hWnd);
static void OnPaint(HWND hWnd);
static void OnDestroy(HWND hWnd);

int WINAPI WinMain(HINSTANCE hCurrInstance,HINSTANCE hPrevInstance,LPSTR szArgs,int nWinMode) {
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;
	int nResult;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hCurrInstance;
	wc.lpszClassName = szClassName;
	wc.lpfnWndProc = WindowProc;
	wc.style = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (RegisterClassEx(&wc)==0) 
	{
		return 0;
	}

	hWnd = CreateWindow(szClassName, szWindowName, WS_EX_OVERLAPPEDWINDOW | DCX_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hCurrInstance,
		NULL);
	if (hWnd == NULL) 
	{
		return 0;
	}

	ShowWindow(hWnd,nWinMode);
	UpdateWindow(hWnd);
	while (TRUE) 
	{
		nResult = GetMessage(&msg,NULL,0,0);
		if (nResult == -1 || nResult == 0) 
		{
			break;

		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam) {
	switch (nMessage) 
	{
	case WM_CREATE:
		OnCreate(hWnd);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_DESTROY:
		OnDestroy(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,nMessage,wParam,lParam);
	}
	return 0;
}