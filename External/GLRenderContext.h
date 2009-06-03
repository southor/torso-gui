#ifndef _STATE_GUI_GL_RENDER_CONTEXT_H_
#define _STATE_GUI_GL_RENDER_CONTEXT_H_

#include "SGui\RenderContext.h"

namespace SGui
{

	class GLRenderContext : public RenderContext
	{
	protected:

		void renderBox(const RectIfc *rect, const Color4f &color, int lineWidth);

	public:


		void initGL(uint w, uint h);

		void startNewRendering();

		virtual void pushMatrix();
		virtual void popMatrix();

		virtual void translate(int x, int y);

		virtual void setClipping(const Pos &pos, const Rect &clipRect);

		virtual gl_uint createDisplayList();

		virtual void renderBoxToDisplayList(gl_uint displayList, bool execute, const RectIfc *rect, const Color4f &color, int lineWidth);
		virtual void renderDisplayList(gl_uint displayList);

		virtual gl_uint loadTxtr(Txtr::Pixel4 *pixels, gl_uint width, gl_uint height);
		virtual void unloadTxtr(gl_uint txtrId);
		
		virtual gl_uint createDefaultTxtr();

		virtual void renderTxtr(gl_uint txtrId, const RectIfc *rect, const TxtrCoord *txtrCoords);

		virtual void renderText(gl_uint fontTxtrId, int nVtx, float *vtxArr, float *colorArr, float *txtrCoordArr);
		
		
	};

	//static RenderContext *renderContext;

};

#endif