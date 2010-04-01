#ifndef _STATE_GUI_STATE_CPP_
#define _STATE_GUI_STATE_CPP_

#include "State.h"
#include "StateHndlr.h"

#include <algorithm>

//#include "gl_includes.h"
#include "RenderContext.h"

namespace SGui
{

	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------  State::TreeIter ------------------------------------------
	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------


	State::TreeIter::TreeIter(State *root) : root(root), statesStack(), endStack()
	{
		State *state = root;
		while (state->getNChildren() > 0)
		{
		
			ChildrenIter &current = state->childrenBegin();
			ChildrenIter &end = state->childrenEnd();

			statesStack.push_back(current);
			endStack.push_back(end);

			state = *current;
		}
	}

	State::TreeIter::TreeIter() : root(NULL), statesStack(), endStack()
	{
	}

	State::TreeIter& State::TreeIter::operator++()
	{
		if (statesStack.empty())
		{
			dAssert(root); // Is not allowed to call ++ if this is the end iterator.
			root = NULL;
		}
		else
		{					
			dAssert(statesStack.back() != endStack.back()); // We must be at an element

			++statesStack.back();
		
			while(statesStack.back() != endStack.back())
			{				
				State *state = *(statesStack.back());			
				statesStack.push_back(state->childrenBegin());
				endStack.push_back(state->childrenEnd());							
			}

			statesStack.pop_back();
			endStack.pop_back();				
			
		}
		return *this;
	}

	State* State::TreeIter::operator*()
	{
		if (statesStack.empty())
		{
			dAssert(root);
			return root;
		}
		else
		{
			return *(statesStack.back());
		}
	}

	State::TreeIter& State::TreeIter::operator=(State::TreeIter &stateTreeIter)
	{
		root = stateTreeIter.root;
		statesStack = stateTreeIter.statesStack;
		endStack = stateTreeIter.endStack;
		return *this;
	}

	bool State::TreeIter::operator==(TreeIter &stateTreeIter)
	{
		return ((root == stateTreeIter.root)
				&& (statesStack == stateTreeIter.statesStack)
				&& (endStack == stateTreeIter.endStack));
	}

	bool State::TreeIter::operator!=(TreeIter &stateTreeIter)
	{
		return ((root != stateTreeIter.root)
				|| (statesStack != stateTreeIter.statesStack)
				|| (endStack != stateTreeIter.endStack));
	}



	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------
	// ------------------------------------------- State -------------------------------------------------
	// ------------------------------------------ Private ------------------------------------------------
	// ---------------------------------------------------------------------------------------------------

	//void State::exitFrom(StateHndlr *stateHndlr)
	//{
	//	dAssert(active);
	//	
	//	if (isLeaf())
	//	{
	//		stateHndlr->addActiveStateLeaf(this);
	//	}
	//	else if (parallel)
	//	{
	//		ChildrenIter iter = childrenBegin();
	//		ChildrenIter end = childrenEnd();
	//		for(; iter != end; ++iter)
	//		{
	//			(*iter)->exitFrom(stateHndlr);
	//		}
	//	}
	//	else
	//	{
	//		dAssert(activeChild);
	//		activeChild->exitFrom(stateHndlr);			
	//	}

	//	exit();
	//	if (parent) --(parent->childActivity);
	//	active = false;		
	//}

	//void State::exitTo(StateHndlr *stateHndlr, State *state)
	//{
	//	dAssert(active); // TODO correct?
	//	
	//	if ((this != state) && (childActivity == 0))
	//	{
	//		dAssert(parent);
	//		
	//		exit();
	//		--(parent->childActivity);
	//		active = false;

	//		parent->exitTo(stateHndlr, state);
	//	}
	//}

	//void State::enterFrom(StateHndlr *stateHndlr)
	//{
	//	if (active)
	//	{			
	//		if (activeChild)
	//		{				
	//			/**
	//			 * Must be this case becuase otherwise the child would also
	//			 * been active and then this call should not have happen.
	//			 */
	//			dAssert(!parallel);

	//			activeChild->enterTo(stateHndlr);
	//		}
	//		else
	//		{
	//			dAssert(isLeaf());
	//		}
	//	}
	//	else
	//	{
	//		if (parent)
	//		{
	//			// If the parent is a parallel state than this assignment has no menaing
	//			parent->activeChild = this;

