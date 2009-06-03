#ifndef _STATE_GUI_IMAGE_CPP
#define _STATE_GUI_IMAGE_CPP

#include "Image.h"

//#include "gl_includes.h"
 
namespace SGui
{

	Image::Image() : RenderObj(), txtrId(Txtr::getDefaultTxtrId())
	{
		initTxtrCoords();
	}

	Image::Image(gl_uint txtrId, Pos pos, Vec size, TxtrCoord posWithinTxtr, TxtrCoord sizeWithinTxtr, int operations1, int operations2)
		: RenderObj(pos, size), txtrId(txtrId), useFixedTxtr(false)
	{
		initTxtrCoords(posWithinTxtr, sizeWithinTxtr);
		applyOperations(operations1);
		applyOperations(operations2);
	}

	Image::Image(gl_uint txtrId, Pos pos, Vec size, int operations1, int operations2)
		: RenderObj(pos, size), txtrId(txtrId)
	{
		initTxtrCoords();
		applyOperations(operations1);
		applyOperations(operations2);
	}

	Image::Image(RenderContext *renderContext, const char *fileName, Pos pos, Vec size, TxtrCoord posWithinTxtr, TxtrCoord sizeWithinTxtr, int operations1, int operations2)
		: RenderObj(pos, size), txtrId(txtrId)
	{
		txtrId = Txtr::loadAdd(renderContext, fileName);
		initTxtrCoords(posWithinTxtr, sizeWithinTxtr);
		applyOperations(operations1);
		applyOperations(operations2);
	}

	Image::Image(RenderContext *renderContext, const char *fileName, Pos pos, Vec size, int operations1, int operations2)
		: RenderObj(pos, size), txtrId(0)
	{
		txtrId = Txtr::loadAdd(renderContext, fileName);
		initTxtrCoords();
		applyOperations(operations1);
		applyOperations(operations2);
	}



	void Image::initTxtrCoords(TxtrCoord posWithinTxtr, TxtrCoord sizeWithinTxtr)
	{
		txtrCoords[0] = TxtrCoord(posWithinTxtr.s + sizeWithinTxtr.s, posWithinTxtr.t);
		txtrCoords[1] = TxtrCoord(posWithinTxtr.s + sizeWithinTxtr.s, posWithinTxtr.t + sizeWithinTxtr.t);
		txtrCoords[2] = TxtrCoord(posWithinTxtr.s, posWithinTxtr.t + sizeWithinTxtr.t);
		txtrCoords[3] = TxtrCoord(posWithinTxtr.s, posWithinTxtr.t);
	}

	void Image::initTxtrCoords()
	{
		txtrCoords[0] = TxtrCoord(1.0f, 0.0f);
		txtrCoords[1] = TxtrCoord(1.0f, 1.0f);
		txtrCoords[2] = TxtrCoord(0.0f, 1.0f);
		txtrCoords[3] = TxtrCoord(0.0f, 0.0f);
	}



	void Image::render(RenderContext *renderContext)
	{
		//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, txtrId);
		//glBegin(GL_QUADS);
		//	glTexCoord2f(txtrCoords[0].s, txtrCoords[0].t);	glVertex2i((this->rect.pos.x + this->rect.size.x), this->rect.pos.y);
		//	glTexCoord2f(txtrCoords[1].s, txtrCoords[1].t);	glVertex2i((this->rect.pos.x + this->rect.size.x), (this->rect.pos.y + this->rect.size.y));
		//	glTexCoord2f(txtrCoords[2].s, txtrCoords[2].t);	glVertex2i(this->rect.pos.x, (this->rect.pos.y + this->rect.size.y));
		//	glTexCoord2f(txtrCoords[3].s, txtrCoords[3].t);	glVertex2i(this->rect.pos.x, this->rect.pos.y);
		//glEnd();

		//RenderContext *renderContext = getRenderContext();
		dAssert(renderContext);

		renderContext->renderTxtr(txtrId, this, txtrCoords);
	}

	void Image::setPos(const Pos &pos)
	{
		if (useFixedTxtr) setPosFixedTxtr(pos);
		else ConcreteWRectIfc::setPos(pos);
	}

	void Image::setSize(const Vec &size)
	{
		if (useFixedTxtr) setSizeFixedTxtr(size);
		else ConcreteWRectIfc::setSize(size);
	}

