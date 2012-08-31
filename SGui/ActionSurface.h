#ifndef _STATE_GUI_ACTION_SURFACE_H
#define _STATE_GUI_ACTION_SURFACE_H

#include "ConcreteRectIfc.h"
#include "EventReceiver.h"
#include <limits>
#include <set>

namespace SGui
{

	class State;

	class ActionSurface : public ConcreteRectIfc
	{
	private:
		//Rect rect;
		Vec gridRectSize;

		Pos mouseGridPos; // Tells where mouse is currently positioned within this action surface

		// Tells which grid events should be accepted.
		int gridEventFilter;

		//// all action surfaces that the mouse is "over"
		//static std::set<ActionSurface*> mouseOverSurfaces;

		//Event Reciver
		PRI_RW_MEMBER(EventReceiver*, eventReceiver, EventReceiver);

		static const int ALL_MOUSE_BUTTON_EVENTS_BITS = TWO_TO_POWER_OF(LEFT_MOUSE_DOWN) |
														TWO_TO_POWER_OF(LEFT_MOUSE_UP) |
														TWO_TO_POWER_OF(RIGHT_MOUSE_DOWN) |
														TWO_TO_POWER_OF(RIGHT_MOUSE_UP);
		static const int ALL_GRID_EVENTS_BITS = ALL_MOUSE_BUTTON_EVENTS_BITS |
														TWO_TO_POWER_OF(MOUSE_OVER_TILE) |
														TWO_TO_POWER_OF(MOUSE_AWAY_FROM_TILE);

		inline void setPos(Pos pos)					{ rect.setPos(pos); }

	public:


		//static const int ALL_EVENTS = ALL_MOUSE_EVENTS | ALL_GRID_EVENTS;

		
		
		static const int DEFAULT_GRID_EVENT_FILTER = ALL_GRID_EVENTS_BITS;
		
		
		
		
		



		/**
		 * Tells if this actionSurface should react when
		 * this surface is covered with other surfaces.
		 */
		bool acceptIndirectEvents;

		/**
		 * Creates an over all covering action surface
		 * which accepts all mouse button events. No action receiver.
		 * Grid with one grid rectangle for each pixel.
		 */
		ActionSurface() : ConcreteRectIfc(INT_MIN/2, INT_MIN/2, INT_MAX, INT_MAX), gridRectSize(1, 1),
							gridEventFilter(DEFAULT_GRID_EVENT_FILTER), eventReceiver(nullptr), mouseGridPos(-1, -1), acceptIndirectEvents(false)
		{}

		ActionSurface(const Pos &pos, const Vec &gridRectSize, const Vec &nGridRects,
						EventReceiver *eventReceiver = nullptr)
			: eventReceiver(eventReceiver), mouseGridPos(-1, -1), gridEventFilter(DEFAULT_GRID_EVENT_FILTER), acceptIndirectEvents(false)
		{
			//dAssert(checkFlags(gridEventFilter, ALL_GRID_EVENTS_BITS));			
			setPos(pos);
			setGrid(gridRectSize, nGridRects);
		}

		/**
		 * @param size The size of the action surface in pixels. Since gridRectSize
		 * will be equal to the size nGridRects will be (1, 1).
		 */
		ActionSurface(const Pos &pos, const Vec &size, EventReceiver *eventReceiver = nullptr)
			: ConcreteRectIfc(pos, size), gridRectSize(size), eventReceiver(eventReceiver), gridEventFilter(DEFAULT_GRID_EVENT_FILTER), acceptIndirectEvents(false)
		{
			//dAssert(checkFlags(gridEventFilter, ALL_GRID_EVENTS_BITS));
		}

		//inline int getGridEventFilter()									{ return gridEventFilter; }

		void setGridEventFilter(int gridEvent1=-1, int gridEvent2=-1, int gridEvent3=-1,
								int gridEvent4=-1, int gridEvent5=-1, int gridEvent6=-1);

		inline bool accept(int gridEvent)
		{
			return (gridEventFilter & TWO_TO_POWER_OF(gridEvent)) != 0;
		}

		/**
		 * @param eventPos position in parent coordinates
		 * @return true if there is a hit at this position.
		 */
		//bool hit(const Pos &eventPos, bool indirect) const;

		//inline bool acceptGridEvent(int gridEvent, bool indirect)		{ return filter(gridEvent) && (acceptIndirectEvents || !indirect); }
		//inline bool acceptEvent(int event, bool indirect)				{ return filter(mouseEvent) && (acceptIndirectEvents || !indirect); }

		/**
		 * @param id The id of this actionSurface
		 * @param eventPos position in parent coordinates
		 * @returns true if it was a hit
		 */
		//bool handleMouseEvent(State *state, int id, int mouseEvent, bool indirect, Pos eventPos);

		void handleMouseButtonEvent(State *state, int id, int mouseButtonEvent);

		bool handleMouseMoveEvent(State *state, int id, Pos mousePos, bool indirect);

		//inline void gridEventHit(State *state, int id, int gridEvent, const Pos &gridPos)
		//{
		//	int filteredGridEvent = filter(gridEvent);
		//	if (eventReceiver && filteredGridEvent) eventReceiver->recieveEvent(state, id, filteredGridEvent, gridPos);
		//}

		//Pos getPos() const;
		//Vec getSize() const;

		const Vec& getGridRectSize() const							{ return gridRectSize; }

		Vec getNGridRects() const									{ return getSize() / gridRectSize; }

		/**
		 * A local mouse grid position is stored within this object, to check if it's currently covering this
		 * object, call this function. To update this local information, call handleMouseMoveEvent member.
		 * @return true if the stored mouse position is over this object.
		 */
		inline bool mouseIsOver() const								{ return (mouseGridPos.x >= 0); }
				
		static inline Pos getOutsidePos()							{ return Pos(INT_MIN/2, INT_MIN/2); }

		

		void setGrid(const Vec &gridRectSize, const Vec &nGridRects)
		{
			this->gridRectSize = gridRectSize;
			rect.setSize(gridRectSize * nGridRects);
		}
		
		inline void setGridRectSize(const Vec &gridRectSize)
		{
			setGrid(gridRectSize, getNGridRects());
		}

		inline void setNGridRects(const Vec &nGridRects)
		{
			setGrid(gridRectSize, getNGridRects());
		}

		void setSize(Vec size)
		{			
			gridRectSize = size / getNGridRects();
			rect.setSize(size);
		}



		

	};
};

#endif

