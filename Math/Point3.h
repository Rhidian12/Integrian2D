#pragma once

#include "../Integrian2D_API.h"
#include "Point.h" // Point 
#include "AreEqual.h"

namespace Integrian2D::Math
{
	template<typename T>
	struct Point<3, T>
	{
	#pragma region Ctors

		Point() = default;
		Point(const T x, const T y, const T z);

	#pragma endregion

	#pragma region Data

		START_DISABLE_WARNING(4201); // Nameless struct
		union
		{
			T Data[3];

			struct
			{
				T x, y, z;
			};
		};
		END_DISABLE_WARNING(4201);

	#pragma endregion

	#pragma region Member_Functions

		Point operator-() const
		{
			return Point{ -x, -y, -z };
		}

	#pragma endregion
	};

	template<typename T>
	Point<3, T>::Point(const T _x, const T _y, const T _z)
		: x{ _x }
		, y{ _y }
		, z{ _z }
	{}

	template<typename T>
	Point<3, T> operator+(const Point<3, T>& l, const Vector<3, T>& r)
	{
		return Point<3, T>{ l.x + r.x, l.y + r.y, l.z + r.z };
	}

	template<typename T>
	Point<3, T> operator-(const Point<3, T>& l, const Vector<3, T>& r)
	{
		return Point<3, T>{ l.x - r.x, l.y - r.y, l.z - r.z };
	}

	template<typename T>
	Point<3, T> operator*(const Point<3, T>& l, const Vector<3, T>& r)
	{
		return Point<3, T>{ l.x* r.x, l.y* r.y, l.z * r.z };
	}

	template<typename T>
	Point<3, T> operator/(const Point<3, T>& l, const Vector<3, T>& r)
	{
		return Point<3, T>{ l.x / r.x, l.y / r.y, l.z / r.z };
	}

	template<typename T>
	Point<3, T>& operator+=(Point<3, T>& l, const Vector<3, T>& r)
	{
		l.x += r.x;
		l.y += r.y;
		l.z += r.z;

		return l;
	}

	template<typename T>
	Point<3, T>& operator-=(Point<3, T>& l, const Vector<3, T>& r)
	{
		l.x -= r.x;
		l.y -= r.y;
		l.z -= r.z;

		return l;
	}

	template<typename T>
	Point<3, T>& operator*=(Point<3, T>& l, const Vector<3, T>& r)
	{
		l.x *= r.x;
		l.y *= r.y;
		l.z *= r.z;

		return l;
	}

	template<typename T>
	Point<3, T>& operator/=(Point<3, T>& l, const Vector<3, T>& r)
	{
		l.x /= r.x;
		l.y /= r.y;
		l.z /= r.z;

		return l;
	}

	template<typename T>
	bool operator==(const Point<3, T>& l, const Point<3, T>& r)
	{
		return (AreEqual(l.x, r.x) && AreEqual(l.y, r.y) && AreEqual(l.z, r.z));
	}

	template<typename T>
	bool operator!=(const Point<3, T>& l, const Point<3, T>& r)
	{
		return !(l == r);
	}
}