#ifndef _STATE_GUI_TEST_SDL_WINDOW_H_
#define _STATE_GUI_TEST_SDL_WINDOW_H_

#include "SGui\files.h"

#include "SGui\StateHndlr.h"

#include "External\GLRenderContext.h"

//#include "External\gl_includes.h"
#include "SDL.h"

class SDLWindow
{

	private:
		
		SDL_Surface *screen;		

		SGui::uint windowWidth;
		SGui::uint windowHeight;

		//SGui::Font *font;


		SGui::GLRenderContext renderContext;
		
		void init();
		
		/**
		 * @return returns true if a quit was performed
		 */
		bool pollEvents();

	public:

		int getError()		{ return 0; }

		SGui::StateHndlr stateHndlr;


		SGui::GLRenderContext* getRenderContext()		{ return &renderContext; }
		
		SDLWindow();

		~SDLWindow();

		SGui::uint getWidth()			{ return windowWidth; }

		SGui::uint getHeight()			{ return windowHeight; }

		void run();

		void render();

		inline float getFrameLength()	{ return 1.0f/100.0f; }		

};


#endif