	void Image::setPosFixedTxtr(const Pos &pos)
	{
		//TODO size can be zero, check for division by zero.
		
		// s coordinates per x-pixel.
		Vecf sScale((txtrCoords[0].s - txtrCoords[3].s) / this->rect.size.x,
					(txtrCoords[2].s - txtrCoords[3].s) / this->rect.size.y); 
		
		// t coordinates per y-pixel.
		Vecf tScale((txtrCoords[0].t - txtrCoords[3].t) / this->rect.size.x,
					(txtrCoords[2].t - txtrCoords[3].t) / this->rect.size.y);

		Vec posDiff(pos - this->rect.pos);
		Vecf movement(static_cast<float>(posDiff.x), static_cast<float>(posDiff.y));
		float sDelta = movement.x * sScale.x + movement.y * sScale.y;
		float tDelta = movement.x * tScale.x + movement.y * tScale.y;
		
		// change texture coordinates
		for(int i=0; i<4; ++i)
		{
			txtrCoords[i].s += sDelta;
			txtrCoords[i].t += tDelta;
		}

		//setPos(pos);
		ConcreteWRectIfc::setPos(pos);
	}

	void Image::setSizeFixedTxtr(const Vec &size)
	{
		// s coordinates per x-pixel.
		Vecf sScale((txtrCoords[0].s - txtrCoords[3].s) / this->rect.size.x,
					(txtrCoords[2].s - txtrCoords[3].s) / this->rect.size.y); 
		
		// t coordinates per y-pixel.
		Vecf tScale((txtrCoords[0].t - txtrCoords[3].t) / this->rect.size.x,
					(txtrCoords[2].t - txtrCoords[3].t) / this->rect.size.y);

		Vec sizeDiff(size - this->rect.size);
		Vecf enlargement(static_cast<float>(sizeDiff.x), static_cast<float>(sizeDiff.y));
		float sDelta = enlargement.x * sScale.x + enlargement.y * sScale.y;
		float tDelta = enlargement.x * tScale.x + enlargement.y * tScale.y;

		//change texture coordinates
		txtrCoords[0].s += sDelta;
		txtrCoords[1].s += sDelta;
		txtrCoords[1].t += tDelta;
		txtrCoords[2].t += tDelta;


		//setSize(size);
		ConcreteWRectIfc::setSize(size);
	}

	void Image::mirrorX()
	{
		TxtrCoord tmp;		
		
		tmp = txtrCoords[3];
		txtrCoords[3] = txtrCoords[0]; 
		txtrCoords[0] = tmp;

		tmp = txtrCoords[2];
		txtrCoords[2] = txtrCoords[1];
		txtrCoords[1] = tmp;
	}

	void Image::mirrorY()
	{
		TxtrCoord tmp;
		
		tmp = txtrCoords[3];
		txtrCoords[3] = txtrCoords[2];
		txtrCoords[2] = tmp;

		tmp = txtrCoords[0];
		txtrCoords[0] = txtrCoords[1];
		txtrCoords[1] = tmp;
	}

	void Image::rotateLeft()
	{
		TxtrCoord tmp;

		tmp = txtrCoords[3];
		txtrCoords[3] = txtrCoords[2];
		txtrCoords[2] = txtrCoords[1];
		txtrCoords[1] = txtrCoords[0];
		txtrCoords[0] = tmp;
	}

	void Image::rotateRight()
	{
		TxtrCoord tmp;

		tmp = txtrCoords[3];
		txtrCoords[3] = txtrCoords[0];
		txtrCoords[0] = txtrCoords[1];
		txtrCoords[1] = txtrCoords[2];
		txtrCoords[2] = tmp;
	}

	void Image::applyOperations(int operations)
	{		
		dAssert(checkFlags(operations, ALLOWED_OPERATIONS));
		if (operations | MIRROR_X) mirrorX();
		else if (operations | MIRROR_Y) mirrorY();
		if (operations | ROTATE_LEFT) rotateLeft();
		else if (operations | ROTATE_RIGHT) rotateRight();
	}

	//void Image::setCenterPosFixedTxtr(const Pos &cPos)					{ setPosFixedTxtr(centerPosToPos(cPos)); }	
	//void Image::setCenterXFixedTxtr(int cx)								{ setXFixedTxtr(centerXToX(cx)); }
	//void Image::setCenterYFixedTxtr(int cy)								{ setYFixedTxtr(centerYToY(cx)); }

};

#endif