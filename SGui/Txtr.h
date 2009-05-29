#ifndef _STATE_GUI_TEXTURE_H
#define _STATE_GUI_TEXTURE_H

#include "basic.h"
#include "basic_includes.h"
#include "gl_includes.h"

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
			GLubyte r, g, b;
			Pixel3() {}
			Pixel3(GLubyte r, GLubyte g, GLubyte b) : r(r), g(g), b(b) {}
			inline GLubyte getBWColor() const	{ return static_cast<GLubyte>(((uint)r+(uint)g+(uint)b) / 3); }
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
			GLubyte r, g, b, a;
			Pixel4() {}
			Pixel4(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {}
			inline GLubyte getBWColor() const	{ return static_cast<GLubyte>(((uint)r+(uint)g+(uint)b) / 3); }
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
		
		GLuint width;
		GLuint height;
		Pixel4 *pixels;

	public:
		
		Txtr();
		Txtr(const Txtr &txtr);
		Txtr(GLuint w, GLuint h);
		Txtr(const char *colorsFileName, GLubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		Txtr(const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint transparentAA = 1);
		Txtr(const char *colorsFileName, const char *alphaFileName);
		Txtr(Pixel3 color, const char *alphaFileName);
		
		Txtr &operator=(const Txtr &txtr);

		~Txtr(void);

		inline uint getWidth() const						{ return width; }
		inline uint getHeight() const						{ return height; }
		inline Vec getSize() const							{ return Vec(width, height); }

		inline const Pixel4 *getPixels() const				{ assert(hasImage());
															  return pixels; }

		inline Pixel4 *getPixelsForChanging()				{ assert(hasImage());
													          return pixels; }

		inline uint getPixelIndex(uint x, uint y) const		{ return y*(width) + x; }

		inline const Pixel4 &getPixel(uint i) const			{ assert(hasImage());
															  if (!(i < width*height))
																assert(i < width*height);
															  return pixels[i]; }

		Pixel4 getInterpoolatedPixel(float x, float y) const;

		inline void setPixel(uint i, const Pixel4 &pixel)	{ assert(hasImage());
															  assert(i < width*height);
															  pixels[i] = pixel; }

		inline const Pixel4 &getPixel(uint x, uint y) const			{ return getPixel(getPixelIndex(x, y)); }		

		inline void setPixel(uint x, uint y, const Pixel4 &pixel)	{ setPixel(getPixelIndex(x, y), pixel); }

		// only sets color, not alpha value of pixels
		void fillColor(const Pixel3 &color);

		
		/**
		 * @return Returns true if it did not have an
		 * image beofre this call, otherwise false.
		 */
		bool createImage(GLuint w, GLuint h);

		/*
		 * @return Returns false if it has image.
		 */
		bool removeImage();

		inline bool hasImage() const		{ return (pixels != NULL); }

		
		void load(const char *colorsFileName, GLubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		void load(const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint transparentAA = 1);
		void load(const char *colorsFileName, const char *alphaFileName);
		void load(Pixel3 color, const char *alphaFileName);
		
		
		
		GLuint add(const char *name);
		
		void setAlpha(GLubyte alpha);
		void setAlpha(GLubyte alpha, Pixel3 transparentColor, uint antiAliasing = 0);
		void setTransparent(Pixel3 transparentColor, uint antiAliasing = 1);


		// Draws the hole texture context of txtr to this texture at pixel x, y
		void copyTo(Txtr *txtr, int x, int y);
		
		static GLuint loadAddN(const char *name, const char *colorsFileName, GLubyte alpha = 255);		
		// @param transparentAA transparent anti aliasing value
		static GLuint loadAddN(const char *name, const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint antiAliasing = 1);
		static GLuint loadAddN(const char *name, const char *colorsFileName, const char *alphaFileName);
		static GLuint loadAddN(const char *name, Pixel3 color, const char *alphaFileName);


		static GLuint loadAdd(const char *colorsFileName, GLubyte alpha = 255);
		// @param transparentAA transparent anti aliasing value
		static GLuint loadAdd(const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint antiAliasing = 1);
		static GLuint loadAdd(const char *colorsFileName, const char *alphaFileName);
		static GLuint loadAdd(Pixel3 color, const char *alphaFileName);
		

		// Should be called one time before
		static GLuint createDefaultTxtr();

		static GLuint getDefaultTxtrId();

		//debug
		bool isConsistent() const;

	private:

		// Must have no Image to call this.
		void loadColors(const char *fileName, bool initialize = true);

		/**
		 * Must have an image to call this.
		 * Will add alphavalues if images has same proportions
		 */
		void loadAlpha(const char *fileName, GLubyte defaultAlpha, bool initialize = false);

		static Pixel3* loadFile(const char *fileName, GLuint *w, GLuint *h);

		typedef std::pair<std::string, GLuint> TxtrPair;

		static std::map<std::string, GLuint> txtrIdPool;

		// createDefaultTxtr() should be called before accessing the rest of this namespace!
		static GLuint defaultTxtr;



	};

};


#endif