#ifndef _STATE_GUI_TEST_WIN_WINDOW_CPP_
#define _STATE_GUI_TEST_WIN_WINDOW_CPP_

#include "WinWindow.h"
#include "SGui\Txtr.h"
#include "SGui\macros.h"

#include "win_includes.h"

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
	wglMakeCurrent( NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}

WinWindow::WinWindow() : stateHndlr()//, font(NULL)
{
	
	
	error = init();

	//font = new SGui::Font("../Test/graphics/fonts/arial");
}

WinWindow::~WinWindow()
{
	//delete font;

	uninit();

}

void WinWindow::run()
{

	MSG Msg;

	//meassage loop
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		
		render();
		
		SwapBuffers((HDC)(hDC));
	}

}	

void WinWindow::render()
{
	renderContext.startNewRendering();
	stateHndlr.render(&renderContext);
	renderContext.flush();
}

// **************************************************************************************************************
// *------------------------------------------------------------------------------------------------------------*
// *--------------------------------------------- PRIVATE ------------------------------------------------------*
// *------------------------------------------------------------------------------------------------------------*
// **************************************************************************************************************


//bool WinWindow::pollEvents()
//{
//	SDL_Event event;
//	bool quit = false;
//	
//
//	while(SDL_PollEvent(&event))
//	{
//	  switch(event.type)
//	  {
//		case SDL_KEYDOWN:
//		{
//		  switch(event.key.keysym.sym)
//		  {
//			case SDLK_LEFT:
//				//mapRendererController.scrollLeft = true;
//			  break;
//			case SDLK_RIGHT:
//				//mapRendererController.scrollRight = true;				  
//			  break;
//			case SDLK_UP:
//				//mapRendererController.scrollUp = true;				  
//			  break;
//			case SDLK_DOWN:
//				//mapRendererController.scrollDown = true;				  
//			  break;
//		  
//			case SDLK_ESCAPE:
//			  quit = true;
//			  break;
//              
//			case SDLK_f:					
//			  if (event.key.keysym.mod & KMOD_CTRL)
//				SDL_WM_ToggleFullScreen(screen);
//			  break;
//              
//			default:
//			  break;
//		  } // end switch
//          
//		  break;
//		}
//		case SDL_KEYUP:
//		{
//			switch(event.key.keysym.sym)
//			{
//				case SDLK_LEFT:
//					//mapRendererController.scrollLeft = false;
//				  break;
//				case SDLK_RIGHT:
//					//mapRendererController.scrollRight = false;
//				  break;
//				case SDLK_UP:
//					//mapRendererController.scrollUp = false;
//				  break;
//				case SDLK_DOWN:
//					//mapRendererController.scrollDown = false;
//				  break;
//			}
//		}
//		break;
//		case SDL_QUIT:
//		  quit = true;
//          
//		default:
//		  break;
//          
//	  } // end switch
//	} // end while
//
//	return quit;
//}

WinWindow::error_t WinWindow::init()
{

	HINSTANCE hInstance = NULL;

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
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"window register failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return WINDOW_REGISTER_FAILED;
	}

	windowWidth = 640;
	windowHeight = 480;

	// creating window
	hwnd = (win_hwnd)CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, L"SGui Test",WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, L"window creation failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return WINDOW_CREATION_FAILED;
	}

	
	ShowWindow((HWND)hwnd, SW_SHOWNORMAL);

	EnableOpenGL((HWND)hwnd, (HDC*)&hDC, (HGLRC*)&hRC);
	

	renderContext.initGL(windowWidth, windowHeight);

	return NESTLA_TEST_NO_ERROR;

}

void WinWindow::uninit()
{

	DisableOpenGL((HWND)hwnd, (HDC)hDC, (HGLRC)hRC);

}

#endif