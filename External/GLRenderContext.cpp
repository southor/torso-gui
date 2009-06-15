
#include "External\GLRenderContext.h"
#include "External\gl_includes.h"


namespace SGui
{

	void GLRenderContext::flush()
	{
		glFlush();
	}

	void GLRenderContext::pushMatrix()
	{
		glPushMatrix();
	}

	void GLRenderContext::popMatrix()
	{
		glPopMatrix();
	}

	void GLRenderContext::translate(const Vec &v)
	{
		glTranslatef(static_cast<float>(v.x), static_cast<float>(v.y), 0.0f);
	}

	void GLRenderContext::scale(const Vecf &v)
	{
		glScalef(v.x, v.y, 1.0f);
	}

	void GLRenderContext::initGL(uint w, uint h)
	{

		glViewport(0, 0, w, h);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, static_cast<double>(w), 0.0, static_cast<double>(h), 0.5, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -2.0f);



		glShadeModel(GL_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_VERTEX_ARRAY);	

		//glEnable(GL_TEXTURE_COORD_ARRAY);
		//glTexCoordPointer(2, GL_FLOAT, 0, txtrCoordArr);
		//glDrawElements(PRIMITIVE_TYPE_GL_DRAW_MODES[primitiveType], nInd, GL_UNSIGNED_INT, indArr);
		//glDisable(GL_TEXTURE_COORD_ARRAY);


		//glEnable(GL_COLOR_ARRAY);
		//glColorPointer(4, GL_FLOAT, 0, colorArr);				
		//glDrawArrays(PRIMITIVE_TYPE_GL_DRAW_MODES[primitiveType], 0, nVtx);
		//glDisable(GL_COLOR_ARRAY);
		
		glEnable(GL_SCISSOR_TEST);
	}

	void GLRenderContext::uninitGL()
	{
		// TODO: anything?
	}

	void GLRenderContext::startNewRendering()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	gl_uint GLRenderContext::createDefaultTxtr()
	{
		GLuint txtrId;

		static Txtr::Pixel4 pixel(127, 127, 127, 255);

		glGenTextures(1, &txtrId);
		glBindTexture(GL_TEXTURE_2D, txtrId);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)&pixel);
		//txtrIdPool[std::string("DefaultTxtr")] = txtrId;

		return txtrId;
	}

	gl_uint GLRenderContext::loadTxtr(Txtr::Pixel4 *pixels, gl_uint width, gl_uint height)
	{
		GLuint txtrId;
		
		glGenTextures(1, &txtrId);
		glBindTexture(GL_TEXTURE_2D, txtrId);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)pixels);		
		
		// Perform these here?
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		return txtrId;
	}

	void GLRenderContext::unloadTxtr(gl_uint txtrId)
	{
		glDeleteTextures(1, &txtrId);
	}

	void GLRenderContext::renderTxtr(uint txtrId, const RectIfc *rect, const TxtrCoord *txtrCoords)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, txtrId);
		glBegin(GL_QUADS);
			glTexCoord2f(txtrCoords[0].s, txtrCoords[0].t);	glVertex2i(rect->getRight(), rect->getBottom());
			glTexCoord2f(txtrCoords[1].s, txtrCoords[1].t);	glVertex2i(rect->getRight(), rect->getTop());
			glTexCoord2f(txtrCoords[2].s, txtrCoords[2].t);	glVertex2i(rect->getLeft(), rect->getTop());
			glTexCoord2f(txtrCoords[3].s, txtrCoords[3].t);	glVertex2i(rect->getLeft(), rect->getBottom());
		glEnd();
	}

	gl_uint GLRenderContext::createDisplayList()
	{
		return glGenLists(1);
	}

	void GLRenderContext::renderBox(const RectIfc *rect, const Color4f &color, int lineWidth)
	{

		GLfloat lineWidthf = static_cast<GLfloat>(lineWidth);
		
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

		cOX = static_cast<GLfloat>(rect->getLeft());
		fOX = static_cast<GLfloat>(rect->getRight());
		cOY = static_cast<GLfloat>(rect->getBottom());
		fOY = static_cast<GLfloat>(rect->getTop());

		// ------- Inner values ----------		

		GLfloat cIX; // close inner X 		
		GLfloat fIX; // far inner X
		GLfloat cIY; // close inner Y 
		GLfloat fIY; // far inner Y

		
		GLfloat shrinkVal = veryFatBorderMode ? lineWidthf : (lineWidthf / 2.0f);

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
		
	}


	void GLRenderContext::renderBoxToDisplayList(gl_uint displayList, bool execute, const RectIfc *rect, const Color4f &color, int lineWidth)
	{
		glDisable(GL_TEXTURE_2D);
		glNewList(displayList, execute ? GL_COMPILE_AND_EXECUTE : GL_COMPILE);			
			renderBox(rect, color, lineWidth);
		glEndList();
	}

	void GLRenderContext::renderDisplayList(gl_uint displayList)
	{
		glDisable(GL_TEXTURE_2D);
		glCallList(displayList);
	}

	void GLRenderContext::renderText(gl_uint fontTxtrId, int nVtx, const float *vtxArr, const float *colorArr, const float *txtrCoordArr)
	{ 		
		if (nVtx > 0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, fontTxtrId);
			glEnable(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, txtrCoordArr);
			glEnable(GL_COLOR_ARRAY);
			glColorPointer(3, GL_FLOAT, 0, colorArr);
			glVertexPointer(3, GL_FLOAT, 0, vtxArr);

			glDrawArrays(GL_QUADS, 0, nVtx);

			glDisable(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_COLOR_ARRAY);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	void GLRenderContext::setClipping(const Pos &pos, const Rect &clipRect)
	{
		glScissor(pos.x + clipRect.getX(), pos.y + clipRect.getY(),
				  clipRect.getWidth(), clipRect.getHeight());
	}

};

