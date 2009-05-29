#ifndef _STATE_GUI_RECTANGLE_H
#define _STATE_GUI_RECTANGLE_H

#include "basic.h"
#include "function_templates.h"

namespace SGui
{
	class Rect
	{
	public:

		Pos pos;
		Vec size;



		inline Rect()														{}

		inline Rect(Pos pos, Vec size) : pos(pos), size(size)				{}

		inline Rect(int x, int y, int w, int h) : pos(x, y), size(w, h)		{}


		// -----------------------------  Get functions  ---------------------------------

		inline const Pos& getPos() const						{ return pos; }
		inline const Vec& getSize() const						{ return size; }

		inline int getX() const									{ return pos.x; }
		inline int getY() const									{ return pos.y; }
		inline int getWidth() const								{ return size.x; }
		inline int getHeight() const							{ return size.y; }

		inline int getLeft() const								{ return pos.x; }
		inline int getRight() const								{ return pos.x + size.x; }
		inline int getBottom() const							{ return pos.y; }
		inline int getTop() const								{ return pos.y + size.y; }

		inline Pos getBottomRight() const						{ return Pos(getRight(), getBottom()); }
		inline Pos getTopRight() const							{ return pos + size; }
		inline Pos getTopLeft() const							{ return Pos(getLeft(), getTop()); }		
		inline Pos getBottomLeft() const						{ return pos; }

		inline Pos getCenterPos() const							{ return pos + size / 2; }		

		inline int getCenterX() const							{ return pos.x + size.x / 2; }
		inline int getCenterY() const							{ return pos.y + size.y / 2; }
		

		// -----------------------------  Set functions  ---------------------------------

		inline void setPos(const Pos &pos)						{ this->pos = pos; }

		inline void setSize(const Vec &size)					{ this->size = size; }

		// set center Pos
		inline void setCenterPos(Pos cPos)						{ this->pos = cPos - size / 2; }
		inline void setCenterX(int cx)							{ this->pos.x = cx - size.x / 2; }
		inline void setCenterY(int cy)							{ this->pos.y = cy - size.y / 2; }
				
		// inlines
		inline void setX(int x)									{ this->pos.x = x; }
		inline void setY(int y)									{ this->pos.y = y; }
		inline void setWidth(int w)								{ this->size.x = w; }
		inline void setHeight(int h)							{ this->size.y = h; }
		inline void setPos(int x, int y)						{ this->pos.x = x;
																  this->pos.y = y; }
		inline void setSize(int w, int h)						{ this->size.x = w;
																  this->size.y = h; }
		inline void setRect(const Pos &pos, const Vec &size)	{ this->pos = pos;
																  this->size = size; }
		inline void setRect(int x, int y, int w, int h)			{ setPos(x, y);
																  setSize(w, h); }
		inline void setCenterPos(int cx, int cy)				{ setCenterPos(Pos(cx, cy)); }

		inline void setLeft(int l)								{ this->pos.x = l; }
		inline void setRight(int r)								{ this->pos.x = r - size.x; }
		inline void setTop(int t)								{ this->pos.y = t - size.y; }
		inline void setBottom(int b)							{ this->pos.y = b; }
		inline void setBottomRight(Pos br)						{ setPos(br.x + getWidth(), br.y); }
		inline void setTopRight(Pos tr)							{ this->pos = tr - size; }
		inline void setTopLeft(Pos tl)							{ setPos(tl.x, tl.y + getHeight()); }
		inline void setBottomLeft(Pos bl)						{ this->pos = bl; }


		// -------------- Area info ------------

		int area() const;

		inline bool empty()										{ return (size.x == 0) || (size.y == 0); }

		// -------------------  Interacting with other rectangles -----------------

		// Updates this rectangle
		void intersectWith(const Rect &rect);

		inline Rect intersection(const Rect &rect) const
		{
			Rect resultRect(*this);
			resultRect.intersectWith(rect);
			return resultRect;
		}

		inline bool overlapping(const Rect &rect) const
		{
			Rect tmpRect(*this);
			tmpRect.intersectWith(rect);
			return (tmpRect.area() > 0);
		}

		inline bool covering(const Pos &pos) const
		{
			return ((pos.x >= this->pos.x)
				&& (pos.y >= this->pos.y)
				&& (pos.x < (this->pos.x + size.x))
				&& (pos.y < (this->pos.y + size.y)));
		}

		// @return true if rect is completely inside this rectangle
		inline bool covering(const Rect &rect) const
		{
			Rect tmpRect(*this);
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