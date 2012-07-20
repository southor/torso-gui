#ifndef _STATE_GUI_STATE_HANDLER_H_
#define _STATE_GUI_STATE_HANDLER_H_

#include "State.h"
#include "declares.h"
#include "Event.h"

#include <deque>

namespace SGui
{
	class StateHndlr
	{
	private:

		class StatePairArr
		{
		private:
			int nStates;
			State **arr;
		public:
			StatePairArr(int nStates);

			~StatePairArr();
			
			void insert(State *state1, State *state2, State *mapState);
			
			inline State* StateHndlr::StatePairArr::get(int stateId1, int stateId2)
			{
				return arr[stateId1 * nStates + stateId2];
			}

			State* get(State *state1, State *state2);
			
		};

		State *root;

		Pos mousePos;
		
		//struct StatePair
		//{
		//	State *State1;
		//	State *State2;

		//	StatePair(State *state1, State* state2) : state1(State1), state2(state2)  {}			
		//};

		//Hashtable<StatePair, State*> *commonFathers;

		StatePairArr *commonFathers;

		std::map<std::string, State*> stateNames; // map from name to state pointers


		void recFillCommonFathers(State *a, State *b, State *commonFather);

		void recFillCommonFathersCheck(State *a, State *b, State *commonFather);


		typedef std::deque<State*> ActiveStateLeaves;
		ActiveStateLeaves activeStateLeaves;



		// state handling

		void stateExitFrom(State *state);

		void stateExitTo(State *state, State *toState);

		// @return the state we entered from. (The lowest inactive state)
		State* stateEnterFrom(State *state);

		// enter states until it reaches the leaves of the tree
		void stateEnterTo(State *state);

		void addActiveStateLeaf(State *state)			{ activeStateLeaves.push_back(state); }

	public:
		
		StateHndlr();

		~StateHndlr();
		
		//static const int SET_IDS = 1;

		///**
		// * Sets up this StateHndlr to become the handler of the StateTree.
		// * If another state is added to the tree, this function must be called again,
		// * alternatevly updateStateTree can be called.
		// *
		// * @oaram flags SET_IDS: Sets all id's for the states, if not passed,
		// *				consistent id numbers should already been assigned.
		// */
		//void setStateTree(State *root, int flags = 0);

		/**
		 * Sets up this StateHndlr to become the handler of the StateTree.
		 * If another state is added to the tree, this function must be called again,
		 * alternatevly updateStateTree can be called.
		 */
		void setStateTree(State *root);

		inline bool hasStateTree()						{ return root != nullptr; }

		inline State* getState(int stateId)				{ return commonFathers->get(stateId, stateId); }

		// @Return nullptr if no State have been 
		State* getState(const std::string &name);

		State* getCommonFather(State *a, State *b)		{ State *state = commonFathers->get(a, b);
																		 dAssert(state);
																		 return state; }
		
		void enterState(State *state);

		void restartState(State *state);

		void exitTree();

		void enterState(int stateId);

		void restartState(int stateId);

		// Render
		void render(RenderContext *renderContext);

		

		/**
		 * @param mousePos position in global coordinates
		 * @indirect Set to true if the mouse button event is of the kind that has already
		 *			 hit an object which obscures this state tree.
		 */
		void handleMouseMoveEvent(const Pos &mousePos, bool indirect = false);

		inline void handleMouseButtonEvent(int mouseButtonEvent)
		{
			if (root) root->handleMouseButtonEvent(mouseButtonEvent);
		}

		inline void handleMouseButtonEvent(int mouseButtonEvent, const Pos &mousePos, bool indirect = false)
		{
			handleMouseMoveEvent(mousePos, indirect);
			handleMouseButtonEvent(mouseButtonEvent);			
		}

		//inline void handleClientEvent(int clientEvent, int arg, bool indirect = false)
		//{
		//	//if (root) root->handleClientEventRec(clientEvent, arg, indirect);
		//	if (root) root->handleClientEvent(clientEvent, arg, indirect);
		//}

		inline void handleClientEvent(const Event &ev, bool indirect = false)
		{
			//if (root) root->handleClientEventRec(clientEvent, arg, indirect);
			if (root) root->handleClientEvent(ev, indirect);
		}

		inline void handleEvent(const Event &ev, bool indirect = false)
		{
			switch(ev.generalType)
			{
			//case SGUI_NULL_EVENT:
			//	break;
			case SGUI_MOUSE_BUTTON_EVENT:
				handleMouseButtonEvent(ev.subType, ev.getArgAsPos(), indirect);
				break;
			case SGUI_MOUSE_MOVE_EVENT:
				handleMouseMoveEvent(ev.getArgAsPos(), indirect);
				break;
			default:
				//handleClientEvent(ev.generalType, ev.subType, indirect);
				handleClientEvent(ev, indirect);
				break;
			}
		}

	};

};

#endif