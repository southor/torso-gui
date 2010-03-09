#ifndef _STATE_GUI_GL_RENDER_CONTEXT_H_
#define _STATE_GUI_GL_RENDER_CONTEXT_H_

#include "SGui\RenderContext.h"

namespace SGui
{

	class GLRenderContext : public RenderContext
	{
	protected:

		//bool textureNonPowerOfTwoExtensionAvailible;

		void renderBox(const RectIfc *rect, const Color4f &color, int lineWidth);

		bool glExtensionAvailible(const char *extensionName);

		//uint viewportWidth;
		//uint viewportHeight;

	public:

		void initGL(uint w, uint h, const SGui::Color3f &bgColor);
		void uninitGL();

		//virtual bool isTextureNonPowerOfTwoExtensionAvailible();

		//virtual bool modifyTxtrSizeIfNecessary(gl_uint sizeValue);

		virtual void flush();

		//virtual void startNewRendering(const SGui::Color3f &color);
		virtual void startNewRendering();

		virtual void pushMatrix();
		virtual void popMatrix();

		virtual void translate(const Vec &v);

		virtual void scale(const Vecf &v);

		virtual void setClipping(const Pos &pos, const Rect &clipRect);

		virtual gl_uint createDisplayList();

		virtual void renderBoxToDisplayList(gl_uint displayList, bool execute, const RectIfc *rect, const Color4f &color, int lineWidth);
		virtual void renderDisplayList(gl_uint displayList);

		virtual gl_uint loadTxtr(const Txtr::Pixel4 *pixels, gl_uint width, gl_uint height);
		virtual void unloadTxtr(gl_uint txtrId);
		
		virtual gl_uint createDefaultTxtr();

		virtual void renderTxtr(gl_uint txtrId, const RectIfc *rect, const TxtrCoord *txtrCoords);

		virtual void renderText(gl_uint fontTxtrId, int nVtx, const float *vtxArr, const float *colorArr, const float *txtrCoordArr);
		
		
	};

	//static RenderContext *renderContext;

};

#endif