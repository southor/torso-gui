#ifndef _STATE_GUI_TEST_WINDOW_H_
#define _STATE_GUI_TEST_WINDOW_H_

#include "SGui\files.h"
#include "SGui\StateHndlr.h"

#include "SGuiExternal\GLRenderContext.h"

//#ifdef WIN32
//#pragma comment(lib, "SDL.lib")
//#pragma comment(lib, "SDLmain.lib")
//
////#pragma comment(lib, "SDL_net.lib")
//#endif

//#if defined _WIN32
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#endif
//
//#include "SDL.h"

class Window
{
protected:
	
	//SDL_Surface *screen;		

	SGui::uint32 windowWidth;
	SGui::uint32 windowHeight;

	PRO_R_MEMBER(bool, wasError, WasError);

	//SGui::Font *font;

	//virtual bool init() = 0;
	//virtual void uninit() = 0;


	SGui::GLRenderContext renderContext;
	
	///**
	// * @return returns true if a quit was performed
	// */
	//bool pollEvents();

	SGui::Pos toSGuiPos(SGui::int32 x, SGui::int32 y);

	void render();

public:

	SGui::StateHndlr stateHndlr;

	SGui::GLRenderContext* getRenderContext()		{ return &renderContext; }

	//SGui::TextBox *textBox;

	SGui::Pos mousePos;


	
	Window();

	virtual ~Window();

	SGui::uint getWidth()			{ return windowWidth; }

	SGui::uint getHeight()			{ return windowHeight; }

	virtual void run() = 0;

	inline float getFrameLength()	{ return 1.0f/100.0f; }

};


#endif