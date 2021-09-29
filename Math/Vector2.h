#pragma once

#include "Vector.h"
#include "Point.h"
#include <iostream>
#include <utility>

namespace Integrian2D
{
	// == Vector2f (Vector specialisation) ==
	template<typename Type>
	struct Vector<2, Type>
	{
#pragma region Constructors
		explicit Vector<2, Type>()
			: x{}
			, y{}
		{}
		explicit Vector<2, Type>(const Type _x, const Type _y)
			: x{ _x }
			, y{ _y }
		{}
		explicit Vector<2, Type>(const Point<2, Type>& from, const Point<2, Type>& to)
			: x{ to.x - from.x }
			, y{ to.y - from.y }
		{}
		explicit Vector<2, Type>(const Vector<3, Type>& v)
			: x{ v.x }
			, y{ v.y }
		{}
#pragma endregion

#pragma region Rule Of 5
		Vector<2, Type>(const Vector<2, Type>& v1)
			: x{ v1.x }
			, y{ v1.y }
		{}
		Vector<2, Type>(Vector<2, Type>&& v1)
			: x{ std::move(v1.x) }
			, y{ std::move(v1.y) }
		{}
		Vector<2, Type>& operator=(const Vector<2, Type>& v1)
		{
			x = v1.x;
			y = v1.y;
			return *this;
		}
		Vector<2, Type>& operator=(Vector<2, Type>&& v1)
		{
			x = std::move(v1.x);
			y = std::move(v1.y);
			return *this;
		}
#pragma endregion

#pragma region Data
		Type x, y;
	};

#pragma region Arithmetic Operators
	template<typename Type>
	Vector<2, Type> operator+(const Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x + rhs, lhs.y + rhs};
	}

	template<typename Type>
	Vector<2, Type> operator+(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x + rhs.x, lhs.y + rhs.y};
	}

	template<typename Type>
	Vector<2, Type> operator-(const Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x - rhs, lhs.y - rhs};
	}

	template<typename Type>
	Vector<2, Type> operator-(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x - rhs.x, lhs.y - rhs.y};
	}

	template<typename Type>
	Vector<2, Type> operator*(const Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x* rhs, lhs.y* rhs};
	}

	template<typename Type>
	Vector<2, Type> operator*(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x* rhs.x, lhs.y* rhs.y};
	}

	template<typename Type>
	Vector<2, Type> operator/(const Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x / rhs, lhs.y / rhs};
	}

	template<typename Type>
	Vector<2, Type> operator/(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x / rhs.x, lhs.y / rhs.y};
	}
#pragma endregion

#pragma region Compound Assignment Operators
	template<typename Type>
	Vector<2, Type>& operator+=(Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x += rhs;
		lhs.y += rhs;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type>& operator+=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type>& operator-=(Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x -= rhs;
		lhs.y -= rhs;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type>& operator-=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type>& operator/=(Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type>& operator/=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type>& operator*=(Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type>& operator*=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		return lhs;
	}
#pragma endregion

#pragma region Relational Operators
	template<typename Type>
	bool operator==(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Utils::AreEqual(lhs.x, rhs.x) && Utils::AreEqual(lhs.y, rhs.y);
	}

	template<typename Type>
	bool operator!=(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return !(lhs == rhs);
	}
#pragma endregion

#pragma region Functions
	template<typename Type>
	Type Dot(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	template<typename Type>
	Type Cross(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}

	template<typename Type>
	Vector<2, Type> Orthogonal(const Vector<2, Type>& v) noexcept
	{
		return Vector<2, Type>{ -v.y, v.x };
	}

	template<typename Type>
	bool DoVectorsIntersect(const Point<2, Type>& p1, const Vector<2, Type>& v1, const Point<2, Type>& p2, const Vector<2, Type>& v2, Point<2, Type>* pIntersectionPoint)
	{
		// Reference: https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

		const Vector<2, Type> pointOneToPointTwo{ p1, p2 };
		const Type vectorsCross{ Cross(v1, v2) };
		const Type pointVectorVectorOneCross{ Cross(pointOneToPointTwo, v1) };

		const Type firstLineParameter{ Cross(pointOneToPointTwo, v2) / vectorsCross };
		const Type secondLineParameter{ Cross(pointOneToPointTwo, v1) / vectorsCross };

		if (Utils::AreEqual(vectorsCross, static_cast<Type>(0.f)) && Utils::AreEqual(pointVectorVectorOneCross, static_cast<Type>(0.f)))
		{
			// the two vectors are colinear
			const Type distanceFirstSegment{ DistanceSquared(p1, Point<2, Type>{v1.x, v1.y}) };

			if (DistanceSquared(p1, p2) <= distanceFirstSegment || DistanceSquared(p1, Point<2, Type>{v2.x, v2.y}) <= distanceFirstSegment)
			{
				// vectors are intersecting
				if (pIntersectionPoint) // does the user care about the intersection point
					*pIntersectionPoint = Point<2, Type>{ p1 + v1 * firstLineParameter };

				return true;
			}
		}
		else if (Utils::AreEqual(vectorsCross, static_cast<Type>(0.f)) && !Utils::AreEqual(pointVectorVectorOneCross, static_cast<Type>(0.f)))
			return false; // the vectors are parallel
		else if (!Utils::AreEqual(vectorsCross, static_cast<Type>(0.f)) && Utils::IsInRange(firstLineParameter, static_cast<Type>(0.f), static_cast<Type>(1.f)) &&
			Utils::IsInRange(secondLineParameter, static_cast<Type>(0.f), static_cast<Type>(1.f)))
		{
			// vectors are intersecting
			if (pIntersectionPoint) // does the user care about the intersection point
				*pIntersectionPoint = Point<2, Type>{ p1 + v1 * firstLineParameter };

			return true;
		}
		else // the vectors are not parallel and they do not intersect
			return false;
	}
#pragma endregion

#pragma region Miscellaneous Operators
	template<typename Type>
	std::ostream& operator<<(std::ostream& os, const Vector<2, Type>& v) noexcept
	{
		os << v.x << ", " << v.y;
		return os;
	}
#pragma endregion
}

