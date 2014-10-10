#ifndef _STATE_GUI_COLOR_H_
#define _STATE_GUI_COLOR_H_

#include "functions.h"

namespace SGui
{

	template <typename T> struct Color3
	{
		typedef T value_type;

		T r, g, b;

		Color3();
		Color3(const T& bw);
		Color3(const T& r, const T& g, const T& b);
		Color3(const char *str);
		explicit Color3(const T* p);

		operator T* ();
		operator const T* () const;

		Color3<T>& operator=(const Color3<T>& rhs);

		Color3<T>& operator+=(const Color3<T>& c);
		Color3<T>& operator-=(const Color3<T>& c);
		Color3<T>& operator*=(const T& s);
		Color3<T>& operator/=(const T& s);
		
	};
	
	template <typename T> struct Color4
	{
		typedef T value_type;

		T r, g, b, a;

		Color4();
		Color4(const T& bw, const T& a);
		Color4(const T& r, const T& g, const T& b, const T& a);
		Color4(const char *str);
		explicit Color4(const T* p);

		operator T* ();
		operator const T* () const;

		Color4<T>& operator=(const Color4<T>& rhs);

		Color4<T>& operator+=(const Color4<T>& c);
		Color4<T>& operator-=(const Color4<T>& c);
		Color4<T>& operator*=(const T& s);
		Color4<T>& operator/=(const T& s);
	};


	//
	//
	//  Color3
	//
	// 
	template <typename T>
	Color3<T>::Color3()
	{
	}

	template <typename T>
	Color3<T>::Color3(const T& r, const T& g, const T& b)
		: r(r), g(g), b(b)
	{
	}

	template <typename T>
	Color3<T>::Color3(const T& bw)
		: r(bw), g(bw), b(bw)
	{
	}

	template <typename T>
	Color3<T>::Color3(const T* p)
		: r(p[0]), g(p[1]), b(p[2]) 
	{
	}

	template <typename T>
	Color3<T>::Color3(const char *str)		
	{
		r = readHexByte(str+0);
		g = readHexByte(str+2);
		b = readHexByte(str+4);
	}

	template <typename T>
	Color3<T>::operator T* ()
	{
		return (T *) &r; 
	}

	template <typename T>
	Color3<T>::operator const T* () const
	{
		return (const T *) &r; 
	}

	template <typename T> 
	Color3<T>& Color3<T>::operator =(const Color3<T>& rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		return *this;
	}

	template <typename T> 
	Color3<T>& Color3<T>::operator +=(const Color3<T>& c)
	{
		r += c.r;
		g += c.g;
		b += c.b;		
		return *this;
	}

	template <typename T> 
	Color3<T>& Color3<T>::operator -=(const Color3<T>& c)
	{
		r -= c.r;
		g -= c.g;
		b -= c.b;
		return *this;
	}

	template <typename T> 
	Color3<T>& Color3<T>::operator *=(const T& s)
	{
		r *= s;
		g *= s;
		b *= s;		
		return *this;
	}

	template <typename T> 
	Color3<T>& Color3<T>::operator /=(const T& s)
	{
		return *this *= (1/s);
	}



	//
	//
	//  Color4
	//
	// 
	template <typename T>
	Color4<T>::Color4() 
	{
	}

	template <typename T>
	Color4<T>::Color4(const T& r, const T& g, const T& b, const T& a)
		: r(r), g(g), b(b), a(a)
	{
	}

	template <typename T>
	Color4<T>::Color4(const T& bw, const T& a)
		: r(bw), g(bw), b(bw), a(a)
	{
	}

	template <typename T>
	Color4<T>::Color4(const T* p)
		: r(p[0]), g(p[1]), b(p[2]), a(p[3]) 
	{
	}

	template <typename T>
	Color4<T>::Color4(const char *str)		
	{
		r = readHexByte(str+0);
		g = readHexByte(str+2);
		b = readHexByte(str+4);
		a = readHexByte(str+6);
	}

	//template <typename T>
	//Color4<T>::Color4(const Color3<T>& color3)
	//	: r(color3.r), g(color3.r), b(color3.r), a(FULL_VALUE)
	//{
	//}

	template <typename T>
	Color4<T>::operator T* ()
	{
		return (T *) &r; 
	}

	template <typename T>
	Color4<T>::operator const T* () const
	{
		return (const T *) &r; 
	}

	template <typename T> 
	Color4<T>& Color4<T>::operator =(const Color4<T>& rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		a = rhs.a;
		return *this;
	}

	template <typename T> 
	Color4<T>& Color4<T>::operator +=(const Color4<T>& c)
	{
		r += c.r; 
		g += c.g; 
		b += c.b; 
		a += c.a;
		return *this;
	}

	template <typename T> 
	Color4<T>& Color4<T>::operator -=(const Color4<T>& c)
	{
		r -= c.r; 
		g -= c.g; 
		b -= c.b; 
		a -= c.a;
		return *this;
	}

	template <typename T> 
	Color4<T>& Color4<T>::operator *=(const T& s)
	{
		r *= s; 
		g *= s; 
		b *= s; 
		a *= s;
		return *this;
	}

	template <typename T> 
	Color4<T>& Color4<T>::operator /=(const T& s)
	{
		return *this *= (1/s);
	}
};

#endif
