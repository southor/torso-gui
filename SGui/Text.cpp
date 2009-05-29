#ifndef _STATE_GUI_TEXT_CPP_
#define _STATE_GUI_TEXT_CPP_

#include "Text.h"

namespace SGui
{
	const Color Text::DEFAULT_COLOR = Color(static_cast<uchar>(0));

	const int Text::DEFAULT_MODS = 0;

	const char Text::ON_STRING[] = "on";
	const char Text::OFF_STRING[] = "off";

	Text::WhiteSpace::WhiteSpace(const Font *font, char whiteSpaceChar, int mods) : c(whiteSpaceChar)
	{				
		assert(isWhiteSpace(whiteSpaceChar));				
		incWidth(font->getCharWidth(whiteSpaceChar, mods));
	}

	Text::Unit* Text::Word::split(int maxWidth)
	{
		// Find split point
		int sum = 0;
		int i;
		for(i=0; i<getNChars(); ++i)
		{					
			int newSum = sum + textChars[i].getWidth(font);
			if (newSum > maxWidth) break;
			sum = newSum;
		}
		width = sum;
		
		// Create the new Word
		Word *newWord = new Word(font);				
		
		// copy chars
		for(; i<getNChars(); ++i)
		{
			newWord->addChar(textChars[i]);
		}

		// remove chars that have been copied
		for(int j=(getNChars()-1); j>=i; --j)
		{
			textChars.pop_back();
		}

		// Transfer returns to the new word
		newWord->nReturns = nReturns;
		nReturns = 0;

		return newWord;
	}

	int Text::Word::writeToVtxArr(GLfloat*& vtxArr, GLfloat*& colorArr, GLfloat*& txtrCoordArr, Pos pos, float size) const
	{
		for(int i=0; i<getNChars(); ++i)
		{					
			pos.x += textChars[i].writeToVtxArr(font, vtxArr, colorArr, txtrCoordArr, pos, size);
		}
		return getWidth();
	}

	bool Text::Word::isConsistent() const
	{
	/*	if (nChars < 0) return false;
		else if (nChars == 0) return !textCharArr;
		else
		{					
			for(int i=0; i<nChars; ++i)
			{
				if(textCharArr[i].isConsistent() == false) return false;
			}									
			return true;
		} */
		
		if (!Unit::isConsistent()) return false;				

		int nTextChars = static_cast<int>(textChars.size());
		for(int i=0; i<nTextChars; ++i)
		{
			if (textChars[i].isConsistent() == false) return false;
		}

		return true;
	}

	void Text::deleteTextUnits()
	{
		int ntextUnits = static_cast<int>(textUnits.size());
		for(int i=0; i<ntextUnits; ++i)
		{
			delete textUnits[i];
		}
	}

	int Text::countNChars()
	{
		int returnVal = 0; 			
		for(int i=0; i<getNUnits(); ++i)
		{
			returnVal += textUnits[i]->getNChars();
		}

		return returnVal;
	}

	void Text::moveVtxsX(GLfloat *vtxArr, int nFloats, int offset)
	{
		GLfloat offsetF = static_cast<GLfloat>(offset);
		for(int i=0; i<nFloats; i += Font::N_FLOATS_PER_VTX)
		{
			vtxArr[i] += offsetF;			
		}
	}

	void Text::moveVtxsY(GLfloat *vtxArr, int nFloats, int offset)
	{
		GLfloat offsetF = static_cast<GLfloat>(offset);
		for(int i=1; i<nFloats; i += Font::N_FLOATS_PER_VTX)
		{
			vtxArr[i] += offsetF;
		}
	}



	// --------------------------------------------------------------------------------------
	// ------------------------------------- public -----------------------------------------
	// --------------------------------------------------------------------------------------

