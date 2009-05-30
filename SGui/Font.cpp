#ifndef _STATE_GUI_FONT_CPP_
#define _STATE_GUI_FONT_CPP_

#include <string>
#include <fstream>

#include "Font.h"
#include "Txtr.h"
//#include "function_templates.h"

#include <iostream>


// solving LNK error
#include "function_templates.inl"


namespace SGui
{

	// **************************************************************************************************************
	// *------------------------------------------------------------------------------------------------------------*
	// *------------------------------------------ STATIC PRIVATE --------------------------------------------------*
	// *------------------------------------------------------------------------------------------------------------*
	// **************************************************************************************************************

	void Font::loadCharWidths(const char *filename, uchar maxWidth, uchar *charWidths)
	{
		std::ifstream file(filename);
		assert(file.good());

		uchar in;
		for(int i=0; i<N_CHARS; ++i)
		{			
			file.read((char*)&in, sizeof(in));
			
			if (in > maxWidth)
			{
				in = maxWidth;
				//assert(in <= maxWidth);
			}
			charWidths[i] = in;			
		}
	}


	// **************************************************************************************************************
	// *------------------------------------------------------------------------------------------------------------*
	// *---------------------------------------------- PUBLIC ------------------------------------------------------*
	// *------------------------------------------------------------------------------------------------------------*
	// **************************************************************************************************************


	const char Font::MOD_SYMBOLS[] = "bui";

	
	Font::Font(const char *fontDirectory, Vec fontImageNCharacters)
		: fontImageNCharacters(fontImageNCharacters)
	{
		assert(std::strlen(MOD_SYMBOLS) == N_MODS);

		const int &B = B_BIT;
		const int &U = U_BIT;
		const int &I = I_BIT;
		
		switch(N_MODS)
		{
		case 3:
			// Set number of font images
			this->nFontImagesCombined = Pos(3, 3);
			
			// font image positions
			this->fontImagePos[0] = Pos(0, 0);
			this->fontImagePos[B] = Pos(1, 0);
			this->fontImagePos[U] = Pos(2, 0);
			this->fontImagePos[B|U] = Pos(0, 1);
			this->fontImagePos[I] = Pos(1, 1);
			this->fontImagePos[B|I] = Pos(2, 1);
			this->fontImagePos[U|I] = Pos(0, 2);
			this->fontImagePos[B|U|I] = Pos(1, 2);			
		break;
		default:
			assert(false);
		break;
		}

		// Load all fonts which will make up the combined font
		std::string baseFileName = fontDirectory;
		baseFileName += "/image_";		
		const Txtr::Pixel3 WHITE = Txtr::Pixel3(255, 255, 255);
		Txtr image(WHITE, (baseFileName + ".bmp").c_str());
		Txtr imageB(WHITE, (baseFileName + "b.bmp").c_str());
		Txtr imageU(WHITE, (baseFileName + "u.bmp").c_str());
		Txtr imageBU(WHITE, (baseFileName + "bu.bmp").c_str());
		Txtr imageI(WHITE, (baseFileName + "i.bmp").c_str());
		Txtr imageBI(WHITE, (baseFileName + "bi.bmp").c_str());
		Txtr imageUI(WHITE, (baseFileName + "ui.bmp").c_str());
		Txtr imageBUI(WHITE, (baseFileName + "bui.bmp").c_str());

		// Set the font image size
		this->fontImageSize = Vec(image.getWidth(), image.getHeight());

		// Set character height
		this->charHeight = fontImageSize.y / fontImageNCharacters.y;

		// Set char basewidth
		this->charBaseWidth = fontImageSize.x / fontImageNCharacters.x;

		// Create the combined font texture
		Txtr combinedFont(nFontImagesCombined.x * fontImageSize.x,
						  nFontImagesCombined.y * fontImageSize.y);

		// Draw all font images to the combined font image
		image.copyTo(&combinedFont, fontImagePos[0].x * fontImageSize.x,
									fontImagePos[0].y * fontImageSize.y);
		imageB.copyTo(&combinedFont, fontImagePos[B].x * fontImageSize.x,
									 fontImagePos[B].y * fontImageSize.y);
		imageU.copyTo(&combinedFont, fontImagePos[U].x * fontImageSize.x,
									 fontImagePos[U].y * fontImageSize.y);
		imageBU.copyTo(&combinedFont, fontImagePos[B|U].x * fontImageSize.x,
									  fontImagePos[B|U].y * fontImageSize.y);
		imageI.copyTo(&combinedFont, fontImagePos[I].x * fontImageSize.x,
									 fontImagePos[I].y * fontImageSize.y);
		imageBI.copyTo(&combinedFont, fontImagePos[B|I].x * fontImageSize.x,
									  fontImagePos[B|I].y * fontImageSize.y);
		imageUI.copyTo(&combinedFont, fontImagePos[U|I].x * fontImageSize.x,
									  fontImagePos[U|I].y * fontImageSize.y);
		imageBUI.copyTo(&combinedFont, fontImagePos[B|U|I].x * fontImageSize.x,
									   fontImagePos[B|U|I].y * fontImageSize.y);

		//// temp debug test
		//combinedFont.setPixel(4, 4, Txtr::Pixel4(0, 0, 150, 255));
		//combinedFont.setPixel(4, 5, Txtr::Pixel4(0, 0, 150, 255));
		//combinedFont.setPixel(5, 4, Txtr::Pixel4(0, 0, 150, 255));
		//combinedFont.setPixel(5, 5, Txtr::Pixel4(0, 0, 150, 255));

		//std::cout << "font width: " << combinedFont.getWidth() << std::endl;
		//std::cout << "font height: " << combinedFont.getHeight() << std::endl;


		// Load font to the grafics card.
		this->combinedFontTxtrId = combinedFont.add(fontDirectory);

		//// temp debug test
		//this->combinedFontTxtrId = Txtr::loadAdd((baseFileName + ".bmp").c_str());


		// Load character widths
		std::string charWidthsFilename;				
		for(int b=0; b<2; ++b)
		{			
			for(int u=0; u<2; ++u)
			{				
				for(int i=0; i<2; ++i)
				{					
					charWidthsFilename = fontDirectory;
					charWidthsFilename += "/char_widths_";
					if (b) charWidthsFilename += 'b';					
					if (u) charWidthsFilename += 'u';
					if (i) charWidthsFilename += 'i';
					charWidthsFilename += ".dat";
					
					loadCharWidths(charWidthsFilename.c_str(), charBaseWidth, &(this->charWidths[b*B | u*U | i*I][0]));			
				}
			}
		}

	}
	
