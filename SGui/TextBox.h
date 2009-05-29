#ifndef _STATE_GUI_TEXT_BOX_H_
#define _STATE_GUI_TEXT_BOX_H_

#include "Text.h"
#include "RenderObj.h"

namespace SGui
{
	class TextBox : public RenderObj
	{
	private:
		//Pos pos;
		//Vec size;

		Font *font;
		std::string textString;

		bool updateNeeded;


		// ------ vtx array stuff --------
		int nVtx;

		GLfloat *vtxArr;
		GLfloat *colorArr;
		GLfloat *txtrCoordArr;

		int xAlign;
		int yAlign;

	public:
		
		bool autoUpdate;
		
		TextBox();

		TextBox(const Pos &pos, const Vec &size, Font *font = NULL, int xAlign = ALIGN_LEFT, int yAlign = ALIGN_TOP, bool autoUpdate = false, const std::string &textString = std::string());			

		~TextBox();

		bool updateVtxArrs();

		void setPos(const Pos &pos);
		void setSize(const Vec &size);

		void setFont(Font *font);

		inline std::string getTextString() const		{ return textString; }
		void setTextString(const std::string &textString);

		inline void clearTextString()					{ setTextString(std::string()); }

		void render();

		bool isConsistent();
		
	};

};

#endif