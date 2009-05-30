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

	// tmp note: Fixa loadFile, snygga till kod. mer konsekvent.
	// använd GLubyte istället för char

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
			//GLubyte r, g, b, a;
			gl_ubyte r, g, b, a;
			Pixel4() {}
			//Pixel4(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {}
			Pixel4(gl_ubyte r, gl_ubyte g, gl_ubyte b, gl_ubyte a) : r(r), g(g), b(b), a(a) {}
			//inline GLubyte getBWColor() const	{ return static_cast<GLubyte>(((uint)r+(uint)g+(uint)b) / 3); }
			inline gl_ubyte getBWColor() const	{ return static_cast<gl_ubyte>(((uint)r+(uint)g+(uint)b) / 3); }
			bool operator == (const Pixel4 &pixel4) const
			{
				return (r == pixel4.r) && (g == pixel4.g) && (b == pixel4.b) && (a == pixel4.a);
			}
			//Pixel4 operator *(float v)
			//{
			//	return Pixel4((GLubyte)(((float)r)*v), (GLubyte)(((float)g)*v), (GLubyte)(((float)b)*v), (GLubyte)(((float)a)*v));
			//}
		};
	
	private:
		
		//GLuint width;
		//GLuint height;
		gl_uint width;
		gl_uint height;

		Pixel4 *pixels;

	public:
		
		Txtr();
		Txtr(const Txtr &txtr);
		Txtr(gl_uint w, gl_uint h);
		Txtr(const char *colorsFileName, gl_ubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		Txtr(const char *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint transparentAA = 1);
		Txtr(const char *colorsFileName, const char *alphaFileName);
		Txtr(Pixel3 color, const char *alphaFileName);
		
		Txtr &operator=(const Txtr &txtr);

		~Txtr(void);

		inline uint getWidth() const						{ return width; }
		inline uint getHeight() const						{ return height; }
		inline Vec getSize() const							{ return Vec(width, height); }

		inline const Pixel4 *getPixels() const				{ dAssert(hasImage());
															  return pixels; }

		inline Pixel4 *getPixelsForChanging()				{ dAssert(hasImage());
													          return pixels; }

		inline uint getPixelIndex(uint x, uint y) const		{ return y*(width) + x; }

		inline const Pixel4 &getPixel(uint i) const			{ dAssert(hasImage());
															  if (!(i < width*height))
																dAssert(i < width*height);
															  return pixels[i]; }

		Pixel4 getInterpoolatedPixel(float x, float y) const;

		inline void setPixel(uint i, const Pixel4 &pixel)	{ dAssert(hasImage());
															  dAssert(i < width*height);
															  pixels[i] = pixel; }

		inline const Pixel4 &getPixel(uint x, uint y) const			{ return getPixel(getPixelIndex(x, y)); }		

		inline void setPixel(uint x, uint y, const Pixel4 &pixel)	{ setPixel(getPixelIndex(x, y), pixel); }

		// only sets color, not alpha value of pixels
		void fillColor(const Pixel3 &color);

		
		/**
		 * @return Returns true if it did not have an
		 * image beofre this call, otherwise false.
		 */
		bool createImage(gl_uint w, gl_uint h);

		/*
		 * @return Returns false if it has image.
		 */
		bool removeImage();

		inline bool hasImage() const		{ return (pixels != NULL); }

		
		void load(const char *colorsFileName, gl_ubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		void load(const char *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint transparentAA = 1);
		void load(const char *colorsFileName, const char *alphaFileName);
		void load(Pixel3 color, const char *alphaFileName);
		
		
		
		gl_uint add(const char *name);
		
		void setAlpha(gl_ubyte alpha);
		void setAlpha(gl_ubyte alpha, Pixel3 transparentColor, uint antiAliasing = 0);
		void setTransparent(Pixel3 transparentColor, uint antiAliasing = 1);


		// Draws the hole texture context of txtr to this texture at pixel x, y
		void copyTo(Txtr *txtr, int x, int y);
		
		static /*GLuint*/gl_uint loadAddN(const char *name, const char *colorsFileName, gl_ubyte alpha = 255);		
		
		// @param transparentAA transparent anti aliasing value
		static /*GLuint*/gl_uint loadAddN(const char *name, const char *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint antiAliasing = 1);
		static /*GLuint*/gl_uint loadAddN(const char *name, const char *colorsFileName, const char *alphaFileName);
		static /*GLuint*/gl_uint loadAddN(const char *name, Pixel3 color, const char *alphaFileName);


		static /*GLuint*/gl_uint loadAdd(const char *colorsFileName, gl_ubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		static /*GLuint*/gl_uint loadAdd(const char *colorsFileName, gl_ubyte alpha, Pixel3 transparentColor, uint antiAliasing = 1);
		static /*GLuint*/gl_uint loadAdd(const char *colorsFileName, const char *alphaFileName);
		static /*GLuint*/gl_uint loadAdd(Pixel3 color, const char *alphaFileName);
		
		// Clears the texture ids pool.
		static void clearLoaded();


		// Should be called one time before
		static /*GLuint*/gl_uint createDefaultTxtr();

		static /*GLuint*/gl_uint getDefaultTxtrId();

		//debug
		bool isConsistent() const;

	private:

		// Must have no Image to call this.
		void loadColors(const char *fileName, bool initialize = true);

		/**
		 * Must have an image to call this.
		 * Will add alphavalues if images has same proportions
		 */
		void loadAlpha(const char *fileName, gl_ubyte defaultAlpha, bool initialize = false);

		static Pixel3* loadFile(const char *fileName, gl_uint *w, gl_uint *h);

		typedef std::pair<std::string, gl_uint> TxtrPair;

		static std::map<std::string, gl_uint> txtrIdPool;

		// createDefaultTxtr() should be called before accessing the rest of this namespace!
		static /*GLuint*/gl_uint defaultTxtr;



	};

};


#endif