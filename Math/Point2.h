#pragma once

#include "../Integrian2D_API.h"
#include "Point.h" // Point 
#include "AreEqual.h"

namespace Integrian2D::Math
{
	template<typename T>
	struct Point<2, T>
	{
	#pragma region Ctors

		Point() = default;
		Point(const T _x, const T _y);
		Point(const Point<3, T>& p);

	#pragma endregion

	#pragma region Data

		START_DISABLE_WARNING(4201); // Nameless struct
		union
		{
			T Data[2];

			struct
			{
				T x, y;
			};
		};
		END_DISABLE_WARNING(4201);

	#pragma endregion

	#pragma region Member_Functions

		Point operator-() const
		{
			return Point{ -x, -y };
		}

	#pragma endregion
	};

	template<typename T>
	Point<2, T>::Point(const T _x, const T _y)
		: x{ _x }
		, y{ _y }
	{}

	template<typename T>
	Point<2, T>::Point(const Point<3, T>& p)
		: x{ p.x }
		, y{ p.y }
	{}

	template<typename T>
	Point<2, T> operator+(const Point<2, T>& l, const Vector<2, T>& r)
	{
		return Point<2, T>{ l.x + r.x, l.y + r.y };
	}

	template<typename T>
	Point<2, T> operator-(const Point<2, T>& l, const Vector<2, T>& r)
	{
		return Point<2, T>{ l.x - r.x, l.y - r.y };
	}

	template<typename T>
	Point<2, T> operator*(const Point<2, T>& l, const Vector<2, T>& r)
	{
		return Point<2, T>{ l.x* r.x, l.y* r.y };
	}

	template<typename T>
	Point<2, T> operator/(const Point<2, T>& l, const Vector<2, T>& r)
	{
		return Point<2, T>{ l.x / r.x, l.y / r.y };
	}

	template<typename T>
	Point<2, T>& operator+=(Point<2, T>& l, const Vector<2, T>& r)
	{
		l.x += r.x;
		l.y += r.y;

		return l;
	}

	template<typename T>
	Point<2, T>& operator-=(Point<2, T>& l, const Vector<2, T>& r)
	{
		l.x -= r.x;
		l.y -= r.y;

		return l;
	}

	template<typename T>
	Point<2, T>& operator*=(Point<2, T>& l, const Vector<2, T>& r)
	{
		l.x *= r.x;
		l.y *= r.y;

		return l;
	}

	template<typename T>
	Point<2, T>& operator/=(Point<2, T>& l, const Vector<2, T>& r)
	{
		l.x /= r.x;
		l.y /= r.y;

		return l;
	}

	template<typename T>
	bool operator==(const Point<2, T>& l, const Point<2, T>& r)
	{
		return (AreEqual(l.x, r.x) && AreEqual(l.y, r.y));
	}

	template<typename T>
	bool operator!=(const Point<2, T>& l, const Point<2, T>& r)
	{
		return !(l == r);
	}
}