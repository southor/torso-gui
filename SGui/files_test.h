#ifndef _STATE_GUI_FILES_TEST_H_
#define _STATE_GUI_FILES_TEST_H_

#include "files.h"

namespace SGui
{
	void testFiles()
	{
		// ----------- testing State ------------
		
		State *state1 = new State();
		
		assert(state1->isConsistent());
		assert(state1->getNChildren() == 0);
		assert(state1->getTreeSize() == 1);

		State *state2 = new State();
		
		assert(state2->isConsistent());
		
		state1->addChild(state2);

		assert(state1->getNChildren() == 1);
		assert(state1->getTreeSize() == 2);
		assert(state2->getTreeSize() == 1);
		assert(state1->childrenBegin() != state1->childrenEnd());
		assert(*(state1->childrenBegin()) == state2);

		State *state3 = new State();

		state1->addChild(state3);

		assert(state1->getTreeSize() == 3);
		
		State::TreeIter iter = state1->treeBegin();
		
		assert(*iter == state2);
		++iter;
		assert(*iter == state3);
		++iter;
		assert(*iter == state1);
		++iter;
		assert(iter == state1->treeEnd());



		state2->setRenderOrder(1);
		state1->renderTree(Pos(0, 0), Rect(-10000, -10000, 20000, 20000));


		// --------- testing StateHndlr ----------

		StateHndlr *stateHndlr = new StateHndlr();
		//stateHndlr->setStateTree(state1, StateHndlr::SET_IDS);
		stateHndlr->setStateTree(state1);

		assert(stateHndlr->getCommonFather(state1, state1) == state1);
		assert(stateHndlr->getCommonFather(state1, state2) == state1);
		assert(stateHndlr->getCommonFather(state1, state3) == state1);
		assert(stateHndlr->getCommonFather(state2, state2) == state2);
		assert(stateHndlr->getCommonFather(state2, state3) == state1);
		assert(stateHndlr->getCommonFather(state3, state3) == state3);



		// --------- testing Text ----------

		Font font("F:/Programering/C++/SGui/Test/graphics/fonts/arial");

		Text text(&font, "hello world");
		assert(text.getNChars() == 10);


		// -------------- cleanup ---------------

		delete state1;
		delete state2;
		delete state3;
		delete stateHndlr;

	}
};

#endif