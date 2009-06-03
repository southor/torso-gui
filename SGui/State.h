#ifndef _STATE_GUI_STATE_H_
#define _STATE_GUI_STATE_H_

#include "basic.h"
#include "Slot.h"
#include "ActionSurface.h"
#include "SGui.h"
#include "RenderContext.h"
#include "macros.h"


#include <vector>
#include <list>
#include <climits>
#include <string>


namespace SGui
{

	class StateHndlr;
	//class RenderContext;

	/**
	 * Different type of coordinates.
	 * Global coordinates: Global coordinates of the hole application, usually window or screen coordinates.
	 * Local Coordinates: Coordinates within the state.
	 * Parent Coordinates: Coordinates within the parent state. A child's parent coordinates is the parents local coordinates.
	 */
	class State : 
					public ConcreteWRectIfc
					//public Slot
	{
	private:

		// it's id
		PRI_R_MEMBER(int, id, Id);

		//name of the State, not necessarly used.
		PRI_R_MEMBER(std::string, name, Name);
		
		// The parentstate of this state.
		State *parent;
		
		// The childstates of this state
		typedef std::vector<State*> Children;
		Children children;

		// The children render list
		typedef std::list<State*> ChildrenRL;
		ChildrenRL childrenRL;
		typedef ChildrenRL::iterator ChildrenRLIter;		
		



		// True if this state is currenlty active.
		bool active;

		/**
		 * Used if this state is paralell. Used when exiting this state.
		 * Tells how many of the children that are still active.
		 */
		int childActivity;

		/**
		 * Used if this state is not paralell.
		 */
		State *activeChild;


		// Fast acccess to the render context for this state tree.
		RenderContext *renderContext;


		

		/**
		 * Is executed when a state is entered.
		 */
		virtual void enter() {}

		/**
		 * Is executed when a state is exited.
		 */
		virtual void exit()	{}

		//void exitFrom(StateHndlr *stateHndlr);
		//
		//void exitTo(StateHndlr *stateHndlr, State *state);

		///**
		// * Will enter from the highest active grandfather.
		// */
		//void enterFrom(StateHndlr *stateHndlr);

		//
		///**
		// * Will just enter the active child upwards too the leaf.
		// */
		//void enterTo(StateHndlr *stateHndlr);

		friend StateHndlr;
		
		// Only used by StateHndlr
		void executeExit();
		
		// Only used by StateHndlr
		void executeEnter();
		
		//State* getActiveChild()								{ return activeChild; }
		//int getChildActivity()								{ return childActivity; }

		// @param mousePos position of mouse in local coordinates
		bool handleMouseMoveEventState(const Pos &mousePos, bool indirect = false);

	public:

		typedef Children::iterator ChildrenIter;		
		typedef Children::const_iterator ChildrenConstIter;
		
		//// It's position relative to the parent (Parent coordinates)
		//Pos pos;



		//// clipping rectangle, in local coordinates
		//Rect clipRect;

		// If clipping should be activated or not
		bool clipping;

		/**
		 * Paralell state means activating this state
		 * activates all children too instead of only one.
		 */
		bool paralell;

		/**
		 * Tells if the members "enter" and "exit" should be
		 * called every time this state is entered and exited.
		 */
		bool callEnterExit;


		// ActionSurfaces
		typedef std::vector<ActionSurface> ActionSurfaces;
		ActionSurfaces actionSurfaces;


		//static const int ROOT_ID = 0;

		
		class TreeIter
		{
		private:
			/**
			 * When statesStack is empty then root is the current element.
			 * When root is NULL then this is an end iterator.		 
			 */
			State *root;			
			std::vector<ChildrenIter> statesStack;
			std::vector<ChildrenIter> endStack;
		public:

			/**
			 * Creates an iterator for the StatesTree.
			 * @param root The StatesTree
			 */
			TreeIter(State *root);
						
			// Creates an end iterator.			 
			TreeIter();

			TreeIter& operator++();
			State* operator*();
			TreeIter& operator=(TreeIter &stateTreeIter);
			bool operator==(TreeIter &stateTreeIter);
			bool operator!=(TreeIter &stateTreeIter);

		};

		
		///**
		// * Becomes a root object, but will be converted
		// * if added as a child to another state. The id of this state
		// * will always be zero as long as it stays as the root of the tree.
		// */
		//State();

		/**
		 * Becomes a root object, but will be converted
		 * if added as a child to another state. The id of this state
		 * will always be zero as long as it stays as the root of the tree.
		 * // @param renderContext The render context. Must be the same for all states in the same StateTree.
		 * @param name The name of the state. If used, it is another id for the state.
		 *			   If the empty string is passed, the state will have no name.
		 */
		State(std::string name = "");

		///**
		// * Becomes a root object, but will be converted
		// * if added as a child to another State.
		// * @param id The id that this state should have
		// */
		//State(int id);

		virtual ~State()				{}


		// ------------------------------ children ------------------------

		/**
		 * @param state Add a state to become a child of this state.
		 * @param id The id that this state should have, if zero is
		 * passed a new id will automaticly be generated for this state.
		 * This state will always keep it's id in this tree unless
		 * you specify any other state to have this id.
		 */
		void addChild(State *state, int id);

		/**
		 * @param state Add a state to become a child of this state.
		 * An id will automaticly be generated for this state.
		 */
		inline void addChild(State *state)
		{
			dAssert(state->id == 0);
			addChild(state, 0);		
		}

		/**
		 * @return Number of children
		 */
		inline int getNChildren() const				{ return static_cast<int>(children.size()); }
		
		// @return Returns the children begin iterator
		inline ChildrenIter childrenBegin()			{ return children.begin(); }

		// @return Returns the children end iterator
		inline ChildrenIter childrenEnd()			{ return children.end(); }

		//// @return Returns the children const begin iterator
		//inline ChildrenConstIter childrenBegin()	{ return children.begin(); }

		//// @return Returns the children const end iterator
		//inline ChildrenConstIter childrenEnd()		{ return children.end(); }


		bool isActive() const					{ return active; }


		static const int FIRST = 0;
		static const int LAST = INT_MAX;
		/**		 
		 * Sets the render order number that this state should have in the parent Child Render List.
		 * If this is the root state then nothing will happen.
		 * @param order The render order number that this state should have.
		 *				Can also be set to one of the flags FIRST, LAST.		 
		 */
		void setRenderOrder(int order);
		
		// @return True if this is a leaf, which means has no children.		
		inline bool isLeaf() const					{ return children.size() == 0; }

		//inline bool isActive() const				{ return active; }

		inline bool isRoot() const					{ return (parent == NULL); }

		//inline int getId() const					{ return id; }

		bool partOf(State *state);

		/**
		 * Get the used clip rect in local coordinates.
		 * @param clipRect  This clip rect should will be intersected with the usedClip and the result
							is stored back into the same clip rect. When passed this clip rect should be in 
							global coordinates but will be returned in local coordinates.						   
		 */
		void getUsedClipRect(Rect &clipRect);

		// ------------------------------ tree ------------------------

		// @return the root of this state tree.
		State* getRoot();

		// @return Number of states in the hole state tree.
		int getTreeSize();

		/**
		 * @return The begin iterator of the hole
		 * state tree that this state defines.
		 */
		inline TreeIter treeBegin()					{ return TreeIter(this); } 

		/**
		 * @return The end iterator of the hole
		 * state tree that this state defines.
		 */
		inline TreeIter treeEnd()					{ return TreeIter(); }

		/**
		 * First it calls renderState then it calls renderTree for all children
		 * of this state. The openGL matrix stack is used during rendering tree.
		 * @param parentGlobalPos The position of the parent in global coordinates.
		 * @param parentUsedClipRect The clip rectangle of the parent used in this case in parent coordinates.
		 */
		void renderTree(RenderContext *renderContext, const Pos &parentGlobalPos, const Rect &parentUsedClipRect);



		// ------------------------------ other -------------------------

		/**
		 * Renders only this state.
		 * @param clipRect The clipping rectangle of the caller.
		 */
		virtual void renderState(RenderContext *renderContext, const Rect &clipRect)						{}
		
		/**	
		 * @param parentGlobalPos The position of the parent in global coordinates.
		 * @param parentUsedClipRect The clip rectangle of the parent used in this case in parent coordinates.
		 * @param mouseEvent Can be any of the following:
					LEFT_MOUSE_DOWN, LEFT_MOUSE_UP, RIGHT_MOUSE_DOWN, RIGHT_MOUSE_UP, MOUSE_MOVEMENT
		 * @param indirect True if another action area has already been activated.
		 *				   Even if the action was filtered away it still counts as being activated.
		 * @param eventPos The position where a mouse action occured. (Local coordinates)
		 * @return True if a hit occured.
		 */
		//bool handleMouseEvent(const Pos &parentGlobalPos, const Rect &parentUsedClipRect, int mouseEvent, bool indirect, Pos eventPos);

		/**
		 * @param parentUsedClipRect Parent coordinates
		 * @param mousePos position of mouse in parent coordinates
		 * @indirect Set to true if the mouse button event is of the kind that has already
		 *			 hit an object which obscures this state tree.
		 */
		bool handleMouseMoveEvent(const Rect &parentUsedClipRect, Pos mousePos, bool indirect = false);

		void handleMouseButtonEvent(int mouseButtonEvent);

		/**
		 * @param clickSurfaceId The id of the click surface that was hit.
		 * @param actionPos The position within the clicksurface that the hit occured.
		 */
		//virtual void actionHit(int action, int actionSurfaceId, const Pos &actionPos);


		//debug
		bool isConsistent();
		bool recIsConsistent();


		

	};

};

#endif