#ifndef _STATE_GUI_FONT_H_
#define _STATE_GUI_FONT_H_

#include "basic.h"
#include "Txtr.h"
#include "function_templates.h"
#include "macros.h"

#include <vector>
#include <string>



namespace SGui
{
	class Font
	{
	public:
		static const int N_FLOATS_PER_VTX = 3;
		static const int N_VTX_PER_CHAR = 4;
		static const int N_VTX_FLOATS_PER_CHAR = N_FLOATS_PER_VTX * N_VTX_PER_CHAR;

		static const int N_FLOATS_PER_COLOR = 3;
		static const int N_COLOR_FLOATS_PER_CHAR = N_VTX_PER_CHAR * N_FLOATS_PER_COLOR;

		static const int N_TXTR_COORD_PER_VTX = 2;
		static const int N_TXTR_COORD_FLOATS_PER_CHAR = N_VTX_PER_CHAR * N_TXTR_COORD_PER_VTX;

		static const int BOLD = 1;
		static const int UNDERLINE = 2;
		static const int ITALIC = 4;		
	private:

		static const int N_CHARS = 256;
		

		
		static const int N_MODS = 3;		
		// Mods
		static const int B_INDEX = 0;
		static const int U_INDEX = 1;
		static const int I_INDEX = 2;

		static const char MOD_SYMBOLS[];

		static const int N_MOD_COMBINATIONS = 8; // POW_TO_2[N_MODS];
		static const int B_BIT = BOLD;  // POW_TO_2[B_INDEX];
		static const int U_BIT = UNDERLINE; // POW_TO_2[U_INDEX];
		static const int I_BIT = ITALIC; // POW_TO_2[I_INDEX];


		// Number of characters in each font image, in x and y
		Vec fontImageNCharacters;

		// The size of one font image in pixels, width and height.
		Vec fontImageSize;

		// Number of font images in x and y axis in the combined font image.
		Vec nFontImagesCombined;

		// The combined font image loaded to the grafics card.
		gl_uint combinedFontTxtrId;

		// The height of each character, always the same.
		uchar charHeight;

		// The basewidth of each character
		uchar charBaseWidth;

		// Boolean telling if texture coordinates needs rescaling or not
		bool usingTxtrCoordRescale;	

		// Rescale values for texture coordinates, stored for fast access.
		Vecd txtrCoordRescaleVec;

		/**
		 * Position of each fontimage in the combined fontimage.
		 * The combined fontimage is an 2-dimensional array of fontimages.
		 * The only reason for it to be 2-dimensional is that it should have a
		 * chanse to have the same width and height in pixels
		 * (fontImageSize must be same in x and y)
		 */
		VecTempl<int8> fontImagePos[N_MOD_COMBINATIONS];
		

		// The width of each character, (just affects rendering, not  storage)
		uchar charWidths[N_MOD_COMBINATIONS][N_CHARS];

		







		/**		 
		 * Loads char widths from the file and stores in charWidths
		 * @param filename The file to load from.
		 * @param charWidths The array to store the character widths to.
		 */
		static void loadCharWidths(const fschar *filename, uchar maxWidth, uchar *charWidths);


	public:

		static const int ALLOWED_MODS = (BOLD | UNDERLINE | ITALIC);


		/**
		 * @param fontDirectory The directory to the image font files on the hard drive.
		 *                      These images must have a size of 2^n otherwise it might
		 *                      not work depending on the implementation.
		 */
		Font(RenderContext *renderContext, const fschar *fontDirectory, Vec fontImageNCharacters = Vec(16, 16));

		inline gl_uint getTxtrId() const					{ return combinedFontTxtrId; }
		
		inline int getCharWidth(char c, int mods) const		{ dAssert(checkFlags(mods, ALLOWED_MODS));
															  return charWidths[mods][c]; }

		inline int getCharHeight()							{ return charHeight; }

		int writeCharToVtxArr(char c, int mods, Color3f color, gl_float *vtxArr, gl_float *colorArr, gl_float *txtrCoordArr, Pos pos, float size = 1.0f) const;


	public:


		//debug
		int isConsistent() const;
		


		
	};

};

#endif