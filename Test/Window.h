#ifndef _STATE_GUI_TEST_WINDOW_H_
#define _STATE_GUI_TEST_WINDOW_H_

#include "files.h"

#include "StateHndlr.h"

#include "gl_includes.h"
#include "SDL.h"

class Window
{

	private:
		
		SDL_Surface *screen;		

		SGui::uint windowWidth;
		SGui::uint windowHeight;

		//SGui::Font *font;



		
		void init();
		
		/**
		 * @return returns true if a quit was performed
		 */
		bool pollEvents();

	public:

		SGui::StateHndlr stateHndlr;


		
		Window();

		~Window();

		SGui::uint getWidth()			{ return windowWidth; }

		SGui::uint getHeight()			{ return windowHeight; }

		void run();

		void render();

		inline float getFrameLength()	{ return 1.0f/100.0f; }		

};


#endif