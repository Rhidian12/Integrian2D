#pragma once

#ifndef INTEGRIAN2D_VECTOR2_H
#define INTEGRIAN2D_VECTOR2_H

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
		Vector<2, Type>()
			: x{}
			, y{}
		{}
		Vector<2, Type>(const Type _x, const Type _y)
			: x{ _x }
			, y{ _y }
		{}
		Vector<2, Type>(const Point<2, Type>& from, const Point<2, Type>& to)
			: x{ to.x - from.x }
			, y{ to.y - from.y }
		{}
		Vector<2, Type>(const Vector<3, Type>& v)
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
		union
		{
			Type data[2];

#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
			struct
			{
				Type x, y;
			};
#pragma warning ( pop )
		};
#pragma endregion
	};

#pragma region Arithmetic Operators
	template<typename Type>
	Vector<2, Type> operator+(const Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		return Vector<2, Type>{lhs.x + rhs.x, lhs.y + rhs.y};
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
	Vector<2, Type> operator+=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type> operator-=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type> operator/=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type> operator/=(Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type> operator*=(Vector<2, Type>& lhs, const Vector<2, Type>& rhs) noexcept
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		return lhs;
	}

	template<typename Type>
	Vector<2, Type> operator*=(Vector<2, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		return lhs;
	}
#pragma endregion

#pragma region Relational Operators
	template<typename Type>
	bool operator==(const Vector<2, Type>& lhs, const Vector<2, Type>& other) noexcept
	{
		return Utils::AreEqual(lhs.x, other.x) && Utils::AreEqual(lhs.y, other.y);
	}

	template<typename Type>
	bool operator!=(const Vector<2, Type>& lhs, const Vector<2, Type>& other) noexcept
	{
		return !(lhs == other);
	}
#pragma endregion

#pragma region Functions
	template<typename Type>
	Type Dot(const Vector<2, Type>& lhs, const Vector<2, Type>& other) noexcept
	{
		return lhs.x * other.x + lhs.y * other.y;
	}

	template<typename Type>
	Type Cross(const Vector<2, Type>& lhs, const Vector<2, Type>& other) noexcept
	{
		return lhs.x * other.y - lhs.y * other.x;
	}

	template<typename Type>
	Vector<2, Type> Orthogonal(const Vector<2, Type>& lhs) noexcept
	{
		return Vector<2, Type>{ -lhs.y, lhs.x };
	}
#pragma endregion

#pragma region Miscellaneous Operators
	template<typename Type>
	std::ostream& operator<<(std::ostream& os, const Vector<2, Type>& vector) noexcept
	{
		os << vector.x << ", " << vector.y;
		return os;
	}
#pragma endregion
}

#endif // !ENGINE_VECTOR2_H