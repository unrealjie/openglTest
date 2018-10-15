#include<glew.h>
#include<wglew.h>
#include<GL/GL.h>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>

#define _CRT_SECURE_NO_WARNINGS

static TCHAR szClassName[] = TEXT("CLEAR");
static TCHAR szWindowName[] = TEXT("Clear");

LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);
static void OnCreate(HWND hWnd);
static void OnPaint(HWND hWnd);
static void OnDestroy(HWND hWnd);
static void OnSize(HWND hWnd, int nWidth, int nHeight);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);

HGLRC g_hGLRC;
GLuint g_vertexShader;
GLuint g_fragShader;
GLuint g_shaderProgram;
GLuint g_bufferObject;
GLuint g_vertexArrayObject;


static void LoadShaderSource(GLuint shader,const TCHAR* fileName) 
{

	FILE* fp = NULL;
	int size;
	char* buf;

	fp = fopen(fileName,"rb");
	fseek(fp,0,SEEK_END);
	size = ftell(fp);

	buf = (char*)malloc(size);
	fseek(fp,0,SEEK_SET);
	fread(buf,1,size,fp);

	glShaderSource(shader,1,(const GLchar**)&buf,&size);
	free(buf);
	fclose(fp);

}

static void DisplayCompileError(GLuint shader, HWND hWnd) 
{
	GLint compiled;
	int size;
	int len;
	char*buf;

	glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
	if (compiled == GL_FALSE) 
	{
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&size);
		if (size > 0) 
		{
			buf = (char*)malloc(size);
			glGetShaderInfoLog(shader,size,&len,buf);
			MessageBoxA(hWnd,buf,"Compile error !",MB_OK);
			free(buf);
		}
	}
	return;
}

static void DisplayLinkError(GLuint program,HWND hWnd) 
{
	GLint linked;
	int size;
	int len;
	char* buf;

	glGetProgramiv(program,GL_LINK_STATUS,&linked);
	if (linked == GL_FALSE) {
		glGetProgramiv(program,GL_INFO_LOG_LENGTH,&size);
		if (size > 0) 
		{
			buf = (char*)malloc(size);
			glGetProgramInfoLog(program,size,&len,buf);
			MessageBoxA(hWnd, buf, "Link error !", MB_OK);
			free(buf);
		}
	}

	return;
}

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

	const GLfloat colorsAndVertices[3][5] = {
		{1.0f,1.0f,0.0f,-0.5f,-0.5f},
		{1.0f, 1.0f, 0.0f, 0.5f, -0.5f},
		{1.0f,1.0f,0.0f,0.0f,0.5f},
	};


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
		WGL_CONTEXT_MAJOR_VERSION_ARB,3,
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

	wglMakeCurrent(hDC,g_hGLRC);

	g_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	LoadShaderSource(g_vertexShader,"c:\\shader\\Simple.vert");
	glCompileShader(g_vertexShader);
	DisplayCompileError(g_vertexShader,hWnd);

	g_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	LoadShaderSource(g_fragShader,"c:\\shader\\Frag.vert");
	glCompileShader(g_fragShader);
	DisplayCompileError(g_fragShader,hWnd);

	g_shaderProgram = glCreateProgram();
	glAttachShader(g_shaderProgram,g_vertexShader);
	glAttachShader(g_shaderProgram,g_fragShader);

	glDeleteShader(g_vertexShader);
	glDeleteShader(g_fragShader);
	glLinkProgram(g_shaderProgram);
	DisplayLinkError(g_shaderProgram,hWnd);

	glGenBuffers(1,&g_bufferObject);
	glBindBuffer(GL_ARRAY_BUFFER,g_bufferObject);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colorsAndVertices),colorsAndVertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	GLint colorLocation = glGetAttribLocation(g_shaderProgram, "Color");
	GLint vertexLocation = glGetAttribLocation(g_shaderProgram,"Vertex");

	glGenVertexArrays(1,&g_vertexArrayObject);
	glBindVertexArray(g_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER,g_bufferObject);
	glVertexAttribPointer(colorLocation,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),0);
	glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE,5*sizeof(GLfloat),(GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(vertexLocation);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	glDisableVertexAttribArray(glGetAttribLocation(g_shaderProgram,"Color"));
	glDisableVertexAttribArray(glGetAttribLocation(g_shaderProgram,"Vertex"));

	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.2f,1.0f);

	wglMakeCurrent(NULL, NULL);

	ReleaseDC(hWnd,hDC);
}

static void OnDestroy(HWND hWnd) 
{
	HDC hDC;
	hDC = GetDC(hWnd);
	wglMakeCurrent(hDC,g_hGLRC);
	glDeleteVertexArrays(1,&g_vertexArrayObject);
	glDeleteBuffers(1,&g_bufferObject);
	glDeleteProgram(g_shaderProgram);
	wglMakeCurrent(NULL,NULL);
	if (g_hGLRC != NULL) {
		wglDeleteContext(g_hGLRC);
	}
	ReleaseDC(hWnd,hDC);
}

static void OnPaint(HWND hWnd) {

	PAINTSTRUCT ps;
	HDC hDC;

	hDC = BeginPaint(hWnd,&ps);
	wglMakeCurrent(hDC,g_hGLRC);
	glClearColor(0.0f,0.0f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(g_shaderProgram);
	glBindVertexArray(g_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES,0,3);
	glBindVertexArray(0);
	glFlush();
	glUseProgram(0);


	SwapBuffers(hDC);
	wglMakeCurrent(NULL,NULL);

	EndPaint(hWnd,&ps);

}

static void OnSize(HWND hWnd, int nWidth, int nHeight) 
{
	HDC hDC;
	hDC = GetDC(hWnd);
	wglMakeCurrent(hDC, g_hGLRC);
	glViewport(0,0,nWidth,nHeight);
	wglMakeCurrent(NULL,NULL);
	ReleaseDC(hWnd,hDC);
	InvalidateRect(hWnd,NULL,NULL);
}

