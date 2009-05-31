#ifndef _STATE_GUI_TEXTURE_CPP
#define _STATE_GUI_TEXTURE_CPP

#include "Txtr.h"
#include "function_templates.h"

#include <fstream>

//solving LNK error
#include "function_templates.inl"

#include "gl_includes.h"

namespace SGui
{
	std::map<std::string, GLuint> Txtr::txtrIdPool = std::map<std::string, GLuint>();


	// **************************************************************************************************************
	// *------------------------------------------------------------------------------------------------------------*
	// *--------------------------------------------- PUBLIC -------------------------------------------------------*
	// *------------------------------------------------------------------------------------------------------------*
	// **************************************************************************************************************


	Txtr::Txtr() : pixels(NULL), width(0), height(0)
	{
	}

	Txtr::Txtr(const Txtr &txtr) : pixels(NULL), width(txtr.getWidth()), height(txtr.getHeight())
	{
		dAssert(txtr.isConsistent());
		
		if (txtr.hasImage())
		{
			pixels = new Pixel4[width * height];
			for(uint i=0; i<width*height; ++i)
			{
				pixels[i] = txtr.pixels[i];
			}
		}
	}

	Txtr::Txtr(GLuint w, GLuint h) : pixels(NULL), width(0), height(0)
	{
		createImage(w, h);
	}

	Txtr::Txtr(const char *colorsFileName, GLubyte alpha) : pixels(NULL), width(0), height(0)
	{
		load(colorsFileName, alpha);
	}

	Txtr::Txtr(const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint antiAliasing) : pixels(NULL), width(0), height(0)
	{
		load(colorsFileName, alpha, transparentColor, antiAliasing);
	}

	Txtr::Txtr(const char *colorsFileName, const char *alphaFileName) : pixels(NULL), width(0), height(0)
	{
		load(colorsFileName, alphaFileName);
	}

	Txtr::Txtr(Pixel3 color, const char *alphaFileName) : pixels(NULL), width(0), height(0)
	{
		load(color, alphaFileName);
	}

	Txtr &Txtr::operator=(const Txtr &txtr)
	{
		dAssert(txtr.isConsistent());
		dAssert(isConsistent());
		
		removeImage();

		if (txtr.hasImage())
		{
			this->width = txtr.width;
			this->height = txtr.height;
			pixels = new Pixel4[txtr.width * txtr.height];
			for(uint i=0; i<txtr.width*txtr.height; ++i)
			{
				this->pixels[i] = txtr.pixels[i];
			}
		}

		return *this;
	}


	Txtr::~Txtr(void)
	{
		if (pixels != NULL) delete[] pixels;
	}

	void Txtr::fillColor(const Pixel3 &color)
	{
		for(uint i=0; i<width*height; ++i)
		{
			pixels[i].r = color.r;
			pixels[i].g = color.g;
			pixels[i].b = color.b;
		}
	}
	                  
	Txtr::Pixel4 Txtr::getInterpoolatedPixel(float x, float y) const
	{
		dAssert(between(x, 0.0f, static_cast<float>(width)-1.0f));
		if (!between(y, 0.0f, static_cast<float>(height)-1.0f))
			dAssert(between(y, 0.0f, static_cast<float>(height)-1.0f));

		uint leftX = static_cast<uint>(x);
		uint lowY = static_cast<uint>(y);

		float localX = x - static_cast<float>(leftX);
		float localY = y - static_cast<float>(lowY);

		float lowLeftWeight = (1.0f-localX)*(1.0f-localY);
		float lowRightWeight = localX*(1.0f-localY);
		float topLeftWeight = (1.0f-localX)*localY;
		float topRightWeight = localX*localY;

		Pixel4 pixel;

		const Pixel4 &lowLeftPixel = getPixel(leftX, lowY);
		const Pixel4 &lowRightPixel = getPixel(leftX+1, lowY);
		const Pixel4 &topLeftPixel = getPixel(leftX, lowY+1);
		const Pixel4 &topRightPixel = getPixel(leftX+1, lowY+1);
		
		pixel.r = static_cast<GLubyte>(
				  static_cast<float>(lowLeftPixel.r) * lowLeftWeight
				+ static_cast<float>(lowRightPixel.r) * lowRightWeight
				+ static_cast<float>(topLeftPixel.r) * topLeftWeight
				+ static_cast<float>(topRightPixel.r) * topRightWeight);

		pixel.g = static_cast<GLubyte>(
				  static_cast<float>(lowLeftPixel.g) * lowLeftWeight
				+ static_cast<float>(lowRightPixel.g) * lowRightWeight
				+ static_cast<float>(topLeftPixel.g) * topLeftWeight
				+ static_cast<float>(topRightPixel.g) * topRightWeight);

		pixel.b = static_cast<GLubyte>(
				  static_cast<float>(lowLeftPixel.b) * lowLeftWeight
				+ static_cast<float>(lowRightPixel.b) * lowRightWeight
				+ static_cast<float>(topLeftPixel.b) * topLeftWeight
				+ static_cast<float>(topRightPixel.b) * topRightWeight);

		pixel.a = static_cast<GLubyte>(
				  static_cast<float>(lowLeftPixel.a) * lowLeftWeight
				+ static_cast<float>(lowRightPixel.a) * lowRightWeight
				+ static_cast<float>(topLeftPixel.a) * topLeftWeight
				+ static_cast<float>(topRightPixel.a) * topRightWeight);

		return pixel;
	}

