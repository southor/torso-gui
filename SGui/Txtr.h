#ifndef _STATE_GUI_TEXTURE_H
#define _STATE_GUI_TEXTURE_H

#include "basic.h"
#include "basic_includes.h"
//#include "gl_includes.h"
#include "gl_declares.h"
#include "macros.h"

#include <map>
#include <string>
 
namespace SGui
{

	class RenderContext;

	// tmp note: Fixa loadFile, snygga till kod. mer konsekvent.
	// anv�nd GLubyte ist�llet f�r char

	class Txtr
	{
	public:

		struct Pixel3
		{
			//GLubyte r, g, b;
			gl_ubyte r, g, b;
			Pixel3() {}
			//Pixel3(GLubyte r, GLubyte g, GLubyte b) : r(r), g(g), b(b) {}
			Pixel3(gl_ubyte r, gl_ubyte g, gl_ubyte b) : r(r), g(g), b(b) {}
			//inline GLubyte getBWColor() const	{ return static_cast<GLubyte>(((uint)r+(uint)g+(uint)b) / 3); }
			inline gl_ubyte getBWColor() const	{ return static_cast<gl_ubyte>(((uint)r+(uint)g+(uint)b) / 3); }
			bool operator == (const Pixel3 &pixel3) const
			{
				return (r == pixel3.r) && (g == pixel3.g) && (b == pixel3.b);
			}
			//Pixel4 operator *(float v)
			//{
			//}
		};

		struct Pixel4
		{
			gl_ubyte r, g, b, a;
			Pixel4() {}
			Pixel4(gl_ubyte r, gl_ubyte g, gl_ubyte b, gl_ubyte a) : r(r), g(g), b(b), a(a) {}
			inline gl_ubyte getBWColor() const	{ return static_cast<gl_ubyte>(((uint)r+(uint)g+(uint)b) / 3); }
			//bool operator == (const Pixel4 &pixel4) const
			//{
			//	//return (r == pixel4.r) && (g == pixel4.g) && (b == pixel4.b) && (a == pixel4.a);
			//	return *reinterpret_cast<int32>(this) == *reinterpret_cast<int32>(&pixel4);
			//}
		};
	
	private:
		
		//GLuint width;
		//GLuint height;
		gl_uint width;
		gl_uint height;

		/**
		 * Pixels are stored by rows, the current implementation of fill functions depend on this property.
		 */
		Pixel4 *pixels;

	public:
		
