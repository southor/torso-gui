#ifndef _STATE_GUI_GL_INCLUDES_H_
#define _STATE_GUI_GL_INCLUDES_H_

//#ifdef WIN32
//#pragma comment(lib, "SDL.lib")
//#pragma comment(lib, "SDLmain.lib")
////#pragma comment(lib, "SDL_net.lib")
//#endif

// TODO define win32 lean and mean? only for SDL?
#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#include "External\win_includes.h"
#endif


#include <GL/gl.h>
//#include <GL/glu.h>





#endif