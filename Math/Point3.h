#pragma once

#include "Point.h" // Point
#include "Vector.h" // Vector

#include <utility>

namespace Integrian2D
{
	// == Point3 (Point Specialisation) == 
	template<typename Type>
	struct Point<3, Type>
	{
#pragma region Constructors
		explicit Point<3, Type>()
			: x{}
			, y{}
			, z{}
		{}
		explicit Point<3, Type>(const Type _x, const Type _y)
			: x{ _x }
			, y{ _y }
			, z{}
		{}
		explicit Point<3, Type>(const Type _x, const Type _y, const Type _z)
			: x{ _x }
			, y{ _y }
			, z{ _z }
		{}
		explicit Point<3, Type>(const Point<2, Type> _xy)
			: x{ _xy.x }
			, y{ _xy.y }
			, z{}
		{}
#pragma endregion

#pragma region Rule Of 5
		Point<3, Type>(const Point<3, Type>& other) noexcept
			: x{ other.x }
			, y{ other.y }
			, z{ other.z }
		{}
		Point<3, Type>(Point<3, Type>&& other) noexcept
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
			, z{ std::move(other.z) }
		{}
		Point<3, Type>& operator=(const Point<3, Type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			z = other.y;

			return *this;
		}
		Point<3, Type>& operator=(Point<3, Type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			z = std::move(other.y);

			return *this;
		}
#pragma endregion

#pragma region Data
		union
		{
			Type data[3];

#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
			struct
			{
				Point<2, Type> xy;
				Type x, y, z;
			};
#pragma warning ( pop )
		};
#pragma endregion
	};

#pragma region Arithmetic Operators
	template<typename Type>
	Vector<3, Type> operator-(const Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
	}

	template<typename Type>
	Point<3, Type> operator-(const Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Point<3, Type>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
	}

	template<typename Type>
	Vector<3, Type> operator+(const Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
	}

	template<typename Type>
	Point<3, Type> operator+(const Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Point<3, Type>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
	}

	template<typename Type>
	Point<3, Type> operator*(const Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		return Point<3, Type>{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
	}

	template<typename Type>
	Point<3, Type> operator*(const Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Point<3, Type>{lhs.x* rhs.x, lhs.y* rhs.y, lhs.z* rhs.z};
	}

	template<typename Type>
	Point<3, Type> operator/(const Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		return Point<3, Type>{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
	}

	template<typename Type>
	Point<3, Type> operator/(const Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Point<3, Type>{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
	}
#pragma endregion

#pragma region Compound Assignment Operators
	template<typename Type>
	Point<3, Type>& operator+=(Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	}

	template<typename Type>
	Point<3, Type>& operator+=(Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	}

	template<typename Type>
	Point<3, Type>& operator-=(Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		return lhs;
	}

	template<typename Type>
	Point<3, Type>& operator-=(Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		return lhs;
	}

	template<typename Type>
	Point<3, Type>& operator*=(Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
		return lhs;
	}

	template<typename Type>
	Point<3, Type>& operator*=(Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
		return lhs;
	}

	template<typename Type>
	Point<3, Type>& operator/=(Point<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;
		return lhs;
	}

	template<typename Type>
	Point<3, Type>& operator/=(Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;
		return lhs;
	}
#pragma endregion

#pragma region Relational Operators
	template<typename Type>
	bool operator==(const Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		return Utils::AreEqual(lhs.x, rhs.x) && Utils::AreEqual(lhs.y, rhs.y) && Utils::AreEqual(lhs.z, rhs.z);
	}

	template<typename Type>
	bool operator!=(const Point<3, Type>& lhs, const Point<3, Type>& rhs) noexcept
	{
		return !(lhs == rhs);
	}
#pragma endregion

#pragma region Miscellaneous Operators
	template<typename Type>
	std::ostream& operator<<(std::ostream& os, const Point<3, Type>& point) noexcept
	{
		os << point.x << ", " << point.y << ", " << point.z;
		return os;
	}
#pragma endregion
}