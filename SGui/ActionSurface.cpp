#ifndef STATE_GUI_ACTION_SURFACE_CPP
#define STATE_GUI_ACTION_SURFACE_CPP

#include "ActionSurface.h"

#include "basic_includes.h"

namespace SGui
{

	void ActionSurface::setGridEventFilter(int gridEvent1, int gridEvent2, int gridEvent3,
											int gridEvent4, int gridEvent5, int gridEvent6)	
	{
		this->gridEventFilter = TWO_TO_POWER_OF(gridEvent1) |
								TWO_TO_POWER_OF(gridEvent2) |
								TWO_TO_POWER_OF(gridEvent3) |
								TWO_TO_POWER_OF(gridEvent4) |
								TWO_TO_POWER_OF(gridEvent5) |
								TWO_TO_POWER_OF(gridEvent6);
	}

	//bool ActionSurface::hit(const Pos &eventPos, bool indirect) const
	//{
	//	if ((acceptIndirectEvents || !indirect)) return covering(pos);
	//	else return false;
	//}

	//bool ActionSurface::handleMouseEvent(State *state, int id, int mouseEvent, bool indirect, Pos eventPos)
	//{
	//	dAssert(checkFlags(mouseEvent, ALL_MOUSE_EVENTS));
	//	
	//	bool hit = (covering(eventPos) && (acceptIndirectEvents || !indirect));
	//	bool acceptsOverAwayEvents = (filter(MOUSE_OVER_TILE | MOUSE_AWAY_FROM_TILE) != 0);

	//	if (acceptsOverAwayEvents || (mouseEvent != MOUSE_MOVEMENT)) // A shortcut to save time
	//	{
	//		bool mouseWasInGrid = (mouseGridPos.x >= 0);
	//		Pos gridPos;

	//		if (hit)
	//		{
	//			eventPos -= pos; // to local coordinates
	//			gridPos = eventPos / gridRectSize;

	//			if (mouseEvent == MOUSE_MOVEMENT)
	//			{
	//				if ((gridPos != mouseGridPos) && (filter(MOUSE_OVER_TILE | MOUSE_AWAY_FROM_TILE) != 0))
	//				{
	//					if (!mouseWasInGrid)
	//					{
	//						//TODO add to global list of ActionSurfaces
	//						mouseOverSurfaces.insert(this);
	//					}
	//					
	//					if (eventReciever && filter(MOUSE_OVER_TILE))
	//					{
	//						eventReciever->recieveAction(state, id, MOUSE_OVER_TILE, mouseGridPos);
	//					}
	//				}
	//			}
	//			else
	//			{
	//				dAssert(checkFlags(mouseEvent, ALL_MOUSE_BUTTON_EVENTS)); // Only mouse button events should be left
	//				dAssert(checkFlags(ALL_MOUSE_BUTTON_EVENTS, ALL_GRID_EVENTS)); // Should be grid events
	//				
	//				int filteredGridEvent = filter(mouseEvent);
	//				if (eventReciever && filteredGridEvent)
	//				{
	//					eventReciever->recieveAction(state, id, filteredGridEvent, gridPos);
	//				}
	//			}

	//			return true;
	//		}
	//		else if (mouseWasInGrid)
	//		{	
	//			gridPos = mouseGridPos; // Store old grid position
	//			mouseGridPos.x = -1; // set it to "outside"
	//			
	//			// TODO Remove from global list of ActionSurfaces
	//			mouseOverSurfaces.erase(this);
	//			
	//			if (eventReciever && filter(MOUSE_AWAY_FROM_TILE))
	//			{					
	//				eventReciever->recieveAction(state, id, MOUSE_AWAY_FROM_TILE, mouseGridPos);
	//			}

	//			return false;
	//		}
	//	}

	//	return hit;
	//}

	//Pos ActionSurface::getPos() const											{ return rect.getPos(); }
	//
	//Vec ActionSurface::getSize() const											{ return rect.getSize(); }

	void ActionSurface::handleMouseButtonEvent(State *state, int id, int mouseButtonEvent)
	{
		dAssert(checkFlags(mouseButtonEvent, ALL_MOUSE_BUTTON_EVENTS_BITS));
		
		if (mouseIsOver())
		{
			if (eventReciever && accept(mouseButtonEvent))
			{
				GridEventInfo info(state, id, mouseButtonEvent, mouseGridPos);
				eventReciever->recieveEvent(info);
			}
		}
	}

	bool ActionSurface::handleMouseMoveEvent(State *state, int id, Pos mousePos, bool indirect)
	{		
		bool hit = (covering(mousePos) && (acceptIndirectEvents || !indirect));
		//bool acceptsOverAwayEvents = (filter(MOUSE_OVER_TILE | MOUSE_AWAY_FROM_TILE) != 0);

		//if (filter(MOUSE_OVER_TILE | MOUSE_AWAY_FROM_TILE) != 0) // A shortcut to save time
		//{

			if (hit)
			{
				mousePos -= this->rect.pos; // to local coordinates
				Pos newMouseGridPos = mousePos / gridRectSize;

				if (newMouseGridPos != mouseGridPos)
				{
					mouseGridPos = newMouseGridPos;
					//if (!mouseWasInGrid)
					//{
					//	//TODO add to global list of ActionSurfaces
					//	mouseOverSurfaces.insert(this);
					//}
					
					if (eventReciever && accept(MOUSE_OVER_TILE))
					{
						GridEventInfo info(state, id, MOUSE_OVER_TILE, newMouseGridPos);
						eventReciever->recieveEvent(info);
					}
				}


				return true;
			}
			else if (mouseIsOver())
			{
				Pos oldMouseGridPos = mouseGridPos; // Store old grid position
				mouseGridPos.x = -1; // set it to "outside"
				
				//// TODO Remove from global list of ActionSurfaces
				//mouseOverSurfaces.erase(this);
				
				if (eventReciever && accept(MOUSE_AWAY_FROM_TILE))
				{
					GridEventInfo info(state, id, MOUSE_AWAY_FROM_TILE, oldMouseGridPos);
					eventReciever->recieveEvent(info);
				}

				return false;
			}
		//}

		return hit;
	}
};

#endif