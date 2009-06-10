#ifndef _STATE_GUI_TEST_WIN_WINDOW_H_
#define _STATE_GUI_TEST_WIN_WINDOW_H_

#include "Window.h"

#include "win_declares.h"


class WinWindow : public Window
{

	private:

		win_hwnd hwnd;
		
		win_handle hDC; // opengl specific
		win_handle hRC; // opengl specific
		
		bool init();
		void uninit();

	public:
		
		WinWindow();

		~WinWindow();

		virtual void run();

};


#endif