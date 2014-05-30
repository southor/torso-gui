// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SGui\files.h"
#include "SGui\files_test.h"

//#ifdef _M_X64
	#include "WinWindow.h"
//#else
	#include "SDLWindow.h"
//#endif


#include "SGui\SGui.h"

#include <iostream>





int _tmain(int argc, _TCHAR* argv[])
{
	

	static const bool USE_SDL = false;

	std::cout << "sizeof(void*) = " << sizeof(void*) << std::endl;
	
	std::cout << "sizeof(char) = " << sizeof(char) << std::endl;
	std::cout << "sizeof(short) = " << sizeof(short) << std::endl;
	std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
	std::cout << "sizeof(long) = " << sizeof(long) << std::endl;
	std::cout << "sizeof(loing long) = " << sizeof(long long) << std::endl;
	
	std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
	std::cout << "sizeof(double) = " << sizeof(double) << std::endl;
	
	std::cout << "sizeof(__int8) = " << sizeof(__int8) << std::endl;
	std::cout << "sizeof(__int16) = " << sizeof(__int16) << std::endl;
	std::cout << "sizeof(__int32) = " << sizeof(__int32) << std::endl;
	std::cout << "sizeof(__int64) = " << sizeof(__int64) << std::endl;
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
		window = new SDLWindow;
	else
		window = new WinWindow;
	if (window->getWasError()) {
		delete window;
		return 0;
	}

	SGui::RenderContext *renderContext = window->getRenderContext();

	std::cout << "Test State Gui" << std::endl;
	SGui::testFiles(renderContext, L"../../../Test/graphics/fonts"); // TODO, maybe initing opengl should be done before testFiles, otherwise problems with texture ids might appear.

	SGui::initNamespace(window->getRenderContext());


	SGui::Font font(renderContext, L"../../../Test/graphics/fonts/arial");

	SGui::GraphState root;
	SGui::GraphState state1;
	SGui::GraphState state2;

	root.addChild(&state1);
	root.addChild(&state2);

	std::cout << "sizeof(root) = " << sizeof(SGui::State) << std::endl;


	SGui::Image imageBG(renderContext, L"../../../Test/graphics/bg.bmp", SGui::Pos(0, 0), SGui::Vec(window->getWidth(), window->getHeight()));
	//SGui::Image imageBG(font.getTxtrId(), SGui::Pos(0, 0), SGui::Vec(window.getWidth(), window.getHeight()));
	//SGui::Image imageBG("../Test/graphics/fonts/arial/image_.bmp", SGui::Pos(0, 0), SGui::Vec(window.getWidth(), window.getHeight()));
	root.renderObjs.push_back(&imageBG);

	SGui::Txtr arrowTxtr(SGui::Txtr::Pixel3(127, 64, 255), L"../../../Test/graphics/arrow-alpha.bmp");
	SGui::gl_uint arrowTxtrId = arrowTxtr.add(renderContext, L"../../../Test/graphics/arrow.bmp");
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



	SGui::Txtr windowTxtr(L"../../../Test/graphics/window.bmp", L"../../../Test/graphics/window-alpha.bmp");
	SGui::Image imageWindow(windowTxtr.add(renderContext, L"window.bmp"), SGui::Pos(0, 0), SGui::Vec(windowTxtr.getWidth(), windowTxtr.getHeight()));
	state1.renderObjs.push_back(&imageWindow);
	state1.WRectIfc::setPos(300, 100);
	//state1.setPos(300, 100);
	SGui::Box lineBox(SGui::Pos(340, 160) - state1.getPos(), SGui::Vec(150, 90), SGui::Color4f(0.0f, 1.0f, 1.0f, 0.5f), 1);
	SGui::TextBox textBox(lineBox.getPos() + SGui::Vec(1,1), lineBox.getSize() - SGui::Vec(2,2), &font, SGui::ALIGN_MIDDLE, SGui::ALIGN_TOP, true, "ett tva tre fyra fem sex/nsju/natta ~~nio ~uon.tio elva ~c00a0ff.tolv tretton ~uoff.fjorton femton sexton sjutton artan nitton tjugo");
	state1.renderObjs.push_back(&lineBox);
	state1.renderObjs.push_back(&textBox);

	SGui::Txtr largeTestTxtr(64, 64);
	SGui::Txtr colorsTxtr(L"../../../Test/graphics/colors.bmp");
	colorsTxtr.copyTo(&largeTestTxtr, 19, 32, true);
	SGui::Image imageTest(largeTestTxtr.add(renderContext, L"../../../Test/graphics/window.bmp"), SGui::Pos(20, 20), SGui::Vec(largeTestTxtr.getWidth(), largeTestTxtr.getHeight()));
	root.renderObjs.push_back(&imageTest);

	SGui::Txtr gronTxtr(L"../../../Test/graphics/gron.bmp");
	SGui::Image imageGron(gronTxtr.add(renderContext, L"gron.bmp"), SGui::Pos(100, 150), SGui::Vec(gronTxtr.getWidth(), gronTxtr.getHeight()));
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

