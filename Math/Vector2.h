#pragma once

#include "../Integrian2D_API.h"
#include "../Utils/Utils.h"
#include "AreEqual.h"
#include "Vector.h"
#include "Point.h"

namespace Integrian2D::Math
{
	template<typename T>
	struct Vector<2, T>
	{
	#pragma region Ctors

		Vector() = default;
		Vector(const T _x, const T _y);
		Vector(const Point<2, T>& from, const Point<2, T>& to);
		Vector(const Vector<3, T>& v);

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

	#pragma region Required Member Operators
		Vector<2, T> operator-() const
		{
			return Vector<2, T>{ -x, -y };
		}
	#pragma endregion
	};

	template<typename T>
	Vector<2, T>::Vector(const T _x, const T _y)
		: x{ _x }
		, y{ _y }
	{}

	template<typename T>
	Vector<2, T>::Vector(const Point<2, T>& from, const Point<2, T>& to)
		: x{ to.x - from.x }
		, y{ to.y - from.y }
	{}

	template<typename T>
	Vector<2, T>::Vector(const Vector<3, T>& v)
		: x{ v.x }
		, y{ v.y }
	{}

	template<typename T>
	Vector<2, T> operator+(const Vector<2, T>& l, const Vector<2, T>& r)
	{
		return Vector<2, T>{ l.x + r.x, l.y + r.y };
	}

	template<typename T>
	Vector<2, T> operator-(const Vector<2, T>& lhs, const Vector<2, T>& rhs)
	{
		return Vector<2, T>{ lhs.x - rhs.x, lhs.y - rhs.y };
	}

	template<typename T>
	Vector<2, T> operator*(const Vector<2, T>& lhs, const Vector<2, T>& rhs)
	{
		return Vector<2, T>{ lhs.x* rhs.x, lhs.y* rhs.y };
	}

	template<typename T>
	Vector<2, T> operator*(const Vector<2, T>& lhs, const T rhs)
	{
		return Vector<2, T>{ lhs.x* rhs, lhs.y* rhs };
	}

	template<typename T>
	Vector<2, T> operator/(const Vector<2, T>& lhs, const Vector<2, T>& rhs)
	{
		return Vector<2, T>{ lhs.x / rhs.x, lhs.y / rhs.y };
	}

	template<typename T>
	Vector<2, T> operator/(const Vector<2, T>& lhs, const T rhs)
	{
		return Vector<2, T>{ lhs.x / rhs, lhs.y / rhs };
	}

	template<typename T>
	Vector<2, T>& operator+=(Vector<2, T>& l, const Vector<2, T>& r)
	{
		l.x += r.x;
		l.y += r.y;

		return *this;
	}

	template<typename T>
	Vector<2, T>& operator-=(Vector<2, T>& l, const Vector<2, T>& r)
	{
		l.x -= r.x;
		l.y -= r.y;

		return *this;
	}

	template<typename T>
	Vector<2, T>& operator*=(Vector<2, T>& l, const Vector<2, T>& r)
	{
		l.x *= r.x;
		l.y *= r.y;

		return *this;
	}

	template<typename T>
	Vector<2, T>& operator*=(Vector<2, T>& l, const T r)
	{
		l.x *= r;
		l.y *= r;

		return *this;
	}

	template<typename T>
	Vector<2, T>& operator/=(Vector<2, T>& l, const Vector<2, T>& r)
	{
		l.x /= r.x;
		l.y /= r.y;

		return *this;
	}

	template<typename T>
	Vector<2, T>& operator/=(Vector<2, T>& l, const T r)
	{
		l.x /= r;
		l.y /= r;

		return *this;
	}

	template<typename T>
	bool operator==(const Vector<2, T>& l, const Vector<2, T>& r)
	{
		return AreEqual(l.x, r.x) && AreEqual(l.y, r.y);
	}

	template<typename T>
	bool operator!=(const Vector<2, T>& l, const Vector<2, T>& r)
	{
		return !(l == r);
	}

	template<typename T>
	T Dot(const Vector<2, T>& l, const Vector<2, T>& r)
	{
		return l.x * r.x + l.y * r.y;
	}

	template<typename T>
	T Cross(const Vector<2, T>& l, const Vector<2, T>& r)
	{
		return l.x * r.y - l.y * r.x;
	}

	template<typename T>
	Vector<2, T> Orthogonal(const Vector<2, T>& v)
	{
		return Vector<2, T>{ -v.y, v.x };
	}

	template<typename T>
	bool DoVectorsIntersect(const Point<2, T>& p1, const Vector<2, T>& v1, const Point<2, T>& p2,
		const Vector<2, T>& v2, void* pIntersectionPoint)
	{
		// Reference: https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

		const Vector<2, T> pointOneToPointTwo{ p1, p2 };
		const T vectorsCross{ Cross(v1, v2) };
		const T pointVectorVectorOneCross{ Cross(pointOneToPointTwo, v1) };

		const T firstLineParameter{ Cross(pointOneToPointTwo, v2) / vectorsCross };
		const T secondLineParameter{ Cross(pointOneToPointTwo, v1) / vectorsCross };

		if (AreEqual(vectorsCross, static_cast<T>(0.f)) &&
			AreEqual(pointVectorVectorOneCross, static_cast<T>(0.f)))
		{
			// the two vectors are colinear
			const T distanceFirstSegment{ DistanceSquared(p1, Point<2, T>{ v1.x, v1.y }) };

			if (DistanceSquared(p1, p2) <= distanceFirstSegment ||
				DistanceSquared(p1, Point<2, T>{ v2.x, v2.y }) <= distanceFirstSegment)
			{
				// vectors are intersecting
				if (pIntersectionPoint) // does the user care about the intersection point
					*static_cast<Point<2, T>*>(pIntersectionPoint) = Point<2, T>{ p1 + v1 * firstLineParameter };

				return true;
			}
		}
		else if (AreEqual(vectorsCross, static_cast<T>(0.f)) &&
			!AreEqual(pointVectorVectorOneCross, static_cast<T>(0.f)))
		{
			return false; // the vectors are parallel
		}
		else if (!AreEqual(vectorsCross, static_cast<T>(0.f)) &&
			Utils::IsInRange(firstLineParameter, static_cast<T>(0.f), static_cast<T>(1.f)) &&
			Utils::IsInRange(secondLineParameter, static_cast<T>(0.f), static_cast<T>(1.f)))
		{
			// vectors are intersecting
			if (pIntersectionPoint) // does the user care about the intersection point
				*static_cast<Point<2, T>*>(pIntersectionPoint) = Point<2, T>{ p1 + v1 * firstLineParameter };

			return true;
		}

		// the vectors are not parallel and they do not intersect
		return false;

	}
}