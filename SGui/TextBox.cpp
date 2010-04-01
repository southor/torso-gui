#ifndef _STATE_GUI_TEXT_BOX_CPP_
#define _STATE_GUI_TEXT_BOX_CPP_

#include "TextBox.h"

//#include "gl_includes.h"

namespace SGui
{
	TextBox::TextBox() : RenderObj(), font(NULL), xAlign(ALIGN_LEFT), yAlign(ALIGN_TOP), textString(), autoUpdate(false), updateNeeded(true),
					nVtx(0), vtxArr(NULL), colorArr(NULL), txtrCoordArr(NULL)
	{
		updateVtxArrs();
	}

	TextBox::TextBox(const Pos &pos, const Vec &size, Font *font, int xAlign, int yAlgin, bool autoUpdate, const std::string &textString)
		: RenderObj(pos, size), font(font), xAlign(xAlign), yAlign(yAlgin), textString(textString), autoUpdate(autoUpdate),  updateNeeded(true),
		  nVtx(0), vtxArr(NULL), colorArr(NULL), txtrCoordArr(NULL)
	{
		//dAssert(checkFlags(xAlign, ALLOWED_X_ALIGNS));
		//dAssert(checkFlags(yAlign, ALLOWED_Y_ALIGNS));
		dAssert(checkAlternative(xAlign, N_X_ALIGNS));
		dAssert(checkAlternative(yAlign, N_Y_ALIGNS));
		
		updateVtxArrs();
	}

	TextBox::~TextBox()
	{
		if (nVtx > 0)
		{
			delete[] vtxArr;
			delete[] colorArr;
			delete[] txtrCoordArr;
		}
	}

	bool TextBox::updateVtxArrs()
	{						
		dAssert(isConsistent());
		
		if (nVtx > 0)
		{
			delete[] vtxArr;
			delete[] colorArr;
			delete[] txtrCoordArr;
		}
		
		if (font)
		{
			Text text(font, textString.c_str());
			
			nVtx = text.getVtxArrNVtx();
			if (nVtx > 0)
			{
				vtxArr = new gl_float[text.getVtxArrNFloats()];
				colorArr = new gl_float[text.getColorArrNFloats()];
				txtrCoordArr = new gl_float[text.getTxtrCoordArrNFloats()];
				text.writeFieldToVtxArr(vtxArr, colorArr, txtrCoordArr, getPos(), getSize(), xAlign, yAlign);
			}
		}
		else
		{
			nVtx = 0;
		}

		if (nVtx == 0)
		{
			vtxArr = NULL;
			colorArr = NULL;
			txtrCoordArr = NULL;
		}
		
		bool oldUpdateNeeded = updateNeeded;
		updateNeeded = false;
		return oldUpdateNeeded;
	}

	void TextBox::setPos(const Pos &pos)
	{
		if (pos != rect.pos)
		{
			rect.pos = pos;
			updateNeeded = true;
			if (autoUpdate) updateVtxArrs();				
		}
	}

	void TextBox::setSize(const Vec &size)
	{
		if (size != rect.size)
		{
			rect.size = size;
			updateNeeded = true;
			if (autoUpdate) updateVtxArrs();				
		}
	}

	void TextBox::setFont(Font *font)
	{
		if (font != this->font)
		{
			this->font = font;
			updateNeeded = true;
			if (autoUpdate) updateVtxArrs();				
		}
	}

	void TextBox::setTextString(const std::string &textString)
	{
		if (textString != this->textString)
		{
			this->textString = textString;
			updateNeeded = true;
			if (autoUpdate) updateVtxArrs();				
		}
	}	

	void TextBox::render(RenderContext *renderContext)
	{ 
		dAssert(!updateNeeded);

		//if (nVtx > 0)
		//{
		//	glEnable(GL_TEXTURE_2D);
		//	GLuint txtrId = font->getTxtrId();
		//	//std::cout << "txtrId = " << txtrId << std::endl;
		//	glBindTexture(GL_TEXTURE_2D, txtrId);
		//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//	glTexCoordPointer(2, GL_FLOAT, 0, txtrCoordArr);
		//	glEnableClientState(GL_COLOR_ARRAY);
		//	glColorPointer(3, GL_FLOAT, 0, colorArr);
		//	glVertexPointer(3, GL_FLOAT, 0, vtxArr);

		//	glDrawArrays(GL_QUADS, 0, nVtx);

		//	glDisable(GL_TEXTURE_COORD_ARRAY);
		//	glDisable(GL_COLOR_ARRAY);
		//	glColor3f(1.0f, 1.0f, 1.0f);
		//}

		//std::cout << "renderContext = " << renderContext << std::endl;
		dAssert(renderContext);

		renderContext->renderText(font->getTxtrId(), nVtx, vtxArr, colorArr, txtrCoordArr);	
		
	}

	bool TextBox::isConsistent()
	{
		if (nVtx == 0)
		{
			if (vtxArr || colorArr || txtrCoordArr) return false;
		}
		else
		{
			if (!(vtxArr && colorArr && txtrCoordArr)) return false;
		}

		return true;
	}

};

#endif