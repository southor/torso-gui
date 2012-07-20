#ifndef _STATE_GUI_TEXT_H_
#define _STATE_GUI_TEXT_H_

#include "font.h"
#include "functions.h"
#include "basic_converters.h"

namespace SGui
{


	class Text
	{
	private:

		class Word;

		class Unit
		{
		protected:						
			int width;

			// The number of returns that follows this text unit.
			int nReturns;		

			inline void incWidth(int value)
			{
				dAssert(value >= 0);
				this->width += value;
			}
			
		public:

			Unit() : width(0), nReturns(0)				{}
			virtual ~Unit()								{}

			//virtual bool isWord()						{ return false; }

			//virtual Word* toWord()					{ dAssert(false);
			//											  return nullptr; }

			virtual bool isSpace()						{ return false; }

			inline int getWidth() const					{ return width; }

			inline int getNReturns() const				{ return nReturns; }

			virtual int getNChars() const				{ return 0; }

			inline void addReturn()						{ ++(this->nReturns); }

			virtual int writeToVtxArr(gl_float*& vtxArr, gl_float*& colorArr, gl_float*& txtrCoordArr, Pos pos, float size = 1.0f) const
			{
				return 0;
			}

			/** 
			 * Will split unit so that it will be
			 * equal or shorter than maxWidth
			 */
			virtual Unit* split(int maxWidth)
			{
				// A unit have zero width, split should not be called.
				dAssert(false);
				return nullptr;
			}

			//inline void addReturns(int nReturns)		{ this->nReturns += nReturns; }

			// debug
			inline bool isConsistent() const			{ return (width >= 0) && (nReturns >= 0); }
		};

		class WhiteSpace : public Unit
		{
		private:	
			char c;

			enum
			{
				SPACE = ' ',
				TAB = '/t'
			};

		public:

			WhiteSpace(const Font *font, char whiteSpaceChar, int mods);

			inline bool isSpace()							{ return (c == ' '); }

			static bool isWhiteSpace(char c)
			{
				switch (c)
				{
				case SPACE:
					return true;				
				case TAB:
					return true;
				default:
					return false;
				}
			}

			int writeToVtxArr(gl_float*& vtxArr, gl_float*& colorArr, gl_float*& txtrCoordArr, Pos pos, float size = 1.0f) const
			{
				return getWidth();
			}

			inline bool isConsistent()	
			{ 
				return (Unit::isConsistent() && isWhiteSpace(c));
			}
		};
	
		class Char
		{
		private:			

			char c;
			int mods;
			Color color;

		public:

			static const char DEFAULT_CHAR = 0;

			Char() : c(DEFAULT_CHAR), mods(0), color(255, 255, 255)			{}

			Char(char c, int mods, Color color) : c(c), mods(mods), color(color)
			{
				dAssert(isConsistent());
			}

			inline int getWidth(const Font *font)				{ return font->getCharWidth(c, mods); }

			inline int writeToVtxArr(const Font *font, gl_float*& vtxArr, gl_float*& colorArr, gl_float*& txtrCoordArr, Pos pos, float size = 1.0f) const
			{
				Color3f color3f;
				color3bToColor3f(color, color3f);

				//int returnVal = font->writeCharToVtxArr(c, mods, Color3f(static_cast<float>(color.r) / 255.0f,
				//														  static_cast<float>(color.g) / 255.0f,
				//														  static_cast<float>(color.b) / 255.0f),
				//														  vtxArr, colorArr, txtrCoordArr, pos, size);
				int returnVal = font->writeCharToVtxArr(c, mods, color3f, vtxArr, colorArr, txtrCoordArr, pos, size);
				
				vtxArr += Font::N_VTX_FLOATS_PER_CHAR;
				colorArr += Font::N_COLOR_FLOATS_PER_CHAR;
				txtrCoordArr += Font::N_TXTR_COORD_FLOATS_PER_CHAR;

				return returnVal;
			}

			inline bool isConsistent()	const					{ return checkFlags(mods, Font::ALLOWED_MODS); }
		};

		class Word : public Unit
		{
		private:

			const Font *font;
			std::vector<Char> textChars;
		public:
			
			
			Word(const Font *font) : font(font), textChars()
			{}

			//bool isWord()								{ return true; }

			//Word* toWord()							{ return reinterpret_cast<Word*>(this); }

			
			inline int getNChars() const				{ return static_cast<int>(textChars.size()); }


			inline void addChar(Char &textChar)
			{ 
				// once you have added a return, only more returns is allowed to be added.
				dAssert(getNReturns() == 0);
				
				dAssert(textChar.isConsistent());
				
				incWidth(textChar.getWidth(font));
				textChars.push_back(textChar);
			}

			// overrided
			Unit* split(int maxWidth);
						
			int writeToVtxArr(gl_float*& vtxArr, gl_float*& colorArr, gl_float*& txtrCoordArr, Pos pos, float size = 1.0f) const;
			

			bool isConsistent() const;
		};


		
		Font *font;
		std::vector<Unit*> textUnits;

		int nChars;
		

		inline void addUnit(Unit *unit)					{ textUnits.push_back(unit); }

		void deleteTextUnits();

		int getNUnits()									{ return static_cast<int>(textUnits.size()); }

		int countNChars();

		void moveVtxsX(gl_float *vtxArr, int nFloats, int offset);

		void moveVtxsY(gl_float *vtxArr, int nFloats, int offset);

	public:


		static const Color DEFAULT_COLOR;

		static const int DEFAULT_MODS;


		const static int SPECIAL_CHAR = '~';

		
		static const char COLOR_CHAR = 'c';
		
		static const char BOLD_CHAR = 'b';
		static const char UNDERLINE_CHAR = 'u';
		static const char ITALIC_CHAR = 'i';

		static const char ON_STRING[];
		static const char OFF_STRING[];
		
		static const char END_CHAR = '.';

		/*
		
		~bon.		
		~cFFAAFF.
		~cffcc00.
		
		*/
		

		Text(Font *font, const char *textString);

		~Text()											{ deleteTextUnits(); }


		inline int getNChars() const					{ return nChars; }


		inline int getVtxArrNFloats()					{ return Font::N_VTX_FLOATS_PER_CHAR * getNChars(); }

		inline int getColorArrNFloats()					{ return Font::N_COLOR_FLOATS_PER_CHAR * getNChars(); }

		inline int getTxtrCoordArrNFloats()				{ return Font::N_TXTR_COORD_FLOATS_PER_CHAR * getNChars(); }

		inline int getVtxArrNVtx()						{ return Font::N_VTX_PER_CHAR * getNChars(); }


		void writeFieldToVtxArr(gl_float *vtxArr, gl_float *colorArr, gl_float *txtrCoordArr, Pos pos, Vec fieldSize, int xAlign = ALIGN_LEFT, int yAlgin = ALIGN_TOP, float size = 1.0f);


	};

};

#endif