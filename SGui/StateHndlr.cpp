#ifndef _STATE_GUI_STATE_HANDLER_CPP_
#define _STATE_GUI_STATE_HANDLER_CPP_

#include "StateHndlr.h"
#include "functions.h"
//#include "function_templates.h"
#include <limits>
#include <iostream>

// resolving LNK error
#include "function_templates.inl"

namespace SGui
{

	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------
	// -------------------------------------  StateHndlr::StatePairArr -----------------------------------
	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------

	StateHndlr::StatePairArr::StatePairArr(int nStates) : nStates(nStates)
	{
		dAssert(nStates >= 0);
		
		arr = new State*[nStates * nStates];
		zeroFun(arr, nStates * nStates);
	}

	StateHndlr::StatePairArr::~StatePairArr()
	{
		delete[] arr;
	}
	
	void StateHndlr::StatePairArr::insert(State *state1, State *state2, State *mapState)
	{
		dAssert(state1->isConsistent());
		dAssert(state2->isConsistent());
		dAssert(mapState->isConsistent());
				
		arr[state1->getId()*nStates + state2->getId()] = mapState;
		arr[state2->getId()*nStates + state1->getId()] = mapState;
	}
			
	State* StateHndlr::StatePairArr::get(State *state1, State *state2)
	{
		dAssert(state1->isConsistent());
		dAssert(state2->isConsistent());

		return get(state1->getId(), state2->getId());
	}

	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------
	// ------------------------------------------  StateHndlr --------------------------------------------
	// -------------------------------------------- private ----------------------------------------------
	// ---------------------------------------------------------------------------------------------------


	void StateHndlr::recFillCommonFathers(State *a, State *b, State *commonFather)
	{
		dAssert(a && b && commonFather);
		dAssert(commonFathers);
		
		if (commonFathers->get(a, b) == NULL)
		{

			commonFathers->insert(a, b, commonFather);

			State::ChildrenIter iterA = a->childrenBegin();
			State::ChildrenIter endA = a->childrenEnd();
			State::ChildrenIter iterB;
			State::ChildrenIter endB;
			State *childA;
			State *childB;
			for(; iterA != endA; ++iterA)
			{				
				childA = *iterA;
				iterB = b->childrenBegin();
				endB = b->childrenEnd();
				for( ; iterB != endB; ++iterB)
				{					
					childB = *iterB;
					recFillCommonFathersCheck(childA, childB, commonFather);
				}
				recFillCommonFathersCheck(childA, b, commonFather);
			}

			iterB = b->childrenBegin();
			endB = b->childrenEnd();
			for(; iterB != endB; ++iterB)
			{
				childB = *iterB;
				recFillCommonFathersCheck(a, childB, commonFather);
			}
		}
		else
		{
			dAssert(commonFathers->get(a, b) == commonFather);
		}
	}

	void StateHndlr::recFillCommonFathersCheck(State *a, State *b, State *commonFather)
	{
		State *storedCommonFather = commonFathers->get(a, b);
		
		if (a->partOf(b)) commonFather = b;
		else if (b->partOf(a)) commonFather = a;
		
		if (storedCommonFather == NULL)
			recFillCommonFathers(a, b, commonFather);
		else	
			dAssert(storedCommonFather == commonFather);
	}

	void StateHndlr::stateExitFrom(State *state)
	{
		dAssert(state->active);
		
		if (state->isLeaf())
		{
			addActiveStateLeaf(state);
		}
		else if (state->paralell)
		{
			State::ChildrenIter iter = state->childrenBegin();
			State::ChildrenIter end = state->childrenEnd();
			for(; iter != end; ++iter)
			{
				stateExitFrom(*iter);
			}
		}
		else
		{
			dAssert(state->activeChild);
			stateExitFrom(state->activeChild);			
		}

		state->executeExit();	
	}

	void StateHndlr::stateExitTo(State *state, State *toState)
	{
		dAssert(state->active); // TODO correct?
		
		if ((state != toState) && (state->childActivity == 0))
		{
			dAssert(state->parent);
			
			state->executeExit();
			stateExitTo(state->parent, toState);
		}
	}

	State* StateHndlr::stateEnterFrom(State *state)
	{
		if (state->active)
		{			
			if (state->activeChild)
			{				
				// this child is not active, but this is the default-active child
				
				/**
				 * Must be this case becuase otherwise the child would also
				 * been active and then this call should not have happen.
				 */
				dAssert(!state->paralell);

				stateEnterTo(state->activeChild);				
			}
			else
			{
				dAssert(state->isLeaf());
			}
			return state->activeChild;
			
		}
		else
		{
			if (state->parent)
			{
				// If the parent is a parlell state than this assignment has no meaning
				state->parent->activeChild = state;

				return stateEnterFrom(state->parent);
			}
			else
			{
				// This is the root state
				dAssert((state->childActivity == 0) || !state->paralell);

				stateEnterTo(state);

				return state;
			}
		}
	}


	void StateHndlr::stateEnterTo(State *state)
	{
		dAssert(!state->active);
		
		state->active = true;
		if (state->parent) ++(state->parent->childActivity);
		state->enter();

		if (state->isLeaf())
		{
			addActiveStateLeaf(state);
		}
		else if (state->paralell)
		{
			State::ChildrenIter iter = state->childrenBegin();
			State::ChildrenIter end = state->childrenEnd();
			for(; iter != end; ++iter)
			{
				stateEnterTo(*iter);
			}
		}
		else
		{
			dAssert(state->activeChild);
			stateEnterTo(state->activeChild);			
		}

	}

	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------
	// ------------------------------------------  StateHndlr --------------------------------------------
	// -------------------------------------------- public ----------------------------------------------
	// ---------------------------------------------------------------------------------------------------