	bool Txtr::createImage(GLuint w, GLuint h)
	{		
		bool hadImage = hasImage();
		if (hadImage) removeImage();

		if ((w == 0) || (h == 0))
		{
			dAssert((w == 0) && (h == 0));
		}
		else
		{			
			this->width = w;
			this->height = h;
			pixels = new Pixel4[w * h];			
		}

		return !hadImage;
	}

	bool Txtr::removeImage()
	{
		dAssert(isConsistent());
		
		if (hasImage())
		{
			delete[] pixels;
			pixels = NULL;
			width = 0;
			height = 0;
			return true;
		}
		return false;
	}

	void Txtr::load(const char *colorsFileName, GLubyte alpha)
	{
		removeImage();
		if (colorsFileName) loadColors(colorsFileName);
		setAlpha(alpha);
	}

	void Txtr::load(const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint transparentAA)
	{		
		load(colorsFileName, alpha);
		setTransparent(transparentColor, transparentAA);
	}

	void Txtr::load(const char *colorsFileName, const char *alphaFileName)
	{
		removeImage();
		if (colorsFileName) loadColors(colorsFileName);
		if (alphaFileName && hasImage()) loadAlpha(alphaFileName, 255);
		else setAlpha(255);
	}

	void Txtr::load(Pixel3 color, const char *alphaFileName)
	{
		removeImage();
		loadAlpha(alphaFileName, 255, true);
		fillColor(color);
	}





	GLuint Txtr::add(const char *name)
	{
		dAssert(isConsistent());

		std::string nameStr(name);
		GLuint txtrId; // result variable

		std::map<std::string, GLuint>::iterator it = txtrIdPool.find(nameStr);
		if (it == txtrIdPool.end())
		{
			if (hasImage())
			{				
				glGenTextures(1, &txtrId);
 				glBindTexture(GL_TEXTURE_2D, txtrId);
				glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)pixels);		
				
				// Perform these here?
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
			else
			{
				txtrId = defaultTxtr;
			}

			// add to pool
			txtrIdPool[nameStr] = txtrId;
		}
		else
		{
			// get from pool
			txtrId = it->second;
		}


		//if (hasImage())
		//{
		//	std::map<std::string, GLuint>::iterator it = txtrIdPool.find(std::string(name));
		//	if (it == txtrIdPool.end())
		//	{

		//		glGenTextures(1, &txtrId);
 	//			glBindTexture(GL_TEXTURE_2D, txtrId);
		//		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)pixels);		
		//		
		//		// Perform these here?
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//		// add to pool
		//		txtrIdPool[std::string(name)] = txtrId;
		//	}
		//	else
		//	{
		//		// get from pool
		//		txtrId = it->second;
		//	}
		//}
		//else
		//{
		//	txtrId = defaultTxtr;

		//	// add to pool
		//	txtrIdPool[std::string(name)] = txtrId;
		//}
		
