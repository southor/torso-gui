#ifndef _STATE_GUI_TEST_WIN_WINDOW_H_
#define _STATE_GUI_TEST_WIN_WINDOW_H_

#include "SGui\files.h"

#include "SGui\StateHndlr.h"

#include "External\GLRenderContext.h"

#include "win_declares.h"





class WinWindow
{

	private:

		enum error_t
		{
			NESTLA_TEST_NO_ERROR = 0,
			WINDOW_REGISTER_FAILED,
			WINDOW_CREATION_FAILED
		};
		PRI_R_MEMBER(int, error, Error);

		win_hwnd hwnd;
		
		win_handle hDC; // opengl specific
		win_handle hRC; // opengl specific

		SGui::uint windowWidth;
		SGui::uint windowHeight;

		//SGui::Font *font;


		SGui::GLRenderContext renderContext;
		
		error_t init();
		void uninit();
		
		///**
		// * @return returns true if a quit was performed
		// */
		//bool pollEvents();

	public:

		SGui::StateHndlr stateHndlr;


		SGui::GLRenderContext* getRenderContext()		{ return &renderContext; }
		
		WinWindow();

		~WinWindow();

		SGui::uint getWidth()			{ return windowWidth; }

		SGui::uint getHeight()			{ return windowHeight; }

		void run();

		void render();

		inline float getFrameLength()	{ return 1.0f/100.0f; }		

};


#endif