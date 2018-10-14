#include<glew.h>
#include<wglew.h>
#include<GL/GL.h>
#include<windows.h>

static TCHAR szClassName[] = TEXT("CLEAR");
static TCHAR szWindowName[] = TEXT("Clear");

LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);
static void OnCreate(HWND hWnd);
static void OnPaint(HWND hWnd);
static void OnDestroy(HWND hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);

HGLRC g_hGLRC;

int WINAPI WinMain(HINSTANCE hCurrInstance,HINSTANCE hPrevInstance,LPSTR szArgs,int nWinMode) {
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc = {0};
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
	wc.lpszMenuName = NULL;
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

static void OnCreate(HWND hWnd) 
{
	HDC hDC;
	int nPfdID;
	BOOL bResult;
	HGLRC hGLRC;

	const PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,
		0,0,0,
		0,0,
		0,0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,
		0,
		0
	};
	const int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB,4,
		WGL_CONTEXT_MINOR_VERSION_ARB,0,
		WGL_CONTEXT_PROFILE_MASK_ARB,
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	hDC = GetDC(hWnd);

	nPfdID = ChoosePixelFormat(hDC,&pfd);
	if (nPfdID == 0) 
	{
		return;
	}

	bResult = SetPixelFormat(hDC,nPfdID,&pfd);
	if (bResult == FALSE) {
		return;
	}
	g_hGLRC = wglCreateContext(hDC);
	if (g_hGLRC == NULL) {
		return;
	}
	wglMakeCurrent(hDC,g_hGLRC);

	glewInit();
	hGLRC = wglCreateContextAttribsARB(hDC,0,attributes);
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(g_hGLRC);
	g_hGLRC = hGLRC;
	ReleaseDC(hWnd,hDC);
}

static void OnDestroy(HWND hWnd) 
{
	if (g_hGLRC != NULL) {
		wglDeleteContext(g_hGLRC);
	}
}

static void OnPaint(HWND hWnd) {

	PAINTSTRUCT ps;
	HDC hDC;

	hDC = BeginPaint(hWnd,&ps);
	wglMakeCurrent(hDC,g_hGLRC);
	glClearColor(0.0f,0.0f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers(hDC);
	wglMakeCurrent(NULL,NULL);

	EndPaint(hWnd,&ps);

}