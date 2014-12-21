// Test.cpp : Defines the entry point for the console application.
//

#if defined _WIN32
#include "stdafx.h"
#endif

#include "SGui/files.h"
#include "SGui/files_test.h"

#ifdef _WIN32
#include "WinWindow.h"
#endif

#include "SDLWindow.h"


#include "SGui/SGui.h"

#include <iostream>




#if defined SGUI_VISUAL_STUDIO
int _tmain(int argc, _TCHAR* argv[])
#elif defined SGUI_GCC
int main(int argc, char* argv[])
#endif
{
	
#if defined _WIN32
	static const bool USE_SDL = false;
#else
	static const bool USE_SDL = true;
#endif

	rAssert(sizeof(SGui::fint) == sizeof(void*));

	std::cout << "sizeof(void*) = " << sizeof(void*) << std::endl;
	
	std::cout << "sizeof(char) = " << sizeof(char) << std::endl;
	std::cout << "sizeof(short) = " << sizeof(short) << std::endl;
	std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
	std::cout << "sizeof(long) = " << sizeof(long) << std::endl;
	std::cout << "sizeof(long long) = " << sizeof(long long) << std::endl;
	
	std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
	std::cout << "sizeof(double) = " << sizeof(double) << std::endl;
	
	std::cout << "sizeof(int8_t) = " << sizeof(int8_t) << std::endl;
	std::cout << "sizeof(int16_t) = " << sizeof(int16_t) << std::endl;
	std::cout << "sizeof(int32_t) = " << sizeof(int32_t) << std::endl;
	std::cout << "sizeof(int64_t) = " << sizeof(int64_t) << std::endl;
	std::cout << std::endl;
	std::cout << "sizeof(SGui::fint) = " << sizeof(SGui::fint) << std::endl;
	std::cout << "sizeof(SGui::ufint) = " << sizeof(SGui::ufint) << std::endl;
	std::cout << std::endl;
	std::cout << "sizeof(SGui::Font) = " << sizeof(SGui::Font) << std::endl;

	


	// opengl init, must be performed before init namespace because loaded opengl textures will be cleared/wasted by opengl, in newer versions.

//#ifdef _M_X64
//	WinWindow window;
//#else
//	SDLWindow window;
//#endif

	Window *window;
	if (USE_SDL)
	{
		window = new SDLWindow();
	}
	else
	{
#if defined _WIN32
		window = new WinWindow;
#else
		std::cout << "Error: Cannot create a WinWindow on a none-windows platform." << std::endl;
		return 0;
#endif
	}
	if (window->getWasError()) {
		delete window;
		return 0;
	}

	SGui::RenderContext *renderContext = window->getRenderContext();

	std::cout << "Test State Gui" << std::endl;
	SGui::testFiles(renderContext, FSSTRING("../../../Test/graphics/fonts")); // TODO, maybe initing opengl should be done before testFiles, otherwise problems with texture ids might appear.

	SGui::initNamespace(window->getRenderContext());


	SGui::Font font(renderContext, FSSTRING("../../../Test/graphics/fonts/arial"));

	SGui::ufint font_address = reinterpret_cast<SGui::ufint>(&font);
	std::cout << "font_address = " << font_address << std::endl;

	SGui::GraphState root;
	SGui::GraphState state1;
	SGui::GraphState state2;

	root.addChild(&state1);
	root.addChild(&state2);

	std::cout << "sizeof(root) = " << sizeof(SGui::State) << std::endl;


	SGui::Image imageBG(renderContext, FSSTRING("../../../Test/graphics/bg.bmp"), SGui::Pos(0, 0), SGui::Vec(window->getWidth(), window->getHeight()));
	//SGui::Image imageBG(font.getTxtrId(), SGui::Pos(0, 0), SGui::Vec(window.getWidth(), window.getHeight()));
	//SGui::Image imageBG("../Test/graphics/fonts/arial/image_.bmp", SGui::Pos(0, 0), SGui::Vec(window.getWidth(), window.getHeight()));
	root.renderObjs.push_back(&imageBG);

	SGui::Txtr arrowTxtr(SGui::Txtr::Pixel3(127, 64, 255), FSSTRING("../../../Test/graphics/arrow-alpha.bmp"));
	SGui::gl_uint arrowTxtrId = arrowTxtr.add(renderContext, FSSTRING("../../../Test/graphics/arrow.bmp"));
	//arrowTxtr.add("../Test/graphics/arrow.bmp");
	SGui::Image arrowDownImage(arrowTxtrId, SGui::Pos(100, 200), SGui::Vec(arrowTxtr.getWidth(), arrowTxtr.getHeight()));	
	SGui::Box scrollAreaBox(arrowDownImage.getTopLeft(), SGui::Vec(arrowDownImage.getWidth(), 100), SGui::Color4f(0.5f, 0.25f, 1.0f, 1.0f), 1);
	SGui::Box scrollerBox(scrollAreaBox.getPos() + SGui::Vec(2, 2), scrollAreaBox.getSize() - SGui::Vec(4, 35), SGui::Color4f(1.0f, 0.5f, 1.0f, 1.0f));
	SGui::Image arrowUpImage(arrowTxtrId, scrollAreaBox.getTopLeft(), SGui::Vec(arrowTxtr.getWidth(), arrowTxtr.getHeight()));
	arrowUpImage.rotate180();
	SGui::Box scrollBg(arrowDownImage.getBottomLeft(), SGui::Vec(arrowDownImage.getWidth(), arrowUpImage.getTop() - arrowDownImage.getBottom()), SGui::Color4f(0.8f, 0.8f, 0.8f, 1.0f));
	
	root.renderObjs.push_back(&scrollBg);
	root.renderObjs.push_back(&arrowDownImage);
	root.renderObjs.push_back(&scrollAreaBox);
	root.renderObjs.push_back(&scrollerBox);
	root.renderObjs.push_back(&arrowUpImage);



	SGui::Txtr windowTxtr(FSSTRING("../../../Test/graphics/window.bmp"), FSSTRING("../../../Test/graphics/window-alpha.bmp"));
	SGui::Image imageWindow(windowTxtr.add(renderContext, FSSTRING("window.bmp")), SGui::Pos(0, 0), SGui::Vec(windowTxtr.getWidth(), windowTxtr.getHeight()));
	state1.renderObjs.push_back(&imageWindow);
	state1.WRectIfc::setPos(300, 100);
	//state1.setPos(300, 100);
	SGui::Box lineBox(SGui::Pos(340, 160) - state1.getPos(), SGui::Vec(150, 90), SGui::Color4f(0.0f, 1.0f, 1.0f, 0.5f), 1);
	SGui::TextBox textBox(lineBox.getPos() + SGui::Vec(1,1), lineBox.getSize() - SGui::Vec(2,2), &font, SGui::ALIGN_MIDDLE, SGui::ALIGN_TOP, true, "ett tva tre fyra fem sex/nsju/natta ~~nio ~uon.tio elva ~c00a0ff.tolv tretton ~uoff.fjorton femton sexton sjutton artan nitton tjugo");
	state1.renderObjs.push_back(&lineBox);
	state1.renderObjs.push_back(&textBox);

	SGui::Txtr largeTestTxtr(64, 64);
	SGui::Txtr colorsTxtr(FSSTRING("../../../Test/graphics/colors.bmp"));
	colorsTxtr.copyTo(&largeTestTxtr, 19, 32, true);
	SGui::Image imageTest(largeTestTxtr.add(renderContext, FSSTRING("../../../Test/graphics/window.bmp")), SGui::Pos(20, 20), SGui::Vec(largeTestTxtr.getWidth(), largeTestTxtr.getHeight()));
	root.renderObjs.push_back(&imageTest);

	SGui::Txtr gronTxtr(FSSTRING("../../../Test/graphics/gron.bmp"));
	SGui::Image imageGron(gronTxtr.add(renderContext, FSSTRING("gron.bmp")), SGui::Pos(100, 150), SGui::Vec(gronTxtr.getWidth(), gronTxtr.getHeight()));
	state2.renderObjs.push_back(&imageGron);


	//window.stateHndlr.setStateTree(&root, SGui::StateHndlr::SET_IDS);
	window->stateHndlr.setStateTree(&root);
		
	
	//window.stateHndlr.enterState(&root, SGui::ActionSurface::getOutsidePos());
	//window.stateHndlr.restartState(&root, SGui::ActionSurface::getOutsidePos());
	window->stateHndlr.enterState(&root);
	window->stateHndlr.restartState(&root);
	//window.stateHndlr.enterState(&state2);
	


	//SGui::pln("test70");




	window->run();
	//SGui::pln("test75");
	window->stateHndlr.exitTree();

	//char a[32];
	//std::cin >> a;

	delete window;

	return 0;
}

