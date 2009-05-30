#ifndef _STATE_GUI_BOX_CPP
#define _STATE_GUI_BOX_CPP

#include "Box.h"

//#include "gl_includes.h"
#include "basic_includes.h"

#include "gl_includes.h"

namespace SGui
{

	Box::Box() : RenderObj(), /*filled(false)*/ lineWidth(0), color(0.0f, 1.0f), changed(false)
	{
		displayList = glGenLists(1);
		setDisplayList(GL_COMPILE);
	}

	Box::Box(const Pos &pos, const Vec &size, const Color4f &color, int lineWidth)
		: RenderObj(pos, size), /*filled(filled),*/ color(color), changed(false)
	{
		this->lineWidth = limit(lineWidth, 0, 255);
		displayList = glGenLists(1);
		setDisplayList(GL_COMPILE);
	}

	void Box::setDisplayList(GLenum mode)
	{
		assert(sizeof(GLint) == sizeof(int));
		
		glNewList(displayList, mode);			
			renderTo();
		glEndList();
	}

	void Box::setPos(Pos pos)							{ ConcreteWRectIfc::setPos(pos);
															//rect.pos = pos;
														  changed = true; }
		
	void Box::setSize(Vec size)							{ ConcreteWRectIfc::setSize(size);
															//rect.size = size;
														  changed = true; }
	
