#ifndef _STATE_GUI_BASIC_H_
#define _STATE_GUI_BASIC_H_

#include "declares.h"
#include "Color.h"

namespace SGui
{
	
	template <typename T>
	struct VecTempl
	{
		T x;
		T y;

		/**
		 * Default constructor, members will contain garbage.
		 */
		inline VecTempl()												{}

		//inline VecTempl(const VecTempl<T> &v) : x(v.x), y(v.y)		{}

		template <typename S>
		inline VecTempl(const VecTempl<S> &v) : x(v.x), y(v.y)			{}

		inline VecTempl(T x, T y) : x(x), y(y)							{}

		inline VecTempl<T> operator +(const VecTempl<T> &v) const		{ return VecTempl<T>(x + v.x, y + v.y); }

		inline VecTempl<T> operator +(T s) const						{ return VecTempl<T>(x + s, y + s); }

		inline VecTempl<T> operator -(const VecTempl<T> &v) const		{ return VecTempl<T>(x - v.x, y - v.y); }

		inline VecTempl<T> operator *(const VecTempl<T> &v) const		{ return VecTempl<T>(x * v.x, y * v.y); }

		inline VecTempl<T> operator /(const VecTempl<T> &v) const		{ return VecTempl<T>(x / v.x, y / v.y); }

		inline VecTempl<T> operator *(T t) const						{ return VecTempl<T>(x * t, y * t); }

		inline VecTempl<T> operator /(T t) const						{ return VecTempl<T>(x / t, y / t); }

		inline VecTempl<T> operator +=(const VecTempl<T> &v)			{ x += v.x; y += v.y; return *this; }

		inline VecTempl<T> operator -=(const VecTempl<T> &v)			{ x -= v.x; y -= v.y; return *this; }

		inline bool operator ==(const VecTempl<T> &v) const				{ return ((x == v.x) && (y == v.y)); }

		inline bool operator !=(const VecTempl<T> &v) const				{ return ((x != v.x) || (y != v.y)); }

	};

	typedef VecTempl<int> Veci;
	typedef VecTempl<float> Vecf;
	typedef VecTempl<double> Vecd;
	typedef Veci Vec;
	typedef Vec Pos;


	static const int POW_TO_2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

	typedef Color4<float> Color4f;
	typedef Color4<uchar> Color4b;

	typedef Color3<float> Color3f;
	typedef Color3<uchar> Color3b;
	
	typedef Color3b Color;

	//template <typename T>
	///inline operator Color4<T> (const Color3<T> &color3)		{ return Color4<T>(color3.r, color3.g, color3.b, 1); }

	//inline operator Color4<float> (const Color3f &color3)		{ return Color4f(color3.r, color3.g, color3.b, 1.0f); }
	//inline operator Color4b (const Color3b &color3)				{ return Color4b(color3.r, color3.g, color3.b, 1); }

	struct TxtrCoord
	{
		float s;
		float t;
		
		TxtrCoord()										{}
		TxtrCoord(float s, float t) : s(s), t(t)		{}
		//TxtrCoord(const Vecf &v) : s(v.x), t(v.y)		{}
		//TxtrCoord(const Vec &v) : s(static_cast<float>(v.x)), t(static_cast<float>(v.y))	{}
		//TxtrCoord& operator+=(const Vecf &v)			{ s += v.x; t += v.y; }
		operator Vecf()									{ return Vecf(s, t); }
		//const Vecf& operator Vecf()					{ *reinterpret_cast<const Vecf*>(this); }

		void rescale(const Vecd &rescaleVec);

		static inline void rescale(double &value, double rescale)
		{
			value *= rescale;
		}

		//Vecd tmpPos = static_cast<double>(posWithinTxtr) * txtrCoordRescale;
		//Vecd tmpSize = static_cast<double>(sizeWithinTxtr) * txtrCoordRescale;
	};

	template <typename T>
	struct Flags
	{
		T flags;

		Flags()	: flags(0)									{}
		Flags(T flags) : flags(flags)						{}
		Flags(const Flags<T> &flags) : flags(flags.flags)	{}
	
		bool get(T flag)	{ return (flags & flag) != 0; }
		void set(T flag, bool value)
		{
			if (value) flags |= flag;
			else flags &= ~flag;
		}
	};

};

#endif