	//			parent->enterFrom(stateHndlr);
	//		}
	//		else
	//		{
	//			// This is the root state
	//			dAssert((childActivity == 0) || !parallel);

	//			enterTo(stateHndlr);
	//		}
	//	}
	//}


	//void State::enterTo(StateHndlr *stateHndlr)
	//{
	//	dAssert(!active);
	//	
	//	active = true;
	//	if (parent) ++(parent->childActivity);
	//	enter();

	//	if (isLeaf())
	//	{
	//		stateHndlr->addActiveStateLeaf(this);
	//	}
	//	else if (parallel)
	//	{
	//		ChildrenIter iter = childrenBegin();
	//		ChildrenIter end = childrenEnd();
	//		for(; iter != end; ++iter)
	//		{
	//			(*iter)->enterTo(stateHndlr);
	//		}
	//	}
	//	else
	//	{
	//		dAssert(activeChild);
	//		activeChild->enterTo(stateHndlr);			
	//	}

	//}

	void State::executeExit()
	{
		handleMouseMoveEventState(ActionSurface::getOutsidePos());
		if (callEnterExit) exit();
		if (parent) --(parent->childActivity);
		active = false;
	}
	
	void State::executeEnter()
	{
		active = true;
		if (parent) ++(parent->childActivity);
		if (callEnterExit) enter();		
	}

	bool State::handleMouseMoveEventState(const Pos &mousePos, bool indirect)
	{
		// action surfaces
		bool hitOccured = false;
		for(int actionSurfaceId = static_cast<int>(actionSurfaces.size()-1);
			(actionSurfaceId >= 0); --actionSurfaceId)
		{
			hitOccured = actionSurfaces[actionSurfaceId].handleMouseMoveEvent(this, actionSurfaceId, mousePos, hitOccured || indirect)
							|| hitOccured;
		}
		return hitOccured;
	}

	// ---------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------
	// ------------------------------------------- State -------------------------------------------------
	// ------------------------------------------- Public ------------------------------------------------
	// --------------------------------------------------------------------------------------------------

	State::State(std::string name) : 
					 ConcreteWRectIfc(0, 0, INT_MAX, INT_MAX),
					 //Slot(0, 0, INT_MAX, INT_MAX),
					 name(name), parent(NULL), children(), childrenRL(),
					 active(false), childActivity(0), activeChild(NULL),
					 renderContext(renderContext),
					 id(0), clipping(false), parallel(false),
					 callEnterExit(true), actionSurfaces()
	{
		//setSize(INT_MAX, INT_MAX);
		
		//Rect::setPos(0, 0); // do this?
		//Rect::setSize(INT_MAX, INT_MAX);
		
	}

	//State::State(int id) : parent(NULL), children(), childrenRL(), active(false), childActivity(0),
	//				 activeChild(NULL), Rect(0, 0, INT_MAX, INT_MAX), id(id), clipping(false),
	//				 parallel(false), actionSurfaces()
	//{}

	void State::addChild(State *state, int id)
	{
		dAssert(!this->active);
		dAssert(!state->active);	
		dAssert(state->isLeaf());
		
		State *root = getRoot();
		dAssert(root->getId() == 0);

		int greatestId = 0;
		TreeIter it = root->treeBegin();
		TreeIter end = root->treeEnd();		
		for(; it != end; ++it)
		{
			int &currId = (*it)->id;
			if (currId == id) // an id overlap
			{				
				for(; it != end; ++it) // find free id
				{
					int currId2 = (*it)->id;
					if (currId2 > greatestId) greatestId = currId2;
				}

				// solve id overlap
				if (id == 0)
				{
					id = greatestId + 1;
				}
				else
				{
					currId = greatestId + 1;					
				}
				break;
			}
			if (currId > greatestId) greatestId = currId;
		}

		// set the final id
		state->id = id;
		
		children.push_back(state);
		childrenRL.push_back(state);
		state->parent = this;

		if (!activeChild) activeChild = state;
	}

	void State::setRenderOrder(int order)
	{
		if (parent)
		{			
			parent->childrenRL.erase(std::find(parent->childrenRL.begin(),
									 parent->childrenRL.end(),
									 this));

			if (order == FIRST) parent->childrenRL.push_front(this);
			else if (order == LAST) parent->childrenRL.push_back(this);
			else if (order >= parent->getNChildren()-1) parent->childrenRL.push_back(this);
			else
			{
				ChildrenRLIter iter = parent->childrenRL.begin();
				ChildrenRLIter end = parent->childrenRL.end();				
				int count = 0;
				for(; iter != end; ++iter)
				{					
					if (count++ == order)
					{
						parent->childrenRL.insert(iter, this);
						return;
					}					
				}
				dAssert(false); // if reaching here something is wrong
			}
		}
	}

