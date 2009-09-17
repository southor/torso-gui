
#include "SGuiExternal\GLRenderContext.h"
#include "SGuiExternal\gl_includes.h"


#define SGUI_DEBUG_GL_LINES

namespace SGui
{

	void displayGLError(const char *str, GLenum error)
	{

		//std::cout << str << glGetString(error) << std::endl;
		std::cout << str << " GLError = ";

		switch(error)
		{
		case GL_NO_ERROR:
			std::cout << "GL_NO_ERROR";
			break;
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY";
			break;
		//case GL_TABLE_TOO_LARGE:
		//	std::cout << "GL_TABLE_TOO_LARGE";
		//	break;
		default:
			std::cout << "unknown error!";
			break;
		}

		std::cout << std::endl;

	}

	inline void condDisplayGLError(const char *str)
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) displayGLError(str, error);
	}

	bool GLRenderContext::glExtensionAvailible(const char *extensionName)
	{
		const char *glExtensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)); //opengl returns a static string
		return strstr(glExtensions, "GL_ARGB_texture_non_power_of_two") != NULL;
	}

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
#ifndef SGUI_DEBUG_GL_LINES
		glScalef(v.x, v.y, 1.0f);
#endif
	}

	void GLRenderContext::initGL(uint w, uint h)
	{

		glViewport(0, 0, w, h);

		condDisplayGLError("initGL 2");


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, static_cast<double>(w), 0.0, static_cast<double>(h), 0.5, 10.0);
		condDisplayGLError("initGL 5");
		glMatrixMode(GL_MODELVIEW);
		condDisplayGLError("initGL 6");
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -2.0f);

		condDisplayGLError("initGL 10");

		glShadeModel(GL_SMOOTH);
		condDisplayGLError("initGL 12");
		glEnable(GL_BLEND);
		condDisplayGLError("initGL 13");
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		condDisplayGLError("initGL 15");

		////glEnable(GL_VERTEX_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		condDisplayGLError("initGL 19");

		////glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		////glTexCoordPointer(2, GL_FLOAT, 0, txtrCoordArr);
		////glDrawElements(PRIMITIVE_TYPE_GL_DRAW_MODES[primitiveType], nInd, GL_UNSIGNED_INT, indArr);
		////glDisable(GL_TEXTURE_COORD_ARRAY);


		////glEnableClientState(GL_COLOR_ARRAY);
		////glColorPointer(4, GL_FLOAT, 0, colorArr);				
		////glDrawArrays(PRIMITIVE_TYPE_GL_DRAW_MODES[primitiveType], 0, nVtx);
		////glDisable(GL_COLOR_ARRAY);
		
		glEnable(GL_SCISSOR_TEST);

		glEnable(GL_LINE_SMOOTH);

		condDisplayGLError("initGL 20");

		setFeature(FEATURE_TEXTURE_NON_POWER_OF_TWO_AVAILIBLE, glExtensionAvailible("GL_ARGB_texture_non_power_of_two"));

		condDisplayGLError("initGL 21");
		
	}

	

	void GLRenderContext::uninitGL()
	{
		// TODO: anything?
	}

	void GLRenderContext::startNewRendering(const SGui::Color3f &color)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		condDisplayGLError("start New Rendering 2");

		glColor4f(color.r, color.g, color.b, 1.0f);

		condDisplayGLError("start New Rendering 3");

		glBegin(GL_QUADS);
			glVertex3i(0, 0, 0);
			glVertex3i(500, 0, 0);
			glVertex3i(500, 500, 0);
			glVertex3i(0, 500, 0);
		glEnd();

		condDisplayGLError("start New Rendering 4");

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		condDisplayGLError("start New Rendering 5");
	}

	gl_uint GLRenderContext::createDefaultTxtr()
	{
		GLuint txtrId;

		static Txtr::Pixel4 pixel(127, 127, 127, 255);

		condDisplayGLError("createDefaultTxtr 1");

		glGenTextures(1, &txtrId);
		glBindTexture(GL_TEXTURE_2D, txtrId);
		condDisplayGLError("createDefaultTxtr 3");
		glTexImage2D(GL_TEXTURE_2D, 0, 4, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)&pixel);
		//txtrIdPool[std::wstring("DefaultTxtr")] = txtrId;

		condDisplayGLError("createDefaultTxtr 4");

		return txtrId;
	}

	gl_uint GLRenderContext::loadTxtr(const Txtr::Pixel4 *pixels, gl_uint width, gl_uint height)
	{

		GLuint txtrId;

		condDisplayGLError("loadTxtr 0");
		
		glGenTextures(1, &txtrId);
		condDisplayGLError("loadTxtr 1");
		glBindTexture(GL_TEXTURE_2D, txtrId);
		condDisplayGLError("loadTxtr 2");
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)pixels);		
		
		condDisplayGLError("loadTxtr 3");

		// Perform these here?
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		condDisplayGLError("loadTxtr 4");

		return txtrId;
	}

	void GLRenderContext::unloadTxtr(gl_uint txtrId)
	{
		condDisplayGLError("unloadTxtr 1");
		glDeleteTextures(1, &txtrId);
		condDisplayGLError("unloadTxtr 2");
	}

	void GLRenderContext::renderTxtr(uint txtrId, const RectIfc *rect, const TxtrCoord *txtrCoords)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//glDisable(GL_COLOR_2D);
		glEnable(GL_TEXTURE_2D);
		condDisplayGLError("renderTxtr 2");
		glBindTexture(GL_TEXTURE_2D, txtrId);
		glBegin(GL_QUADS);
			glTexCoord2f(txtrCoords[0].s, txtrCoords[0].t);	glVertex2i(rect->getRight(), rect->getBottom());
			glTexCoord2f(txtrCoords[1].s, txtrCoords[1].t);	glVertex2i(rect->getRight(), rect->getTop());
			glTexCoord2f(txtrCoords[2].s, txtrCoords[2].t);	glVertex2i(rect->getLeft(), rect->getTop());
			glTexCoord2f(txtrCoords[3].s, txtrCoords[3].t);	glVertex2i(rect->getLeft(), rect->getBottom());
		
		//	glTexCoord2f(txtrCoords[0].s, txtrCoords[0].t);	glVertex2i(rect->getRight(), rect->getBottom());
		//	glTexCoord2f(txtrCoords[1].s, txtrCoords[1].t);	glVertex2i(rect->getRight(), rect->getTop());
		//	glTexCoord2f(txtrCoords[2].s, txtrCoords[2].t);	glVertex2i(rect->getLeft(), rect->getTop());
		//	glTexCoord2f(txtrCoords[3].s, txtrCoords[3].t);	glVertex2i(rect->getLeft(), rect->getBottom());			
		//	//glTexCoord2f(txtrCoords[3].s, txtrCoords[3].t);	glVertex2i(rect->getLeft(), rect->getBottom());
		//	//glTexCoord2f(txtrCoords[2].s, txtrCoords[2].t);	glVertex2i(rect->getLeft(), rect->getTop());
		//	//glTexCoord2f(txtrCoords[1].s, txtrCoords[1].t);	glVertex2i(rect->getRight(), rect->getTop());
		//	//glTexCoord2f(txtrCoords[0].s, txtrCoords[0].t);	glVertex2i(rect->getRight(), rect->getBottom());
		glEnd();
		condDisplayGLError("renderTxtr 4");
		//glBegin(GL_TRIANGLES);
		//	glTexCoord2f(0.0f, 1.0f);	glVertex2i(rect->getRight(), rect->getBottom());
		//	glTexCoord2f(1.0f, 1.0f);	glVertex2i(rect->getRight(), rect->getTop());
		//	glTexCoord2f(1.0f, 0.0f);	glVertex2i(rect->getLeft(), rect->getTop());
		//glEnd();
		//glEnable(GL_COLOR);
		condDisplayGLError("renderTxtr 5");
	}

	gl_uint GLRenderContext::createDisplayList()
	{
		condDisplayGLError("createDisplayList 1");
		return glGenLists(1);
	}

	void GLRenderContext::renderBox(const RectIfc *rect, const Color4f &color, int lineWidth)
	{

		GLfloat lineWidthf = static_cast<GLfloat>(lineWidth);
		
		// If border is too wide, the gl implementation might not have an appropriate linewidth range for it.
		// So check if we should render in "veryFatBorderMode" or not.

		condDisplayGLError("renderBox 1");

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

			condDisplayGLError("renderBox 4");

			if (lineWidth > 0) glLineWidth(lineWidthf);	

			condDisplayGLError("renderBox 5");

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

		condDisplayGLError("renderBox 7");
		
	}


	void GLRenderContext::renderBoxToDisplayList(gl_uint displayList, bool execute, const RectIfc *rect, const Color4f &color, int lineWidth)
	{
		condDisplayGLError("renderBoxToDisplayList 1");
		glDisable(GL_TEXTURE_2D);
		condDisplayGLError("renderBoxToDisplayList 2");
		glNewList(displayList, execute ? GL_COMPILE_AND_EXECUTE : GL_COMPILE);			
			renderBox(rect, color, lineWidth);
		glEndList();
		condDisplayGLError("renderBoxToDisplayList 3");
	}

	void GLRenderContext::renderDisplayList(gl_uint displayList)
	{
		condDisplayGLError("renderDisplayList 1");
		glDisable(GL_TEXTURE_2D);
		condDisplayGLError("renderDisplayList 2");
		glCallList(displayList);
		condDisplayGLError("renderDisplayList 3");
	}

	void GLRenderContext::renderText(gl_uint fontTxtrId, int nVtx, const float *vtxArr, const float *colorArr, const float *txtrCoordArr)
	{ 		
		if (nVtx > 0)
		{
			condDisplayGLError("renderText 1");
			glEnable(GL_TEXTURE_2D);
			condDisplayGLError("renderText 2");
			glBindTexture(GL_TEXTURE_2D, fontTxtrId);
			condDisplayGLError("renderText 3");
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			condDisplayGLError("renderText 4");
			glTexCoordPointer(2, GL_FLOAT, 0, txtrCoordArr);
			condDisplayGLError("renderText 5");
			glEnableClientState(GL_COLOR_ARRAY);
			condDisplayGLError("renderText 6");
			glColorPointer(3, GL_FLOAT, 0, colorArr);
			condDisplayGLError("renderText 7");
			glVertexPointer(3, GL_FLOAT, 0, vtxArr);
			
			condDisplayGLError("renderText 9");
			glDrawArrays(GL_QUADS, 0, nVtx);

			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			condDisplayGLError("renderText 15");			
		}
	}

	void GLRenderContext::setClipping(const Pos &pos, const Rect &clipRect)
	{
		condDisplayGLError("setClipping 1");
		glScissor(pos.x + clipRect.getX(), pos.y + clipRect.getY(),
				  clipRect.getWidth(), clipRect.getHeight());
		condDisplayGLError("setClipping 2");
	}

};

