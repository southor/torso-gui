#ifndef _STATE_GUI_IMAGE_H
#define _STATE_GUI_IMAGE_H

#include "basic.h"
#include "Txtr.h"
#include "RenderObj.h"
#include "gl_declares.h"

#include "macros.h"

namespace SGui
{
	class Image : public RenderObj
	{
	protected:
		
				
		TxtrCoord txtrCoords[4];

		/**
		 * When true: setting position of image and the Texture will appear
		 * static on the screen instead of following the object.
		 */
		PRO_RW_MEMBER(bool, useFixedTxtr, UseFixedTxtr);

		// set position of image with the Texture apperaing static on the screen.
		void setPosFixedTxtr(const Pos &pos);
		void setSizeFixedTxtr(const Vec &size);

	public:
		

		gl_uint txtrId;

		enum Operation
		{
			MIRROR_X = 1,
			MIRROR_Y = 2,
			ROTATE_LEFT = 4,
			ROTATE_RIGHT = 8
		};
		static const int ALLOWED_OPERATIONS = MIRROR_X | MIRROR_Y | ROTATE_LEFT | ROTATE_RIGHT;

		Image();

		/**
		 * Will create Image and apply operation1 followed by
		 * operation2 on the texture coordinates.
		 * @param op1 Any operations on the texture coordinates. Will apply Mirrors followed by Rotations.
		 * @param op2 Any operations on the texture coordinates. Will apply Mirrors followed by Rotations.
		 */
		
		Image(gl_uint txtrId, Pos pos, Vec size, TxtrCoord posWithinTxtr, TxtrCoord sizeWithinTxtr, int operations1 = 0, int operations2 = 0);		
		Image(gl_uint txtrId, Pos pos, Vec size, int operations1 = 0, int operation2 = 0);

		Image(RenderContext *renderContext, const char *fileName, Pos pos, Vec size, TxtrCoord posWithinTxtr, TxtrCoord sizeWithinTxtr, int operations1 = 0, int operations2 = 0);
		Image(RenderContext *renderContext, const char *fileName, Pos pos, Vec size, int operations1 = 0, int operations2 = 0);


		
		
		void initTxtrCoords(TxtrCoord posWithinTxtr, TxtrCoord sizeWithinTxtr);
		void initTxtrCoords();

		
		void render(RenderContext *renderContext);

		
		//// set position of image with the Texture apperaing static on the screen.
		//void setPosFixedTxtr(const Pos &pos);
		//void setSizeFixedTxtr(const Vec &size);

		virtual void setPos(const Pos &pos);
		virtual void setSize(const Vec &size);


		// ------- Operation functions (only affects the txtrCoords member array) -------
		void mirrorX();
		void mirrorY();
		void rotateLeft();
		void rotateRight();
		
		// Will apply MIRRORS followed by ROTATIONS
		void applyOperations(int operations);

		// ------------- None miniminlistic functions -----------

		//void setCenterPosFixedTxtr(const Pos &cPos);
		//void setCenterXFixedTxtr(int cx);
		//void setCenterYFixedTxtr(int cy);

		// --------- inlines
		
		//inline void setXFixedTxtr(int x)									{ setPosFixedTxtr(Pos(x, getY())); }
		//inline void setYFixedTxtr(int y)									{ setPosFixedTxtr(Pos(getX(), y)); }
		//inline void setWidthFixedTxtr(int w)								{ setSizeFixedTxtr(Vec(w, getHeight())); }
		//inline void setHeightFixedTxtr(int h)								{ setSizeFixedTxtr(Vec(getWidth(), h)); }
		//inline void setPosFixedTxtr(int x, int y)							{ setPosFixedTxtr(Pos(x, y)); }
		//inline void setSizeFixedTxtr(int w, int h)							{ setSizeFixedTxtr(Vec(w, h)); }
		//inline void setRectFixedTxtr(const Rect &rect)						{ setPosFixedTxtr(rect.getPos());
		//																	  setSizeFixedTxtr(rect.getSize()); }
		//inline void setRectFixedTxtr(const Pos &pos, const Vec &size)		{ setRectFixedTxtr(Rect(pos, size)); }
		//inline void setRectFixedTxtr(int x, int y, int w, int h)			{ setRectFixedTxtr(Rect(x, y, w, h)); }

		inline void rotate180()												{ mirrorX(); mirrorY(); }		
		
		
		
		
	};
};

#endif