	Text::Text(Font *font, const char *textString) : font(font), textUnits()
	{
		assert(font);
		assert(textString);
		
		static const char RETURN[] = "/n";
		int returnLength = static_cast<int>(std::strlen(RETURN));
		int onLength = static_cast<int>(std::strlen(ON_STRING));
		int offLength = static_cast<int>(std::strlen(OFF_STRING));

		int currentMods(0);
		Color currentColor(static_cast<uchar>(0));

		//newWord();
		Word *lastWord = NULL;
		addUnit(new Unit());

		bool acceptSpecialChar = false;
		while(*textString != 0)
		{
			if (beginEq(RETURN, returnLength, textString))
			{					
				textUnits.back()->addReturn();
				textString += returnLength;
				lastWord = NULL;
			}
			else if ((*textString == SPECIAL_CHAR) && !acceptSpecialChar)
			{
				++textString;

				if (*textString == SPECIAL_CHAR)
				{
					acceptSpecialChar = true;
				}
				else
				{						
					int modBit = 0;						
					
					switch(*textString)
					{
					case COLOR_CHAR:
						++textString;
						
						// must be a full hex color specification
						assert(atLeastLength(textString, 6));

						currentColor = Color(textString);
						textString += 6;
					break;
					case BOLD_CHAR:
						++textString;
						modBit = Font::BOLD;
					break;
					case UNDERLINE_CHAR:
						++textString;
						modBit = Font::UNDERLINE;							
					break;
					case ITALIC_CHAR:
						++textString;
						modBit = Font::ITALIC;
					break;
					default:
						// TODO what to do in releaes mode, and what to do in debug?
						assert(false); //character not allowed
					};

					if (modBit != 0)
					{
						if (beginEq(ON_STRING, onLength, textString))
						{
							currentMods |= modBit;
							textString += onLength;
						}
						else
						{
							assert(beginEq(OFF_STRING, offLength, textString));
							currentMods &= ~modBit;
							textString += offLength;
						}							
						modBit = 0;
					}
					
					assert(*textString == END_CHAR);
					++textString;
				}
			}
			else if (WhiteSpace::isWhiteSpace(*textString))
			{
				addUnit(new WhiteSpace(font, *textString, currentMods));
				++textString;
			}					
			else
			{
				if (textUnits.back() != lastWord)
				{
					lastWord = new Word(font);
					addUnit(lastWord);
				}
				
				lastWord->addChar(Char(*textString, currentMods, currentColor));
				++textString;

				acceptSpecialChar = false;
			}
		}

		nChars = countNChars();
	}

	void Text::writeFieldToVtxArr(GLfloat *vtxArr, GLfloat *colorArr, GLfloat *txtrCoordArr, Pos pos, Vec fieldSize, int xAlign, int yAlign, float size)
	{
		//assert(checkFlags(xAlign, ALLOWED_X_ALIGNS));
		//assert(checkFlags(yAlign, ALLOWED_Y_ALIGNS));
		assert(checkAlternative(xAlign, N_X_ALIGNS));
		assert(checkAlternative(yAlign, N_Y_ALIGNS));
		
		Unit *textUnit;
		
		int charHeight = font->getCharHeight();		
		
		// local vertex array pointers, points within the hole array
		GLfloat *currVtxArr = vtxArr;
		GLfloat *currColorArr = colorArr;
		GLfloat *currTxtrCoordArr = txtrCoordArr;

		//pointer to the adress where the current row starts
		GLfloat *rowStartVtxArr = vtxArr;

		Pos lPos(0, fieldSize.y - charHeight); // local position within field
		if (lPos.y < 0) return;
		
		int i=0;
		int spaceInARow = 0;
		while(i<getNUnits())
		{				
			textUnit = textUnits[i];
			
			if (textUnit->isSpace()) ++spaceInARow;
			else spaceInARow = 0;

			int nReturns = 0;
			if ((lPos.x + textUnit->getWidth()) > fieldSize.x)
			{
				nReturns = 1;
				if (spaceInARow == 1)
				{
					++i;						
				}
				else
				{
					if (lPos.x == 0)
					{
						// must split.
						Unit *newUnit = textUnit->split(fieldSize.x);
						lPos.x += textUnit->writeToVtxArr(currVtxArr, currColorArr, currTxtrCoordArr, pos + lPos, size);
						assert(textUnit->getNReturns() == 0);
						
						textUnits[i] = newUnit;
					}
				}				
			}
			else
			{
				lPos.x += textUnit->writeToVtxArr(currVtxArr, currColorArr, currTxtrCoordArr, pos + lPos, size);
				nReturns = textUnit->getNReturns();
				++i;
			}

			if (nReturns > 0) // if we should advance to a new row
			{
				// align the row x
				if (xAlign != ALIGN_LEFT) // if xAlign == ALIGN_LEFT, nothing to do
				{
					int xOffset = (fieldSize.x - lPos.x);
					if (xAlign == ALIGN_MIDDLE) xOffset /= 2;					
					moveVtxsX(rowStartVtxArr, currVtxArr - rowStartVtxArr, xOffset);
				}

				// check if end of the field area
				if ((lPos.y - charHeight * nReturns) < 0) break;

				// advance to next row			
				lPos.x = 0;
				lPos.y -= charHeight * nReturns;
				rowStartVtxArr = currVtxArr;
			}
		} // end while

		int vtxArrNFloats = getVtxArrNFloats();

		// align the hole field y
		if (yAlign != ALIGN_TOP) // if xAlign == ALIGN_TOP, nothing to do
		{
			int yOffset = /* fieldSize.y */ -  lPos.y;
			if (yAlign == ALIGN_MIDDLE) yOffset /= 2;					
			moveVtxsY(vtxArr, vtxArrNFloats, yOffset);
		}

		// make sure the rest is not rendered
		//int renderNFloats = currVtxArr - vtxArr;
		//moveVtxsY(currVtxArr, vtxArrNFloats - renderNFloats, - INT_MIN);

	}
};

#endif