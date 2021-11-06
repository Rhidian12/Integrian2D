#pragma once

#include "Point.h" // Point 
#include "Vector.h" // Vector

#include <utility>

namespace Integrian2D
{
	/* This class is the specialisation of Point, representing a Point with 2 dimensions */

	/* A list of available operators:
	   Assume Type is the templated type provided to the Point2 
	   
	   Point<2, Type> operator-(const Point<2, Type>& lhs, const Point<2, Type>& rhs)
	   Point<2, Type> operator-(const Point<2, Type>& lhs, const Vector<2, Type>& rhs)

	   Point<2, Type> operator+(const Point<2, Type>& lhs, const Point<2, Type>& rhs)
	   Point<2, Type> operator+(const Point<2, Type>& lhs, const Vector<2, Type>& rhs)

	   Point<2, Type> operator*(const Point<2, Type>& lhs, const Point<2, Type>& rhs)
	   Point<2, Type> operator*(const Point<2, Type>& lhs, const Type& rhs)

	   Point<2, Type> operator/(const Point<2, Type>& lhs, const Point<2, Type>& rhs)
	   Point<2, Type> operator/(const Point<2, Type>& lhs, const Vector<2, Type>& rhs)

	   Point<2, Type>& operator-=(Point<2, Type>& lhs, const Point<2, Type>& rhs)
	   Point<2, Type>& operator-=(Point<2, Type>& lhs, const Vector<2, Type>& rhs)

	   Point<2, Type>& operator+=(Point<2, Type>& lhs, const Point<2, Type>& rhs)
	   Point<2, Type>& operator+=(Point<2, Type>& lhs, const Vector<2, Type>& rhs)

	   Point<2, Type>& operator*=(Point<2, Type>& lhs, const Point<2, Type>& rhs)
	   Point<2, Type>& operator*=(Point<2, Type>& lhs, const Vector<2, Type>& rhs)

	   Point<2, Type>& operator/=(Point<2, Type>& lhs, const Vector<2, Type>& rhs)
	   Point<2, Type>& operator/=(Point<2, Type>& lhs, const Point<2, Type>& rhs)

	   bool operator==(const Point<2, Type>& lhs, const Point<2, Type>& other)
	   bool operator!=(const Point<2, Type>& lhs, const Point<2, Type>& other)

	   std::ostream& operator<<(std::ostream& os, const Point<2, Type>& point)
	   */

	/* A list of available functions:
	   Type DistanceSquared(const Point<2, Type>& p1, const Point<2, Type>& p2) 
	   =>	Returns the squared distance between the two provided points 
	   
	   Type Distance(const Point<2, Type>& p1, const Point<2, Type>& p2)
	   =>	Returns the distance between the two provided points
	   */
	template<typename Type>
	struct Point<2, Type>
	{
#pragma region Constructors
		explicit Point<2, Type>()
			: x{}
			, y{}
		{}
		explicit Point<2, Type>(const Type _x, const Type _y)
			: x{ _x }
			, y{ _y }
		{}
		explicit Point<2, Type>(const Point<3, Type>& p)
			: x{ p.x }
			, y{ p.y }
		{}
#pragma endregion

#pragma region Rule Of 5
		Point<2, Type>(const Point<2, Type>& p) noexcept
			: x{ p.x }
			, y{ p.y }
		{}
		Point<2, Type>(Point<2, Type>&& other) noexcept
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
		{}
		Point<2, Type>& operator=(const Point<2, Type>& p) noexcept
		{
			x = p.x;
			y = p.y;
			return *this;
		}
		Point<2, Type>& operator=(Point<2, Type>&& p) noexcept
		{
			x = std::move(p.x);
			y = std::move(p.y);
			return *this;
		}
#pragma endregion

#pragma region Data
		Type x, y;
#pragma endregion
	};

#pragma region Arithmetic Operators
	template<typename Type>
	Point<2, Type> operator-(const Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x - rhs.x, lhs.y - rhs.y};
	}

	template<typename Type>
	Point<2, Type> operator-(const Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Point<2, Type>{lhs.x - rhs.x, lhs.y - rhs.y};
	}

	template<typename Type>
	Point<2, Type> operator+(const Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		return Point<2, Type>{lhs.x + rhs.x, lhs.y + rhs.y};
	}

	template<typename Type>
	Point<2, Type> operator+(const Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Point<2, Type>{lhs.x + rhs.x, lhs.y + rhs.y};
	}

	template<typename Type>
	Point<2, Type> operator*(const Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		return Point<2, Type>{lhs.x* rhs.x, lhs.y* rhs.y};
	}

	template<typename Type>
	Point<2, Type> operator*(const Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Point<2, Type>{lhs.x* rhs.x, lhs.y* rhs.y};
	}

	template<typename Type>
	Point<2, Type> operator/(const Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		return Point<2, Type>{lhs.x / rhs.x, lhs.y / rhs.y};
	}

	template<typename Type>
	Point<2, Type> operator/(const Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Point<2, Type>{lhs.x / rhs.x, lhs.y / rhs.y};
	}
#pragma endregion

#pragma region Compound Assignment Operators
	template<typename Type>
	Point<2, Type>& operator+=(Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	template<typename Type>
	Point<2, Type>& operator+=(Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	template<typename Type>
	Point<2, Type>& operator-=(Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	template<typename Type>
	Point<2, Type>& operator-=(Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	template<typename Type>
	Point<2, Type>& operator*=(Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		return lhs;
	}

	template<typename Type>
	Point<2, Type>& operator*=(Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		return lhs;
	}

	template<typename Type>
	Point<2, Type>& operator/=(Point<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		return lhs;
	}

	template<typename Type>
	Point<2, Type>& operator/=(Point<2, Type>& lhs, const Point<2, Type>& rhs) noexcept
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		return lhs;
	}
#pragma endregion

#pragma region Relational Operators
	template<typename Type>
	bool operator==(const Point<2, Type>& lhs, const Point<2, Type>& other) noexcept
	{
		return Utils::AreEqual(lhs.x, other.x) && Utils::AreEqual(lhs.y, other.y);
	}

	template<typename Type>
	bool operator!=(const Point<2, Type>& lhs, const Point<2, Type>& other) noexcept
	{
		return !(lhs == other);
	}
#pragma endregion

#pragma region Miscellaneous Operators
	template<typename Type>
	std::ostream& operator<<(std::ostream& os, const Point<2, Type>& point) noexcept
	{
		os << point.x << ", " << point.y;
		return os;
	}
#pragma endregion
}

