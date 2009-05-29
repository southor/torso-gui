#ifndef _STATE_GUI_BOX_H
#define _STATE_GUI_BOX_H

#include "RenderObj.h"


#include "gl_includes.h"
//#include <GL/gl.h>

namespace SGui
{
	
	
	/**
	 * Can render itself in 2 modes. 
	 * FilledMode: The Box will be solid filled with the chosen color.
	 * EdgeMode: Only the Edges of the box will be drawn with lines with the chosen color and lineWidth.
	 */
	class Box : public RenderObj
	{
	private:
		
		GLuint displayList;
		bool changed; // was a change made?
		

		//bool filled;

		uchar lineWidth; // if lineWidth == 1 then use filled render mode
		Color4f color;
		
		// will run all render code
		void renderTo();

		void setDisplayList(GLenum mode);


	public:
		
		// Wil be set to "filled" mode.
		Box();

		/**
		 * @param lineWidth If lineWidth = 0 is passed (default argument) "filled mode" will be used. 
		 *		  Otherwise edge mode will be used and the passed lineWidth will determine the thickness of the edges.
		 *		  But the value will be clamped to 255 if larger.
		 */
		Box(const Pos &pos, const Vec &size, const Color4f &color, int lineWidth = 0);


		void setPos(Pos pos);	
		void setSize(Vec size);

		inline void setColor(const Color4f &color)		{ this->color = color;
														  changed = true; }

		//inline void setFilled(bool filled)			{ this->filled = filled;
		//												  changed = true; }


		// The Box will be solid filled with the color.
		inline void setFilledMode()						{ this->lineWidth = 0;
														  changed = true; }

		/**
		 * Will only draw borderlines and will not be filled.
		 * @param lineWidth Will be clamped between: [1 255]
		 */
		void setEdgeMode(int lineWidth);




		void render();

	};
};

#endif