	void State::getUsedClipRect(Rect &clipRect)
	{
		if (parent) parent->getUsedClipRect(clipRect);		
		clipRect.intersectWith(this->getRect());
		clipRect.setPos(clipRect.getPos() - this->rect.pos); // Back to local coordinates again
	}

	State* State::getRoot()
	{
		if (isRoot()) return this;
		else return parent->getRoot();
	}

	bool State::partOf(State *state)
	{
		State *currState = this;
		while((currState != state) && (currState != NULL))
			currState = currState->parent;
		return (currState == state);
	}

	int State::getTreeSize()
	{
		int count = 1;

		ChildrenIter iter = childrenBegin();
		ChildrenIter end = childrenEnd();
		for(; iter != end; ++iter)
		{
			count += (*iter)->getTreeSize();
		}

		return count;
	}

	void State::renderTree(RenderContext *renderContext, const Pos &parentGlobalPos, const Rect &parentUsedClipRect)
	{
		if (active)
		{	
			//glPushMatrix();
			renderContext->pushMatrix();
				//glTranslatef(static_cast<float>(this->rect.pos.x), static_cast<float>(this->rect.pos.y), 0.0f);
				renderContext->translate(this->rect.pos);

				Rect usedClipRect(parentUsedClipRect);
				if (clipping)
				{
					usedClipRect.intersectWith(this->getRect());
					renderContext->setClipping(parentGlobalPos, usedClipRect);
				}
				usedClipRect.setPos(usedClipRect.getPos() - this->rect.pos); // convert from parent coordinates to local coordinates
				Pos globalPos(parentGlobalPos + this->rect.pos); // This states position in global coordinates

				if (!usedClipRect.empty())
				{
					renderState(renderContext, usedClipRect);

					if (parallel)
					{
						ChildrenRLIter iter = childrenRL.begin();
						ChildrenRLIter end = childrenRL.end();
						for(; iter != end; ++iter)
						{
							(*iter)->renderTree(renderContext, globalPos, usedClipRect);
						}
					}
					else if (activeChild)
					{
						activeChild->renderTree(renderContext, globalPos, usedClipRect);
					}
				}

				if (clipping)
				{
					renderContext->setClipping(parentGlobalPos, parentUsedClipRect);
				}

			//glPopMatrix();
			renderContext->popMatrix();
		}
	}

	//bool State::handleMouseEvent(const Pos &parentGlobalPos, const Rect &parentUsedClipRect, int mouseEvent, bool indirect, Pos eventPos)
	//{		
	//	bool hitOccured = false;

	//	Rect usedClipRect(parentUsedClipRect);
	//	if (clipping)
	//	{
	//		usedClipRect.intersectWith(*this);
	//		setClipping(parentGlobalPos, usedClipRect);
	//	}
	//	usedClipRect.setPos(usedClipRect.getPos() - pos); // convert from parent coordinates to local coordinates
	//	Pos globalPos(parentGlobalPos + pos); // This states position in global coordinates
	//	
	//	// Check children
	//	if (parallel)
	//	{
	//		ChildrenRL::reverse_iterator iter = childrenRL.rbegin();
	//		ChildrenRL::reverse_iterator end = childrenRL.rend();		
	//		State *child;
	//		for(; (iter != end); ++iter)
	//		{
	//			child = *iter;
	//			hitOccured = hitOccured || child->handleMouseEvent(globalPos, usedClipRect, mouseEvent, hitOccured || indirect, eventPos - child->pos);
	//		}
	//	}
	//	else
	//	{
	//		hitOccured = hitOccured || activeChild->handleMouseEvent(globalPos, usedClipRect, mouseEvent, hitOccured || indirect, eventPos - activeChild->pos);
	//	}