	int Font::writeCharToVtxArr(char c, int mods, Color3f color, GLfloat *vtxArr, GLfloat *colorArr, GLfloat *txtrCoordArr, Pos pos, float size) const
	{		
		assert((mods >= 0) && checkFlags(mods, ALLOWED_MODS));


		// Write to vertex array
		float charW = static_cast<float>(getCharWidth(c, mods)) * size;
		float charH = static_cast<float>(charHeight) * size;
		float x = static_cast<float>(pos.x);
		float y = static_cast<float>(pos.y);
		
		vtxArr[0] = x;
		vtxArr[1] = y;
		vtxArr[2] = 0;

		vtxArr[3] = x + charW;
		vtxArr[4] = y;
		vtxArr[5] = 0;

		vtxArr[6] = x + charW;
		vtxArr[7] = y + charH;
		vtxArr[8] = 0;

		vtxArr[9] = x;
		vtxArr[10] = y + charH;
		vtxArr[11] = 0;


		// Write to color array
		colorArr[0] = color.r;
		colorArr[1] = color.g;
		colorArr[2] = color.b;

		colorArr[3] = color.r;
		colorArr[4] = color.g;
		colorArr[5] = color.b;

		colorArr[6] = color.r;
		colorArr[7] = color.g;
		colorArr[8] = color.b;

		colorArr[9] = color.r;
		colorArr[10] = color.g;
		colorArr[11] = color.b;


		/**
		 * --------------------------------------
		 *		texture coordinate array
		 * --------------------------------------
		 */
		
		// Find basepixel of the font image.
		Pos coord(fontImagePos[mods].x * fontImageSize.x,
					  fontImagePos[mods].y * fontImageSize.y);

		// Calculate column and row from bottom of fontimage
		int rowLength = fontImageNCharacters.x;
		int charRow = (N_CHARS-c-1) / rowLength;
		int charCol = c % rowLength;

		coord.x += charCol * charBaseWidth;
		coord.y += charRow * charHeight;

		coord.x += (charBaseWidth - getCharWidth(c, mods)) / 2;


		// Translate to floating s and t coordinates.

		double combinedWidthD = static_cast<double>((fontImageSize.x * nFontImagesCombined.x));
		double combinedHeightD = static_cast<double>((fontImageSize.y * nFontImagesCombined.y));

		double coordCharWidth = static_cast<double>(charWidths[mods][c]) / combinedWidthD;
		double coordCharHeight = static_cast<double>(charHeight) / combinedHeightD;
	
		//coordCharWidth = 0.33f;
		//coordCharHeight = 0.33f;

		double s = static_cast<double>(coord.x) / combinedWidthD;
		double t = static_cast<double>(coord.y) / combinedHeightD;		
		
		// Write to texture coordinate array
		txtrCoordArr[0] = static_cast<float>(s);
		txtrCoordArr[1] = static_cast<float>(t);

		txtrCoordArr[2] = static_cast<float>(s + coordCharWidth);
		txtrCoordArr[3] = static_cast<float>(t);

		txtrCoordArr[4] = static_cast<float>(s + coordCharWidth);
		txtrCoordArr[5] = static_cast<float>(t + coordCharHeight);

		txtrCoordArr[6] = static_cast<float>(s);
		txtrCoordArr[7] = static_cast<float>(t + coordCharHeight);

		return static_cast<int>(charW + 0.5f);

	}


	int Font::isConsistent() const
	{
		// Must be one mod symbol for each mod.
		if (std::strlen(MOD_SYMBOLS) != N_MODS) return false;
		
		// Must be space for at least one font image for each mod combination.
		if (nFontImagesCombined.x * nFontImagesCombined.y >= N_MOD_COMBINATIONS) return false;

		// Test that every font image has it own position in the combined 2-dimensional array
		{
			const Vec &size = nFontImagesCombined;
			bool *testArr = new bool[size.x * size.y];
			zeroFun(testArr, size.x * size.y);
			for(int i=0; i<N_MOD_COMBINATIONS; ++i)
			{
				// Must be within bounds 
				if (fontImagePos[i].x >= size.x) return false;
				if (fontImagePos[i].y >= size.y) return false;

				int testArrIndex = fontImagePos[i].y *size.x + fontImagePos[i].x;
				 
				// If another fontImage already occupies this position something is wrong
				if (testArr[testArrIndex]) return false;

				// Mark position occupied.
				testArr[testArrIndex] = true;
			}
			
			delete[] testArr;
		}

		return true;
	}
};

#endif