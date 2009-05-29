#ifndef _STATE_GUI_TEST_WINDOW_CPP_
#define _STATE_GUI_TEST_WINDOW_CPP_

#include "Window.h"


Window::Window() : screen(NULL), stateHndlr()//, font(NULL)
{
	init();

	//font = new SGui::Font("../Test/graphics/fonts/arial");
}

Window::~Window()
{
	//delete font;
}

void Window::run()
{
	bool running = true;
	while(running)
	{
		running = !pollEvents();
		
		render();




		SDL_GL_SwapBuffers();
	}
}	

void Window::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	stateHndlr.render();

	
	
	// test render some characters


	//SGui::Text text(font, "ett tva tre fyra fem sex/nsju/natta ~~nio ~uon.tio elva ~c00a0ff.tolv tretton ~uoff.fjorton femton sexton sjutton artan nitton tjugo");

	//float *vtxArr = new GLfloat[text.getVtxArrNFloats()];
	//float *colorArr = new GLfloat[text.getColorArrNFloats()];
	//float *txtrCoordArr = new GLfloat[text.getTxtrCoordArrNFloats()];
	//
	//glEnable(GL_TEXTURE_2D);	
	//glBindTexture(GL_TEXTURE_2D, font->getTxtrId());
	//glEnable(GL_TEXTURE_COORD_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, 0, txtrCoordArr);
	//glEnable(GL_COLOR_ARRAY);
	//glColorPointer(3, GL_FLOAT, 0, colorArr);
	//glVertexPointer(3, GL_FLOAT, 0, vtxArr);
	//



	//text.writeFieldToVtxArr(vtxArr, colorArr, txtrCoordArr, SGui::Pos(340, 160), SGui::Vec(150, 90));
	//glDrawArrays(GL_QUADS, 0, text.getVtxArrNVtx());




	//delete[] vtxArr;
	//delete[] colorArr;
	//delete[] txtrCoordArr; 

	//
	//
	//glDisable(GL_TEXTURE_COORD_ARRAY);
	//glDisable(GL_COLOR_ARRAY);
	//glColor3f(1.0f, 1.0f, 1.0f);
}

// **************************************************************************************************************
// *------------------------------------------------------------------------------------------------------------*
// *--------------------------------------------- PRIVATE ------------------------------------------------------*
// *------------------------------------------------------------------------------------------------------------*
// **************************************************************************************************************


bool Window::pollEvents()
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

void Window::init()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Video initialization failed: %s\n",
			SDL_GetError( ) );
		SDL_Quit( );
	}
	SDL_WM_SetCaption("SGui Test", NULL);
	
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
		assert(false);
		//throw EXCEPTION("Failed to set video mode");
	}
	

	glViewport(0, 0, w, h);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, static_cast<double>(w), 0.0, static_cast<double>(h), 0.5, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);



	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_VERTEX_ARRAY);	

	//glEnable(GL_TEXTURE_COORD_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, 0, txtrCoordArr);
	//glDrawElements(PRIMITIVE_TYPE_GL_DRAW_MODES[primitiveType], nInd, GL_UNSIGNED_INT, indArr);
	//glDisable(GL_TEXTURE_COORD_ARRAY);


	//glEnable(GL_COLOR_ARRAY);
	//glColorPointer(4, GL_FLOAT, 0, colorArr);				
	//glDrawArrays(PRIMITIVE_TYPE_GL_DRAW_MODES[primitiveType], 0, nVtx);
	//glDisable(GL_COLOR_ARRAY);
	
	glEnable(GL_SCISSOR_TEST);


}


#endif