#ifndef _STATE_GUI_RENDER_CONTEXT_H_
#define _STATE_GUI_RENDER_CONTEXT_H_

//#include "gl_declares.h"

//#include "declares.h"
#include "RectIfc.h"

#include "Txtr.h"

namespace SGui
{

	class RenderContext
	{
	protected:

		//bool textureNonPowerOfTwoAvailible;

		Flags<int> features;		

		inline void setFeature(int flag, bool value)
		{
			features.set(flag, value);
		}

	//	virtual void renderBox(const RectIfc *rect, const Color4f &color, int lineWidth);

	public:

		// Feature flags
		enum
		{
			FEATURE_TEXTURE_NON_POWER_OF_TWO_AVAILIBLE = 1
		};

		//RenderContext() : textureNonPowerOfTwoAvailible(false)
		//{}

		//inline bool isTextureNonPowerOfTwoExtensionAvailible()
		//{
		//	return textureNonPowerOfTwoExtensionAvailible;
		//}

		inline bool hasFeature(int flag)
		{
			return features.get(flag);
		}
		

		virtual void flush() = 0;

		virtual void pushMatrix() = 0;
		virtual void popMatrix() = 0;

		virtual void translate(const Vec &v) = 0;

		virtual void scale(const Vecf &v) = 0;

		virtual void setClipping(const Pos &pos, const Rect &clipRect) = 0;

		virtual gl_uint createDisplayList() = 0;

		virtual void renderBoxToDisplayList(gl_uint displayList, bool execute, const RectIfc *rect, const Color4f &color, int lineWidth) = 0;
		virtual void renderDisplayList(gl_uint displayList) = 0;

		virtual gl_uint loadTxtr(const Txtr::Pixel4 *pixels, gl_uint width, gl_uint height) = 0;
		virtual void unloadTxtr(gl_uint txtrId) = 0;
		
		virtual gl_uint createDefaultTxtr() = 0;

		virtual void renderTxtr(gl_uint txtrId, const RectIfc *rect, const TxtrCoord *txtrCoords) = 0;

		virtual void renderText(gl_uint fontTxtrId, int nVtx, const float *vtxArr, const float *colorArr, const float *txtrCoordArr) = 0;
		
		
	};

};

#endif