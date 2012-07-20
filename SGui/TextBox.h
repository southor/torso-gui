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
		int nVtxCapacity;

		gl_float *vtxArr;
		gl_float *colorArr;
		gl_float *txtrCoordArr;

		int xAlign;
		int yAlign;

	public:
		
		bool autoUpdate;
		
		TextBox();

		TextBox(const Pos &pos, const Vec &size, Font *font = nullptr, int xAlign = ALIGN_LEFT, int yAlign = ALIGN_TOP, bool autoUpdate = false, const std::string &textString = std::string());			

		~TextBox();

		bool updateVtxArrs();

		void setPos(const Pos &pos);
		void setSize(const Vec &size);

		void setFont(Font *font);

		inline std::string getTextString() const		{ return textString; }
		void setTextString(const std::string &textString);

		inline void clearTextString()					{ setTextString(std::string()); }

		void render(RenderContext *renderContext);

		bool isConsistent();
		
	};

};

#endif