		return txtrId;
	}

	void Txtr::setAlpha(GLubyte alpha)
	{
		for(uint i=0; i<width*height; ++i)
		{
			pixels[i].a = alpha;
		}
	}

	void Txtr::setAlpha(GLubyte alpha, Pixel3 transparentColor, uint antiAliasing)
	{
		setAlpha(alpha);
		setTransparent(transparentColor, antiAliasing);
	}

	void Txtr::setTransparent(Pixel3 transparentColor, uint antiAliasing)
	{
		if (antiAliasing < 1) antiAliasing = 1;
		
		for(uint i=0; i<width*height; ++i)
		{			
			uint dist = 0;
			dist += abs((pixels+i)->r - transparentColor.r);
			dist += abs((pixels+i)->g - transparentColor.g);
			dist += abs((pixels+i)->b - transparentColor.b);
	
			GLubyte alpha;
			if (dist >= antiAliasing) alpha = 255;
			else if (dist == 0) alpha = 0;
			else alpha = 255 * dist / antiAliasing;
			(pixels+i)->a = alpha;
		}
	}



	bool Txtr::isConsistent() const
	{
		return (((pixels == NULL) || (width == 0) || (height == 0))
			? ((pixels == NULL) && (width == 0) && (height == 0)) : true);
	}



	// **************************************************************************************************************
	// *------------------------------------------------------------------------------------------------------------*
	// *--------------------------------------------- PRIVATE ------------------------------------------------------*
	// *------------------------------------------------------------------------------------------------------------*
	// **************************************************************************************************************

	GLuint Txtr::defaultTxtr = 0;

	void Txtr::loadColors(const char *fileName, bool initialize)
	{
		dAssert(isConsistent());
		dAssert(!hasImage() || !initialize);

		GLuint w;
		GLuint h;
		Pixel3 *colorPixels = loadFile(fileName, &w, &h);
		//Pixel3 *colorPixels = loadFile(fileName, &height, &width);
		if (colorPixels)
		{
			if (initialize)
			{
				width = w;
				height = h;
			}
			
			if ((w == width) && (h == height))
			{
				uint size = width*height;
				pixels = new Pixel4[size];
				for(uint i=0; i<size; ++i)
				{
					pixels[i].r = colorPixels[i].r;
					pixels[i].g = colorPixels[i].g;
					pixels[i].b = colorPixels[i].b;
				}
			}

			delete[] colorPixels;
			
		}
	}

	void Txtr::loadAlpha(const char *fileName, GLubyte defaultAlpha, bool initialize)
	{	
		dAssert(isConsistent());
		dAssert(!hasImage() || !initialize);
		
		GLuint w;
		GLuint h;	
		Pixel3 *colorPixels = loadFile(fileName, &w, &h);
		if (colorPixels)
		{
			if (initialize)
			{
				width = w;
				height = h;
				pixels = new Pixel4[w*h];
			}

			if ((w == width) && (h == height))
			{
				for(uint i=0; i<width*height; ++i)
				{
					//pixels[i].a = static_cast<GLubyte>(colorPixels[i].getBWColor() / 3);
					pixels[i].a = colorPixels[i].getBWColor();
				}
			}
			else
			{
				for(uint i=0; i<width*height; ++i)
				{
					pixels[i].a = defaultAlpha;
				}
			}
			delete[] colorPixels;
		}
	}

	void Txtr::copyTo(Txtr *txtr, int x, int y)
	{
		uint targetStartX = static_cast<uint>(maxFun(0, x));
		uint targetStartY = static_cast<uint>(maxFun(0, y));
		
		uint targetEndX = minFun(txtr->getWidth(), x + this->getWidth());
		uint targetEndY = minFun(txtr->getHeight(), y + this->getHeight());

		uint srcStartX = targetStartX - x;
		uint srcStartY = targetStartY - y;

		uint copyW = targetEndX - targetStartX;
		uint copyH = targetEndY - targetStartY;

		
		for(uint yi = 0; yi < copyH; ++yi)
		{
			for(uint xi = 0; xi< copyW; ++xi)
			{
				uint targetX = targetStartX + xi;
				uint targetY = targetStartY + yi;

				uint srcX = srcStartX + xi;
				uint srcY = srcStartY + yi;
				
				txtr->pixels[targetY * txtr->getWidth() + targetX]
							= this->pixels[srcY * this->getWidth() + srcX];
			}
		}

	}

	// **************************************************************************************************************
	// *------------------------------------------------------------------------------------------------------------*
	// *--------------------------------------------- STATIC -------------------------------------------------------*
	// *------------------------------------------------------------------------------------------------------------*
	// **************************************************************************************************************

	Txtr::Pixel3* Txtr::loadFile(const char *fileName, GLuint *w, GLuint *h)
	{
		long in;
		uint i;

		Pixel3 *pixels = NULL;

		std::ifstream imageFile;
		//if(filename != NULL) imageFile.open((const char*)fileName, ios::nocreate | ios::binary);
		if(fileName != NULL) imageFile.open((const char*)fileName, std::ios::binary);

		if((!(imageFile.good())) || fileName == NULL)
		{
			pixels = NULL;
			dAssert(false);
		}
		else
		{
			for(i=0;i<18;i++)
			{
				imageFile.read((char*)&in,sizeof(char));
			}			

			// read width
			imageFile.read((char*)w,sizeof(int));
			// read height
			imageFile.read((char*)h,sizeof(int));

			uint size = (*w)*(*h);

			for(i=0;i<28;i++)
			{
				imageFile.read((char*)&in,sizeof(char));
			}
			
			pixels = new Pixel3[size];
				
			GLuint x;
			for(GLuint y=0;y<*h;y++)
			{
				for(x=0;x<*w;x++)
				{
					i = (y*(*w)+x);
					// In a bitmap file: BGR
					// Reading to memory as: RGB
					imageFile.read((char*)&((pixels+i)->b),sizeof(char));
					imageFile.read((char*)&((pixels+i)->g),sizeof(char));
					imageFile.read((char*)&((pixels+i)->r),sizeof(char));
					
					//if(transparent == NULL) (pixels+i)->alpha = 255;
					//else if(((pixels+i)->red == transparent->red) && 
					//	((pixels+i)->green == transparent->green) &&
					//	((pixels+i)->blue == transparent->blue))
					//{	
					//	(pixels+i)->alpha = 0;
					//}
					//else (pixels+i)->alpha = 255;

					//imageFile.read((char*)(pixels+i+3),sizeof(char));
					//if ((*(pixels+i+0) == 255) && (*(pixels+i+1) == 255) && (*(pixels+i+2) == 255)) *(pixels+i+3) = 255;
					//else *(pixels+i+3) = 0;
				}
				
				imageFile.read((char*)&in,sizeof(char)*((*w)%4));
			}
			
			//this->pixels = pixels;
		}

		imageFile.close();
		
		return pixels;
	}

	GLuint Txtr::createDefaultTxtr()
	{
		//dAssert(defaultTxtr == NULL);
		
		Pixel4 pixel(127, 127, 127, 255);

		glGenTextures(1, &defaultTxtr);
		glBindTexture(GL_TEXTURE_2D, defaultTxtr);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)&pixel);
		txtrIdPool[std::string("DefaultTxtr")] = defaultTxtr;
		return defaultTxtr;
	}

	GLuint Txtr::getDefaultTxtrId()
	{
		return defaultTxtr;
	}

	GLuint Txtr::loadAddN(const char *name, const char *colorsFileName, GLubyte alpha)
	{
		Txtr t(colorsFileName, alpha);
		return t.add(name);
	}

	GLuint Txtr::loadAddN(const char *name, const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint antiAliasing)
	{
		Txtr t(colorsFileName, alpha, transparentColor, antiAliasing);
		return t.add(name);
	}

	GLuint Txtr::loadAddN(const char *name, const char *colorsFileName, const char *alphaFileName)
	{
		Txtr t(colorsFileName, alphaFileName);
		return t.add(name);
	}

	GLuint Txtr::loadAddN(const char *name, Pixel3 color, const char *alphaFileName)
	{
		Txtr t(color, alphaFileName);
		return t.add(name);
	}



	
	GLuint Txtr::loadAdd(const char *colorsFileName, GLubyte alpha)
	{
		return loadAddN(colorsFileName, colorsFileName, alpha);
	}

	GLuint Txtr::loadAdd(const char *colorsFileName, GLubyte alpha, Pixel3 transparentColor, uint antiAliasing)
	{
		return loadAddN(colorsFileName, colorsFileName, alpha, transparentColor, antiAliasing);
	}

	GLuint Txtr::loadAdd(const char *colorsFileName, const char *alphaFileName)
	{
		return loadAddN(colorsFileName, colorsFileName, alphaFileName);
	}

	GLuint Txtr::loadAdd(Pixel3 color, const char *alphaFileName)
	{
		return loadAddN(alphaFileName, color, alphaFileName);
	}

	void Txtr::clearLoaded()
	{
		std::map<std::string, GLuint>::iterator it = txtrIdPool.begin();
		std::map<std::string, GLuint>::iterator end = txtrIdPool.end();

		GLuint txtrId;
		for(;it != end; ++it)
		{
			txtrId = it->second;
			glDeleteTextures(1, &txtrId);
		}

		txtrIdPool.clear();
	}

	

	

};


#endif


