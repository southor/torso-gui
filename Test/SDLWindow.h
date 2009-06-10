#ifndef _STATE_GUI_TEST_SDL_WINDOW_H_
#define _STATE_GUI_TEST_SDL_WINDOW_H_

#include "Window.h"

#include "SDL.h"


class SDLWindow : public Window
{

	private:
		
		SDL_Surface *screen;		
		
		bool init();
		
		/**
		 * @return returns true if a quit was performed
		 */
		bool pollEvents();

	public:
		
		SDLWindow();

		~SDLWindow();

		virtual void run();	

};


#endif