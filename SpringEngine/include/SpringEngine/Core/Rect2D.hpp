#pragma once

namespace SE
{
	template <typename T>
	class SE_API Rect2D
	{
	public:
		Rect2D() : x(0), y(0), width(0), height(0)
		{

		}

		Rect2D(T x, T y, T width, T height) : x(x), y(y), width(width), height(height)
		{

		}

	public:
		T x;
		T y;
		T width;
		T height;
	};

	typedef Rect2D<float> Rect2Df;
	typedef Rect2D<unsigned int> Rect2Dui;
}