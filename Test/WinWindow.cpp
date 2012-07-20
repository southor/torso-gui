#ifndef _STATE_GUI_TEST_WIN_WINDOW_CPP_
#define _STATE_GUI_TEST_WIN_WINDOW_CPP_

#ifdef _M_X64

#include "WinWindow.h"
#include "SGui\Txtr.h"
#include "SGui\macros.h"

#include "SGuiExternal\win_includes.h"


//the window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
	break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	// get device context
	*hDC = GetDC(hwnd);

	// set the pixel format for DC
	ZeroMemory(&pfd, sizeof(pfd));	
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(*hDC, &pfd);
	SetPixelFormat(*hDC, iFormat, &pfd);

	//Create enable reder context (RC)
	*hRC = wglCreateContext(*hDC);
	wglMakeCurrent( *hDC, *hRC);

}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent( nullptr, nullptr);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}


WinWindow::WinWindow() : Window() //, font(nullptr)
{		
	wasError = !init();
}

WinWindow::~WinWindow()
{
	uninit();
}

void WinWindow::run()
{
	MSG Msg;

	//meassage loop
	while(GetMessage(&Msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		
		render();
		renderContext.flush();
		
		SwapBuffers((HDC)(hDC));
	}
}


bool WinWindow::init()
{

	HINSTANCE hInstance = GetModuleHandle(nullptr);

	wchar_t g_szClassName[] = L"myWindowClass\0";
	
	WNDCLASSEX wc;
	//HWND hwnd;
	//MSG Msg;

	//registrering the windows class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"window register failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	windowWidth = 640;
	windowHeight = 480;

	// creating window
	hwnd = (win_hwnd)CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, L"SGui Test",WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

	if(hwnd == nullptr)
	{
		MessageBox(nullptr, L"window creation failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	
	ShowWindow((HWND)hwnd, SW_SHOWNORMAL);

	EnableOpenGL((HWND)hwnd, (HDC*)&hDC, (HGLRC*)&hRC);
	

	SGui::Color3f bgColor(0.3f, 0.3f, 0.5f);
	renderContext.initGL(windowWidth, windowHeight, bgColor);

	return true;

}

void WinWindow::uninit()
{

	DisableOpenGL((HWND)hwnd, (HDC)hDC, (HGLRC)hRC);

}

#endif

#endif