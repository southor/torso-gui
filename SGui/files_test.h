#ifndef _STATE_GUI_FILES_TEST_H_
#define _STATE_GUI_FILES_TEST_H_

#include "files.h"

namespace SGui
{
	void testFiles(RenderContext *renderContext, const fschar *fontsPath)
	{

		std::cout << "sizeof(void*) = " << sizeof(void*) << std::endl;

		// ----------- testing State ------------
		
		State *state1 = new State();
		
		dAssert(state1->isConsistent());
		dAssert(state1->getNChildren() == 0);
		dAssert(state1->getTreeSize() == 1);

		State *state2 = new State();
		
		dAssert(state2->isConsistent());
		
		state1->addChild(state2);

		dAssert(state1->getNChildren() == 1);
		dAssert(state1->getTreeSize() == 2);
		dAssert(state2->getTreeSize() == 1);
		dAssert(state1->childrenBegin() != state1->childrenEnd());
		dAssert(*(state1->childrenBegin()) == state2);

		State *state3 = new State();

		state1->addChild(state3);

		dAssert(state1->getTreeSize() == 3);
		
		State::TreeIter iter = state1->treeBegin();
		
		dAssert(*iter == state2);
		++iter;
		dAssert(*iter == state3);
		++iter;
		dAssert(*iter == state1);
		++iter;
		dAssert(iter == state1->treeEnd());



		state2->setRenderOrder(1);
		state1->renderTree(renderContext, Pos(0, 0), Rect(-10000, -10000, 20000, 20000));


		// --------- testing StateHndlr ----------

		StateHndlr *stateHndlr = new StateHndlr();
		//stateHndlr->setStateTree(state1, StateHndlr::SET_IDS);
		stateHndlr->setStateTree(state1);

		dAssert(stateHndlr->getCommonFather(state1, state1) == state1);
		dAssert(stateHndlr->getCommonFather(state1, state2) == state1);
		dAssert(stateHndlr->getCommonFather(state1, state3) == state1);
		dAssert(stateHndlr->getCommonFather(state2, state2) == state2);
		dAssert(stateHndlr->getCommonFather(state2, state3) == state1);
		dAssert(stateHndlr->getCommonFather(state3, state3) == state3);



		// --------- testing Text ----------

		//Font font("../Test/graphics/fonts/arial");

		fsstring fontsPathStr(fontsPath);
		fsstring fontArialPathStr;

		if (fontsPathStr.length() > 0)
		{
			bool slash = (fontsPathStr[fontsPathStr.length()-1] == FSCHAR('/')) || (fontsPathStr[fontsPathStr.length()-1] == FSCHAR('\\'));
			fontArialPathStr = fontsPathStr + (slash ? FSSTRING("arial") : FSSTRING("/arial"));
		}
		else
		{
			fontArialPathStr = FSSTRING("arial");
		}
		
		Font font(renderContext, fontArialPathStr.c_str());

		Text text(&font, "hello world");
		dAssert(text.getNChars() == 10);


		// -------------- cleanup ---------------

		delete state1;
		delete state2;
		delete state3;
		delete stateHndlr;

	}
};

#endif
