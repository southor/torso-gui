// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "files.h"
#include "files_test.h"
#include "Window.h"
#include "SGui.h"

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	

	std::cout << "Test State Gui" << std::endl;
	SGui::testFiles("../Test/graphics/fonts"); // TODO, maybe initing opengl should be done before testFiles, otherwise problems with texture ids might appear.

	

	

	Window window; // opengl init, must be performed before init namespace because loaded opengl textures will be cleared/wasted by opengl, in newer versions.

	SGui::initNamespace();


	SGui::Font font("../Test/graphics/fonts/arial");

	SGui::GraphState root;
	SGui::GraphState state1;
	SGui::GraphState state2;

	root.addChild(&state1);
	root.addChild(&state2);

	std::cout << "sizeof(root) = " << sizeof(SGui::State) << std::endl;


	SGui::Image imageBG("../Test/graphics/bg.bmp", SGui::Pos(0, 0), SGui::Vec(window.getWidth(), window.getHeight()));
	//SGui::Image imageBG(font.getTxtrId(), SGui::Pos(0, 0), SGui::Vec(window.getWidth(), window.getHeight()));
	//SGui::Image imageBG("../Test/graphics/fonts/arial/image_.bmp", SGui::Pos(0, 0), SGui::Vec(window.getWidth(), window.getHeight()));
	root.renderObjs.push_back(&imageBG);

	SGui::Txtr arrowTxtr(SGui::Txtr::Pixel3(127, 64, 255), "../Test/graphics/arrow-alpha.bmp");
	GLuint arrowTxtrId = arrowTxtr.add("../Test/graphics/arrow.bmp");
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



	SGui::Txtr windowTxtr("../Test/graphics/window.bmp", "../Test/graphics/window-alpha.bmp");
	SGui::Image imageWindow(windowTxtr.add("window.bmp"), SGui::Pos(0, 0), SGui::Vec(windowTxtr.getWidth(), windowTxtr.getHeight()));
	state1.renderObjs.push_back(&imageWindow);
	state1.WRectIfc::setPos(300, 100);
	//state1.setPos(300, 100);
	SGui::Box lineBox(SGui::Pos(340, 160) - state1.getPos(), SGui::Vec(150, 90), SGui::Color4f(0.0f, 1.0f, 1.0f, 0.5f), 1);
	SGui::TextBox textBox(lineBox.getPos() + SGui::Vec(1,1), lineBox.getSize() - SGui::Vec(2,2), &font, SGui::ALIGN_MIDDLE, SGui::ALIGN_TOP, true, "ett tva tre fyra fem sex/nsju/natta ~~nio ~uon.tio elva ~c00a0ff.tolv tretton ~uoff.fjorton femton sexton sjutton artan nitton tjugo");
	state1.renderObjs.push_back(&lineBox);
	state1.renderObjs.push_back(&textBox);

	SGui::Txtr gronTxtr("../Test/graphics/gron.bmp");
	SGui::Image imageGron(gronTxtr.add("gron.bmp"), SGui::Pos(100, 150), SGui::Vec(gronTxtr.getWidth(), gronTxtr.getHeight()));
	state2.renderObjs.push_back(&imageGron);


	//window.stateHndlr.setStateTree(&root, SGui::StateHndlr::SET_IDS);
	window.stateHndlr.setStateTree(&root);
		
	
	//window.stateHndlr.enterState(&root, SGui::ActionSurface::getOutsidePos());
	//window.stateHndlr.restartState(&root, SGui::ActionSurface::getOutsidePos());
	window.stateHndlr.enterState(&root);
	window.stateHndlr.restartState(&root);
	//window.stateHndlr.enterState(&state2);
	


	//SGui::pln("test70");




	window.run();
	//SGui::pln("test75");
	window.stateHndlr.exitTree();

	//char a[32];
	//std::cin >> a;
	

	


	return 0;
}

