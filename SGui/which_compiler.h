#ifndef _STATE_GUI_WHICH_COMPILER_H_
#define _STATE_GUI_WHICH_COMPILER_H_

#if defined(_MSC_VER)
#define SGUI_VISUAL_STUDIO
#elif defined(__GNUC__) || defined(__GNUG__)
#define SGUI_GCC
#else
SGui_unknown_compiler_error
#endif

#endif
