#ifndef _STATE_GUI_TEST_SDL_WINDOW_CPP_
#define _STATE_GUI_TEST_SDL_WINDOW_CPP_

#ifndef _M_X64

#include "SDLWindow.h"
#include "SGui\Txtr.h"
#include "SGui\macros.h"



SDLWindow::SDLWindow() : screen(nullptr), Window() //, font(nullptr)
{
	wasError = !init();
}

SDLWindow::~SDLWindow()
{
}

void SDLWindow::run()
{
	while(true)
	{
		if (pollEvents()) break;
		
		render();

		SDL_GL_SwapBuffers();
	}
}	

bool SDLWindow::pollEvents()
{
	SDL_Event event;
	bool quit = false;
	

	while(SDL_PollEvent(&event))
	{
	  switch(event.type)
	  {
		case SDL_KEYDOWN:
		{
		  switch(event.key.keysym.sym)
		  {
			case SDLK_LEFT:
				//mapRendererController.scrollLeft = true;
			  break;
			case SDLK_RIGHT:
				//mapRendererController.scrollRight = true;				  
			  break;
			case SDLK_UP:
				//mapRendererController.scrollUp = true;				  
			  break;
			case SDLK_DOWN:
				//mapRendererController.scrollDown = true;				  
			  break;
		  
			case SDLK_ESCAPE:
			  quit = true;
			  break;
              
			case SDLK_f:					
			  if (event.key.keysym.mod & KMOD_CTRL)
				SDL_WM_ToggleFullScreen(screen);
			  break;
              
			default:
			  break;
		  } // end switch
          
		  break;
		}
		case SDL_KEYUP:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:
					//mapRendererController.scrollLeft = false;
				  break;
				case SDLK_RIGHT:
					//mapRendererController.scrollRight = false;
				  break;
				case SDLK_UP:
					//mapRendererController.scrollUp = false;
				  break;
				case SDLK_DOWN:
					//mapRendererController.scrollDown = false;
				  break;
			}
		}
		break;
		case SDL_QUIT:
		  quit = true;
          
		default:
		  break;
          
	  } // end switch
	} // end while

	return quit;
}


bool SDLWindow::init()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Video initialization failed: %s\n",
			SDL_GetError( ) );
		SDL_Quit( );
	}
	SDL_WM_SetCaption("SGui Test", nullptr);
	
	unsigned int flags = SDL_HWSURFACE | SDL_OPENGL;
#ifndef _DEBUG
	//flags |= SDL_FULLSCREEN;
#endif
			
	SGui::uint &w = windowWidth = 640;
	SGui::uint &h = windowHeight = 480;
	unsigned int bpp = 32;	

	screen = SDL_SetVideoMode(w, h, bpp, flags);
	if (screen == 0)
	{
		rAssert(false);
		//throw EXCEPTION("Failed to set video mode");

		return false;
	}
	

	SGui::Color3f bgColor(0.3f, 0.3f, 0.5f);
	renderContext.initGL(w, h, bgColor);

	return true;
}

#endif

#endif