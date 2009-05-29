#ifndef _STATE_GUI_WRITEABlE_RECTANGLE_INTERFACE_H
#define _STATE_GUI_WRITEABlE_RECTANGLE_INTERFACE_H

#include "RectIfc.h"

#include <iostream>

namespace SGui
{

	// This is the interface of a read and writeable rectangle
	class WRectIfc : public RectIfc
	{
	public:


		// ------ Virtual interface ------

		virtual void setPos(Pos pos) = 0;
		virtual void setSize(Vec size) = 0;
		//virtual void setPos(Pos pos);
		//virtual void setSize(Vec size);

		
		// ----------------------------  None minimalistic functions ------------------------------

		// set center Pos
		void setCenterPos(Pos cPos);
		void setCenterX(int cx);
		void setCenterY(int cy);
				
		// inlines
		inline void setX(int x)										{ setPos(Pos(x, getY())); }
		inline void setY(int y)										{ setPos(Pos(getX(), y)); }
		inline void setWidth(int w)									{ setSize(Vec(w, getHeight())); }
		inline void setHeight(int h)								{ setSize(Vec(getWidth(), h)); }
		inline void setPos(int x, int y)							{ setPos(Pos(x, y)); }
		inline void setSize(int w, int h)							{ setSize(Vec(w, h)); }
		inline void setRect(const Rect &rect)						{ setPos(rect.getPos());
																	  setSize(rect.getSize()); }
		inline void setRect(const Pos &pos, const Vec &size)		{ setPos(pos);
																	  setSize(size); }
		inline void setRect(int x, int y, int w, int h)				{ setPos(x, y);
																	  setSize(w, h); }		
		inline void setCenterPos(int cx, int cy)					{ setCenterPos(Pos(cx, cy)); }
		inline void setLeft(int l)									{ setX(l); }
		inline void setRight(int r)									{ setX(r - getWidth()); }
		inline void setTop(int t)									
		{
			//std::cout << " this = " << this << "  ";
			//int tmp1 = getHeight();
			//int tmp2 = getSize().y;
			//Vec tmpVec1 = getSize();
			//int tmp3 = tmpVec1.y;
			//std::cout << " tmp1 = " << tmp1;
			//std::cout << " tmp2 = " << tmp2;
			//std::cout << " tmp3 = " << tmp3;
			setY(t - getHeight());
		}
		inline void setBottom(int b)								{ setY(b); }
		inline void setBottomRight(Pos br)							{ setPos(br.x - getWidth(), br.y); }
		inline void setTopRight(Pos tr)								{ setPos(tr - getSize()); }
		inline void setTopLeft(Pos tl)
		{
			//std::cout << 
			setPos(tl.x, tl.y - getHeight());
			//setPos(tl.x, tl.y);
		}
		inline void setBottomLeft(Pos bl)							{ setPos(bl); }

		// Updates this rectangle
		inline void intersectWith(const Rect &rect)
		{
			Rect tmpRect(getRect());
			tmpRect.intersectWith(rect);
			setRect(tmpRect);
		}
																  
	};
};

#endif