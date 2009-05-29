#ifndef _STATE_GUI_RECTANGLE_INTERFACE_H
#define _STATE_GUI_RECTANGLE_INTERFACE_H

#include "Rect.h"

#include <iostream>

namespace SGui
{

	// This is the interface of a readable rectangle
	class RectIfc
	{
	public:

		// ------ Virtual interface ------

		virtual Pos getPos() const = 0;
		virtual Vec getSize() const = 0;
		//virtual Pos getPos() const;
		//virtual Vec getSize() const;

		// ----------------------------  None minimalistic functions ------------------------------

		inline Rect getRect() const								{ return Rect(getPos(), getSize()); }

		inline int getX() const									{ return getPos().x; }
		inline int getY() const									{ return getPos().y; }
		inline int getWidth() const								{ return getSize().x; }
		inline int getHeight() const
		{
			//std::cout << " this = " << this << "   ";
			return getSize().y;
		}

		inline int getLeft() const								{ return getPos().x; }
		inline int getRight() const								{ return getPos().x + getSize().x; }
		inline int getBottom() const							{ return getPos().y; }
		inline int getTop() const								{ return getPos().y + getSize().y; }

		inline Pos getBottomRight() const						{ return Pos(getRight(), getBottom()); }
		inline Pos getTopRight() const							{ return getPos() + getSize(); }
		inline Pos getTopLeft() const							{ return Pos(getLeft(), getTop()); }		
		inline Pos getBottomLeft() const						{ return getPos(); }

		inline Pos getCenterPos() const							{ return getPos() + getSize() / 2; }		

		inline int getCenterX() const							{ return getPos().x + getSize().x / 2; }
		inline int getCenterY() const							{ return getPos().y + getSize().y / 2; }
		

		inline int area() const									{ getRect().area(); }

		inline bool empty()										{ Vec size(getSize());
																  return (size.x == 0) || (size.y == 0); }

		// -------------------  Interacting with other rectangles -----------------

		inline Rect intersection(const Rect &rect) const
		{
			Rect resultRect(getRect());
			resultRect.intersectWith(rect);
			return resultRect;
		}

		inline bool overlapping(const Rect &rect) const
		{
			Rect tmpRect(getRect());
			tmpRect.intersectWith(rect);
			return (tmpRect.area() > 0);
		}

		inline bool covering(const Pos &pos) const				{ return getRect().covering(pos); }

		// @return true if rect is completely inside this rectangle
		inline bool covering(const Rect &rect) const
		{
			Rect tmpRect(getRect());
			tmpRect.intersectWith(rect);
			return (tmpRect.area() == rect.area());
		}

		

		//// ----- Center Pos calculation function (helpers for other classes) -----
		//inline static Pos centerPosToPos(const Pos &centerPos, const Vec &size)		{ return centerPos - size / 2; }
		//inline static int centerNToN(int cn, int size)								{ return cn - size / 2; }
		//
		//// -- reusers of static helpers --
		//inline Pos centerPosToPos(const Pos &centerPos)								{ return centerPosToPos(centerPos, getSize()); }
		//inline int centerXToX(int cx, int size)										{ return centerNToN(cx, getWidth()); }
		//inline int centerXToX(int cy)												{ return centerNToN(cy, getHeight()); }



		

		//debug
		inline bool isConsistent() const				{ return (area() >= 0); }
	};
};

#endif