	StateHndlr::StateHndlr() : root(NULL), commonFathers(NULL), stateNames(), activeStateLeaves()
	{
	}

	StateHndlr::~StateHndlr()
	{
		dAssert(activeStateLeaves.size() == 0); // TODO use exceptions
		if (commonFathers) delete commonFathers;
	}

	//void StateHndlr::setStateTree(State *root, int flags)
	void StateHndlr::setStateTree(State *root)
	{
		this->root = root;
		
		
		dAssert(root->recIsConsistent());
		//dAssert(!(flags & ~SET_IDS));
		//
		//// set id's
		//if (flags & SET_IDS)
		//{
		//	State::TreeIter stateTreeIter = root->treeBegin();
		//	State::TreeIter stateTreeEnd = root->treeEnd();

		//	for(int currentId = 0; stateTreeIter != stateTreeEnd; ++stateTreeIter)
		//	{
		//		//(*stateTreeIter)->setId(currentId++);
		//		(*stateTreeIter)->id = currentId++;
		//	}
		//}

		int nStates = root->getTreeSize();

		if (commonFathers) delete commonFathers;
		commonFathers = new StatePairArr(nStates);
		
		// Fill common fathers structure
		recFillCommonFathers(root, root, root);

		// Set name-id map strucure
		for(int stateId=0; stateId<nStates; ++stateId)
		{					
			State *state = getState(stateId);
			std::string stateName(state->getName());
			if (stateName != "")
			{
				std::pair<std::string, State*> pair(stateName, state);
				stateNames.insert(pair);
			}
		}


		dAssert(activeStateLeaves.size() == 0);
	}

	State* StateHndlr::getState(const std::string &name)
	{
		std::map<std::string, State*>::iterator it = stateNames.find(name);
		if (it == stateNames.end()) return NULL;
		else return it->second;
	}

	void StateHndlr::enterState(State *state)
	{
		dAssert(root);

		if (state->active == false)
		{

			if (activeStateLeaves.size() > 0)
			{

				State *startLeaf = activeStateLeaves.back();
				State *currentLeaf = activeStateLeaves.back();

				int size = static_cast<int>(activeStateLeaves.size());
				for(int i=0; i<size; ++i)
				{
					currentLeaf = activeStateLeaves.back();
					activeStateLeaves.pop_back();
					State *commonState = getCommonFather(state, currentLeaf);
					dAssert(commonState);
					if (commonState->paralell) activeStateLeaves.push_front(currentLeaf);
					//else currentLeaf->exitTo(this, commonState);
					else stateExitTo(currentLeaf, commonState);
									
					
				}
			}

			State *lowestInactiveState = stateEnterFrom(state);
			
			//// Get the used clip rect
			Rect clipRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX); //TODO use numeric (must get rid of evil min() macro first)
			//lowestInactiveState->getUsedClipRect(clipRect);
			//clipRect.setPos(clipRect.getPos() + lowestInactiveState->getPos()); // to parent coordinates
			//
			//dAssert(lowestInactiveState);
			//lowestInactiveState->handleMouseMoveEvent(clipRect, false, mousePos);

			
			root->handleMouseMoveEvent(clipRect, mousePos);
		}
	}

	void StateHndlr::restartState(State *state)
	{
		dAssert(root);

		stateExitFrom(state);
		
		int size = static_cast<int>(activeStateLeaves.size());
		for(int i=0; i<size; ++i)
		{
			State *currentLeaf = activeStateLeaves.front();
			activeStateLeaves.pop_front();
			stateEnterFrom(currentLeaf);
		}

		// Create a very large clipping rectangle
		Rect clipRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX); //TODO use numeric (must get rid of evil min() macro first)
		
		//state->getUsedClipRect(clipRect);
		//clipRect.setPos(clipRect.getPos() + lowestInactiveState->getPos()); // to parent coordinates
		
		root->handleMouseMoveEvent(clipRect, mousePos);
	}

	void StateHndlr::enterState(int stateId)
	{
		enterState(getState(stateId));
	}

	void StateHndlr::restartState(int stateId)
	{
		restartState(getState(stateId));
	}

	void StateHndlr::exitTree()
	{
		dAssert(root);
		//pln("exitTree: 15");
		
		//TODO correct? should we not pop back one at a time?
		ActiveStateLeaves::iterator iter = activeStateLeaves.begin();
		ActiveStateLeaves::iterator end = activeStateLeaves.end();		
		for(; iter != end; ++iter)
		{
			stateExitTo(*iter, root);
		}
		activeStateLeaves.clear(); //TODO correct to clear it?
		
		if (root->active)
		{
			root->exit();
			root->active = false;
		}
	}

	void StateHndlr::render(RenderContext *renderContext)
	{
		if (root)
		{
			Pos globalStartPos(0, 0);
			
			// Create a very large clipping rectangle
			Rect clipRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX); //TODO use numeric (must get rid of evil min() macro first)
			
			renderContext->setClipping(globalStartPos, clipRect);
			root->renderTree(renderContext, globalStartPos, clipRect);
		}
	}

	//void StateHndlr::render()
	//{		
	//	// Create a very large clipping rectangle
	//	Rect clipRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX); //TODO use numeric (must get rid of evil min() macro first)
	//	render(clipRect);
	//}

	void StateHndlr::handleMouseMoveEvent(const Pos &mousePos, bool indirect)
	{
		this->mousePos = mousePos;
		if (root)
		{
			// Create a very large clipping rectangle
			Rect clipRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX); //TODO use numeric (must get rid of evil min() macro first)
			root->handleMouseMoveEvent(clipRect, mousePos, indirect);
		}
	}

	
	
};

#endif