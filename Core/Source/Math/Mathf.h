#pragma once


#include "Random.h"
#include <math.h>

namespace Forge
{ 
	
	static const float PI = 3.14159265358979323846264338327950288f;
	static const float HALF_PI = PI * 0.5f;

	static const float EPSILON = 0.000001f;
	static const float LARGE_EPSILON = 0.00005f;
	static const float MIN_NEARCLIP = 0.01f;
	static const float MAX_FOV = 160.0f;
	static const float DEGTORAD = PI / 180.0f;
	static const float DEGTORAD_2 = PI / 360.0f;    // M_DEGTORAD / 2.f
	static const float RADTODEG = 1.0f / DEGTORAD;

	inline unsigned SDBMHash(unsigned hash, unsigned char c) 
	{ 
		return c + (hash << 6) + (hash << 16) - hash; 
	}

	inline float Random() 
	{ 
		return Rand() / 32768.0f;
	}

	inline float Random(float range) 
	{ 
		return Rand() * range / 32767.0f; 
	}

	inline float Random(float min, float max) 
	{ 
		return Rand() * (max - min) / 32767.0f + min; 
	}

	inline int Random(int range) 
	{ 
		return (int)(Random() * range); 
	}

	inline int Random(int min, int max) 
	{ 
		float range = (float)(max - min); return (int)(Random() * range) + min; 
	}

	inline float RandomNormal(float meanValue, float variance) 
	{ 
		return RandStandardNormal() * sqrtf(variance) + meanValue; 
	}

	template<class T>
	inline bool Equals(T lhs, T rhs)
	{
		return lhs + std::numeric_limits<T>::epsilon() >= rhs && lhs - std::numeric_limits<T>::epsilon() <= rhs;
	}

	template <class T>
	inline T Clamp(T value, T min, T max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		else
			return value;
	}

	template<class T>
	inline T Max(T lhs, T rhs)
	{
		return lhs > rhs ? lhs : rhs;
	}

	template<class T>
	inline T Min(T lhs, T rhs)
	{
		return lhs > rhs ? rhs : lhs;
	}

	template<class T>
	inline T Abs(T value)
	{
		return value >= 0.0 ? value : -value;
	}

	template <class T>
	inline T Sin(T angle)
	{
		return sin(angle * DEGTORAD);
	}

	template <class T>
	inline T Cos(T angle)
	{
		return cos(angle * DEGTORAD);
	}

	template <class T>
	inline T Tan(T angle)
	{
		return tan(angle * DEGTORAD);
	}

	template <class T>
	inline T Asin(T x)
	{
		return RADTODEG * asin(Clamp(x, T(-1.0), T(1.0)));
	}

	template <class T>
	inline T Acos(T x)
	{
		return RADTODEG * acos(Clamp(x, T(-1.0), T(1.0)));
	}

	template <class T>
	inline T Atan(T x)
	{
		return RADTODEG * atan(x);
	}

	template <class T>
	inline T Atan2(T y, T x)
	{
		return RADTODEG * atan2(y, x);
	}

	template <class T>
	T Pow(T x, T y)
	{
		return pow(x, y);
	}

	template <class T>
	T Ln(T x)
	{
		return log(x);
	}

	template <class T>
	T Sqrt(T x)
	{
		return sqrt(x);
	}

	template <class T>
	T Mod(T x, T y)
	{
		return fmod(x, y);
	}

	template <class T>
	T Fract(T value)
	{
		return value - floor(value);
	}

	template <class T>
	T Floor(T x)
	{
		return floor(x);
	}

	template <class T>
	int FloorToInt(T x)
	{
		return static_cast<int>(floor(x));
	}

	template <class T>
	T Round(T x)
	{
		return floor(x + T(0.5));
	}

	template <class T>
	int RoundToInt(T x)
	{
		return static_cast<int>(floor(x + T(0.5)));
	}

	template <class T>
	T Ceil(T x)
	{
		return ceil(x);
	}

	template <class T>
	int CeilToInt(T x)
	{
		return static_cast<int>(ceil(x));
	}
}