	//	// Check action surfaces
	//	int actionSurfaceId;
	//	for(actionSurfaceId = static_cast<int>(actionSurfaces.size()-1);
	//		(actionSurfaceId >= 0);
	//		--actionSurfaceId)
	//	{
	//		ActionSurface &actionSurface = actionSurfaces[actionSurfaceId];
	//		
	//		//if (actionSurface.hit(eventPos, hitOccured || indirect))
	//		//{
	//		hitOccured = hitOccured ||
	//			actionSurface.handleMouseEvent(this, actionSurfaceId, mouseEvent, indirect, eventPos);				
	//		//}
	//	}

	//	if (clipping)
	//	{
	//		setClipping(parentGlobalPos, parentUsedClipRect);
	//	}

	//	return hitOccured;
	//}

	bool State::handleMouseMoveEvent(const Rect &parentUsedClipRect, Pos mousePos, bool indirect)
	{	
		dAssert(active);

		bool hitOccured = false;

		Rect usedClipRect(parentUsedClipRect);
		if (clipping) usedClipRect.intersectWith(this->getRect());		
		
		if (/*usedClipRect.covering(mousePos)*/ true)
		{
			mousePos -= this->rect.pos; // To local coordinates

			// children
			if (parallel)
			{
				ChildrenRL::reverse_iterator iter = childrenRL.rbegin();
				ChildrenRL::reverse_iterator end = childrenRL.rend();		
				for(; (iter != end); ++iter)
				{
					hitOccured = (*iter)->handleMouseMoveEvent(usedClipRect, mousePos, hitOccured || indirect)
									|| hitOccured;
				}
			}
			else if (!isLeaf())
			{
				dAssert(activeChild);
				hitOccured = activeChild->handleMouseMoveEvent(usedClipRect, mousePos, hitOccured || indirect) 
								|| hitOccured;
			}

			hitOccured = handleMouseMoveEventState(mousePos, hitOccured || indirect)
							|| hitOccured;
		}

		return hitOccured;
	}

	void State::handleMouseButtonEvent(int mouseButtonEvent)
	{
		// children
		if (parallel)
		{
			ChildrenRL::reverse_iterator iter = childrenRL.rbegin();
			ChildrenRL::reverse_iterator end = childrenRL.rend();
			for(; (iter != end); ++iter)
			{
				(*iter)->handleMouseButtonEvent(mouseButtonEvent);
			}
		}
		else
		{
			if (activeChild != NULL) activeChild->handleMouseButtonEvent(mouseButtonEvent);
		}

		// action surfaces
		for(int actionSurfaceId = static_cast<int>(actionSurfaces.size()-1);
			(actionSurfaceId >= 0); --actionSurfaceId)
		{
			actionSurfaces[actionSurfaceId].handleMouseButtonEvent(this, actionSurfaceId, mouseButtonEvent);				
		}
	}

	//void State::actionHit(int action, int actionSurfaceId, const Pos &actionPos)
	//{
	//	if (eventReciever) eventReciever->recieveAction(this, action, actionSurfaceId, actionPos);
	//}

	void State::handleKlientEventRec(int klientEvent, int arg, bool indirect)
	{
		if (parallel)
		{
			ChildrenRL::reverse_iterator iter = childrenRL.rbegin();
			ChildrenRL::reverse_iterator end = childrenRL.rend();
			for(; (iter != end); ++iter)
			{
				(*iter)->handleKlientEventRec(klientEvent, arg, indirect);
			}
		}
		else
		{
			if (activeChild != NULL) activeChild->handleKlientEventRec(klientEvent, arg, indirect); 
		}

		handleKlientEvent(klientEvent, arg, indirect);
	}



	bool State::isConsistent()
	{
		// Only allow sizes that signed int can handle
		int nChildren = static_cast<int>(children.size());
		if ((nChildren < 0) || (nChildren != children.size())) return false;
		//if (ROOT_ID != 0) return false;

		if (parent)
		{
			if (active && !parent->active) return false;
			if (!parallel && childActivity > 1) return false;
			if (childActivity > getNChildren()) return false;			
		}
		else
		{
			// is root
			if (id != 0) return false;
		}
		
		if (activeChild)
		{
			if (std::find(childrenBegin(), childrenEnd(), activeChild) == childrenEnd()) return false;
		}
		else
		{
			if (getNChildren() > 0) return false;
		}
		
		return true;
	}
	
	bool State::recIsConsistent()
	{
		ChildrenIter iter = childrenBegin();
		ChildrenIter end = childrenEnd();
		for(; iter != end; ++iter)
		{
			if ((*iter)->recIsConsistent() == false) return false;
		}
		return isConsistent();
	}

};

#endif