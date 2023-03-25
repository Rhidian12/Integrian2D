#pragma once

#include "../Integrian2D_API.h"
#include "../Utils/Utils.h"
#include "AreEqual.h"
#include "Point2.h"
#include "Vector2.h"

namespace Integrian2D::Math
{
	// xy represents bottom left
	template<typename T>
	struct Rect
	{
	#pragma region Constructors

		Rect();
		Rect(const T _x, const T _y, const T _width, const T _height);
		Rect(const Point<2, T>& _xy, const T _width, const T _height);

	#pragma endregion

	#pragma region Data

		START_DISABLE_WARNING(4201);
		union
		{
			struct { T x, y; };
			Point<2, T> xy;
		};
		END_DISABLE_WARNING(4201);

		T width, height;

	#pragma endregion
	};

	template<typename T>
	Rect<T>::Rect()
		: x{}
		, y{}
		, width{}
		, height{}
	{}

	template<typename T>
	Rect<T>::Rect(const T _x, const T _y, const T _width, const T _height)
		: x{ _x }
		, y{ _y }
		, width{ _width }
		, height{ _height }
	{}

	template<typename T>
	Rect<T>::Rect(const Point<2, T>& _xy, const T _width, const T _height)
		: x{ _xy.x }
		, y{ _xy.y }
		, width{ _width }
		, height{ _height }
	{}

	template<typename T>
	bool operator==(const Rect<T>& r1, const Rect<T>& r2)
	{
		return (r1.xy == r2.xy) && AreEqual(r1.width, r2.width) && AreEqual(r1.height, r2.height);
	}

	template<typename T>
	bool operator!=(const Rect<T>& r1, const Rect<T>& r2)
	{
		return !(r1 == r2);
	}

	template<typename T>
	T GetArea(const Rect<T>& r)
	{
		return r.width * r.height;
	}

	template<typename T>
	Point<2, T> GetTopLeft(const Rect<T>& r)
	{
		return Point<2, T>{ r.x, r.y + r.height };
	}

	template<typename T>
	Point<2, T> GetTopRight(const Rect<T>& r)
	{
		return Point<2, T>{ r.x + r.width, r.y + r.height };
	}

	template<typename T>
	Point<2, T> GetBottomRight(const Rect<T>& r)
	{
		return Point<2, T>{ r.x + r.width, r.y };
	}
}