#ifndef _STATE_GUI_TEST_WINDOW_CPP_
#define _STATE_GUI_TEST_WINDOW_CPP_

#include "Window.h"
//#include "External\gl_includes.h"


Window::Window() : stateHndlr(), wasError(false) //, font(NULL)
{	
}

Window::~Window()
{	
}

void Window::render()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	renderContext.startNewRendering();
	stateHndlr.render(&renderContext);
}

// **************************************************************************************************************
// *------------------------------------------------------------------------------------------------------------*
// *--------------------------------------------- PRIVATE ------------------------------------------------------*
// *------------------------------------------------------------------------------------------------------------*
// **************************************************************************************************************


SGui::Pos Window::toSGuiPos(SGui::int32 x, SGui::int32 y)
{
	return SGui::Pos(x, windowHeight - y);
}



#endif