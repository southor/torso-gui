#ifndef _STATE_GUI_TEST_WINDOW_CPP_
#define _STATE_GUI_TEST_WINDOW_CPP_

#include "Window.h"
//#include "External\gl_includes.h"


Window::Window() : stateHndlr(), wasError(false) //, font(nullptr)
{	
}

Window::~Window()
{	
}

void Window::render()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//SGui::Color3f bgColor(0.3f, 0.3f, 0.5f);
	//renderContext.startNewRendering(bgColor);
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