		Txtr();
		Txtr(const Txtr &txtr);
		Txtr(gl_uint w, gl_uint h);
		Txtr(const fschar *colorsFileName, gl_ubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		Txtr(const fschar *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint transparentAA = 1);
		Txtr(const fschar *colorsFileName, const fschar *alphaFileName);
		Txtr(Pixel3 color, const fschar *alphaFileName);
		
		Txtr &operator=(const Txtr &txtr);

		~Txtr(void);

		inline uint getWidth() const						{ return width; }
		inline uint getHeight() const						{ return height; }
		inline Vec getSize() const							{ return Vec(width, height); }

		inline const Pixel4 *getPixels() const				{ dAssert(hasImage());
															  return pixels; }

		inline Pixel4 *getPixels()							{ dAssert(hasImage());
													          return pixels; }

		inline uint getPixelIndex(uint x, uint y) const		{ return y*(width) + x; }

		inline const Pixel4 &getPixel(uint i) const			{ dAssert(hasImage());
															  //if (!(i < width*height))
															  dAssert(i < width*height);
															  return pixels[i]; }

		inline Pixel4 &getPixel(uint i)						{ dAssert(hasImage());
															  //if (!(i < width*height))
															  dAssert(i < width*height);
															  return pixels[i]; }

		Pixel4 getInterpoolatedPixel(float x, float y) const;

		inline void setPixel(uint i, const Pixel4 &pixel)	{ dAssert(hasImage());
															  dAssert(i < width*height);
															  pixels[i] = pixel; }

		inline const Pixel4 &getPixel(uint x, uint y) const			{ return getPixel(getPixelIndex(x, y)); }		

		inline Pixel4 &getPixel(uint x, uint y)						{ return getPixel(getPixelIndex(x, y)); }

		inline void setPixel(uint x, uint y, const Pixel4 &pixel)	{ setPixel(getPixelIndex(x, y), pixel); }

		// Fills a rectangle are with a color
		void fillArea(int x, int y, int width, int height, const Pixel4 &pixel);

		// only sets color, not alpha value of pixels
		void fillColor3(const Pixel3 &color);

		
		/**
		 * @return Returns true if it did not have an
		 * image before this call, otherwise false.
		 */
		bool createImage(gl_uint w, gl_uint h);

		/*
		 * @return Returns false if it has image.
		 */
		bool removeImage();

		inline bool hasImage() const		{ return (pixels != nullptr); }

		
		void load(const fschar *colorsFileName, gl_ubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		void load(const fschar *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint transparentAA = 1);
		void load(const fschar *colorsFileName, const fschar *alphaFileName);
		void load(Pixel3 color, const fschar *alphaFileName);
		
		
		
		gl_uint add(RenderContext *renderContext, const fschar *name);
		
		void setAlpha(gl_ubyte alpha);
		void setAlpha(gl_ubyte alpha, Pixel3 transparentColor, uint antiAliasing = 0);
		void setTransparent(Pixel3 transparentColor, uint antiAliasing = 1);


		// Draws the hole texture context of txtr to this texture at pixel x, y
		void copyTo(Txtr *txtr, int x, int y, bool fillSurroundings = false);		

		static bool getTxtrCoordRescale(uint txtrId, Vecd &rescaleVec);

		//static Vecf getTxtrCoordRescale(uint txtrId)
		//{
		//	Vecd rescaleVec;
		//	if ( ! getTxtrCoordRescale(txtrId, rescaleVec))
		//	{
		//		rescaleVec.x = 1.0;
		//		rescaleVec.y = 1.0;
		//	}
		//	return rescaleVec;
		//}
		
		static /*GLuint*/gl_uint loadAddN(RenderContext *renderContext, const fschar *name, const fschar *colorsFileName, gl_ubyte alpha = 255);		
		
		// @param transparentAA transparent anti aliasing value
		static /*GLuint*/gl_uint loadAddN(RenderContext *renderContext, const fschar *name, const fschar *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint antiAliasing = 1);
		static /*GLuint*/gl_uint loadAddN(RenderContext *renderContext, const fschar *name, const fschar *colorsFileName, const fschar *alphaFileName);
		static /*GLuint*/gl_uint loadAddN(RenderContext *renderContext, const fschar *name, Pixel3 color, const fschar *alphaFileName);


		static /*GLuint*/gl_uint loadAdd(RenderContext *renderContext, const fschar *colorsFileName, gl_ubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		static /*GLuint*/gl_uint loadAdd(RenderContext *renderContext, const fschar *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint antiAliasing = 1);
		static /*GLuint*/gl_uint loadAdd(RenderContext *renderContext, const fschar *colorsFileName, const fschar *alphaFileName);
		static /*GLuint*/gl_uint loadAdd(RenderContext *renderContext, Pixel3 color, const fschar *alphaFileName);
		
		// Clears the texture ids pool.
		static void clearLoaded(RenderContext *renderContext);


		// Should be called one time before
		static /*GLuint*/gl_uint createDefaultTxtr(RenderContext *renderContext);

		static /*GLuint*/gl_uint getDefaultTxtrId();

		//debug
		bool isConsistent() const;

	private:

		// Must have no Image to call this.
		void loadColors(const fschar *fileName, bool initialize = true);

		/**
		 * Must have an image to call this.
		 * Will add alphavalues if images has same proportions
		 */
		void loadAlpha(const fschar *fileName, gl_ubyte defaultAlpha, bool initialize = false);

		static Pixel3* loadFile(const fschar *fileName, gl_uint *w, gl_uint *h);

		// @return true if sizeValue was modified
		static bool conformSizeValue(gl_uint &sizeValue);

		//// Copies from pixels into a specified row
		//void pasteRow(int y, int xStart, int length, const Pixel4 *copyPixels);

		//// Fills a specified row with a pixel value
		//void fillRow(int y, int xStart, int length, Pixel4 pixel);		

		// Fills the surroungings of the specified area with colors chosen from the edges of the specified area.
		void duplicateRectangleEdges(int x, int y, int width, int height);

		// duplicates a row into multiple rows
		void duplicateRow(int x, int y, int length, int duplicateStep, int nDuplicates);

		// duplicates a column into multiple column
		void duplicateColumn(int x, int y, int length, int duplicateStep, int nDuplicates);

		//// Copy from a selected line of pixels and paste each pixel into a line in another direction.
		//void selectAndDuplicate(int x, int y, int xCopyStep, int yCopyStep, int nToCopy, int xPasteStep, int yPasteStep, int nToPaste);


		typedef std::pair<fsstring, gl_uint> TxtrPair;

		static std::map<fsstring, gl_uint> txtrIdPool;

		static std::map<gl_uint, Vecd> txtrRescaleMap;

		// createDefaultTxtr() should be called before accessing the rest of this namespace!
		static /*GLuint*/gl_uint defaultTxtr;



	};

};


#endif