	void Box::renderTo()
	{
		GLfloat lineWidthf = this->lineWidth;
		
		// If border is too wide, the gl implementation might not have an appropriate linewidth range for it.
		// So check if we should render in "veryFatBorderMode" or not.
		
		GLfloat glLineWidthRange[2];
		glGetFloatv(GL_LINE_WIDTH_RANGE, glLineWidthRange);
		bool veryFatBorderMode = lineWidthf >= glLineWidthRange[1]; // get "high" part of the range

		// ------- Outer values ----------

		GLfloat cOX; // close outer X
		GLfloat fOX; // far outer X
		GLfloat cOY; // close outer Y
		GLfloat fOY; // far outer Y

		// Outer values are first copied from rectangle values 

		cOX = static_cast<GLfloat>(rect.getLeft());
		fOX = static_cast<GLfloat>(rect.getRight());
		cOY = static_cast<GLfloat>(rect.getBottom());
		fOY = static_cast<GLfloat>(rect.getTop());

		// ------- Inner values ----------		

		GLfloat cIX; // close inner X 		
		GLfloat fIX; // far inner X
		GLfloat cIY; // close inner Y 
		GLfloat fIY; // far inner Y

		
		GLfloat shrinkVal = veryFatBorderMode ? lineWidthf : (lineWidthf / 2.0f);

		// veryFatBorderMode == true :		Inner values will represent the rectangle inside of the border.
		//
		// veryFatBorderMode == false :		Inner values makes sure the border is drawn inside the box.
		//									Will represent the center of the lines (In none filled mode).

		cIX = cOX + shrinkVal;
		fIX = fOX - shrinkVal;
		cIY = cOY + shrinkVal;
		fIY = fOY - shrinkVal;

		if (veryFatBorderMode)
		{
			// to wide to be able to use lines

			// Inner values represents the rectangle inside of the border.
			glBegin(GL_QUADS);
				
				glColor4fv(color);

				// Right fat line

				glVertex2f(fOX, cOY); // bottom right
				glVertex2f(fOX, fOY); // top right
				glVertex2f(fIX, fOY); // top left
				glVertex2f(fIX, cOY); // bottom left

				// Top fat line

				glVertex2f(fOX, fIY); // bottom right
				glVertex2f(fOX, fOY); // top right
				glVertex2f(cOX, fOY); // top left
				glVertex2f(cOX, fIY); // bottom left

				// Left fat line

				glVertex2f(cIX, cOY); // bottom right
				glVertex2f(cIX, fOY); // top right
				glVertex2f(cOX, fOY); // top left
				glVertex2f(cOX, cOY); // bottom left

				// Bottom fat line

				glVertex2f(fOX, cOY); // bottom right
				glVertex2f(fOX, cIY); // top right
				glVertex2f(cOX, cIY); // top left
				glVertex2f(cOX, cOY); // bottom left
			
		}
		else
		{

			glLineWidth(lineWidthf);			

			if (lineWidth <= 1)
			{
				// We can optimize and use half of the vertexes in these cases.
				
				if (lineWidth == 0) glBegin(GL_QUADS); // Filled mode
				else glBegin(GL_LINE_LOOP); // lineWidth == 1

				// Only "inner" values are needed But the inner values are actually the real "outer" when lineWidth == 0

					glColor4fv(color);
					glVertex2f(fIX, cIY); // bottom right
					glVertex2f(fIX, fIY); // top right
					glVertex2f(cIX, fIY); // top left
					glVertex2f(cIX, cIY); // bottom left
			}
			else
			{

				// Now also apply shrink values for all outer values

				cOX += 0.5f;
				fOX -= 0.5f;
				cOY += 0.5f;
				fOY -= 0.5f;

				glBegin(GL_LINES); // lineWidth > 1

					glColor4fv(color);
					
					// bottom right to top right
					glVertex2f(fIX, cOY);
					glVertex2f(fIX, fOY);

					// top right to top left
					glVertex2f(fOX, fIY);
					glVertex2f(cOX, fIY);

					// top left to bottom left
					glVertex2f(cIX, fOY);
					glVertex2f(cIX, cOY);

					// bottom left to bottom right
					glVertex2f(cOX, cIY);
					glVertex2f(fOX, cIY);
			}			
		}

		glEnd();
		
		//
		//
		//Vecf posf(static_cast<float>(this->rect.pos.x), static_cast<float>(this->rect.pos.y));
		//Vecf sizef(static_cast<float>(this->rect.size.x), static_cast<float>(this->rect.size.y));
		//
		//float shrinkVal;
		////if (filled)
		//if (lineWidth == 0)
		//{
		//	shrinkVal = 0.0f;
		//	glBegin(GL_QUADS);
		//}
		//else
		//{
		//	float lineWidthf = static_cast<float>(lineWidth);
		//	shrinkVal = lineWidthf / 2.0f;

		//	if (lineWidth > 1)
		//	{
		//		glColor4fv(color);
		//		glVertex2f(posf.x + sizef.x - shrinkVal, posf.y + shrinkVal);
		//		glVertex2f(posf.x + sizef.x - shrinkVal, posf.y + sizef.y - shrinkVal);
		//		glVertex2f(posf.x + shrinkVal, posf.y + sizef.y - shrinkVal);
		//		glVertex2f(posf.x + shrinkVal, posf.y + shrinkVal);
		//		glEnd();
		//		
		//		return;
		//	}


		//	
		//	
		//	glLineWidth(lineWidthf);
		//	glBegin(GL_LINE_LOOP);
		//}
		//	glColor4fv(color);
		//	glVertex2f(posf.x + sizef.x - shrinkVal, posf.y + shrinkVal);
		//	glVertex2f(posf.x + sizef.x - shrinkVal, posf.y + sizef.y - shrinkVal);
		//	glVertex2f(posf.x + shrinkVal, posf.y + sizef.y - shrinkVal);
		//	glVertex2f(posf.x + shrinkVal, posf.y + shrinkVal);
		//glEnd();
	}

	void Box::render()
	{
		glDisable(GL_TEXTURE_2D);
		if (changed)
		{
			setDisplayList(GL_COMPILE_AND_EXECUTE);
			changed = false;
		}
		else
		{
			glCallList(displayList);
		}
	}

	void Box::setEdgeMode(int lineWidth)
	{
		this->lineWidth = limit(lineWidth, 1, 255);
	}

};

#endif