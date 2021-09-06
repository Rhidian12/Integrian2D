#pragma once

#include "Vector.h"
#include "Point.h"

#include <iostream>
#include <utility>

namespace Integrian2D
{
	// == Vector3f ==
	template<typename Type>
	struct Vector<3, Type>
	{
#pragma region Constructors
		explicit Vector<3, Type>()
			: x{}
			, y{}
			, z{}
		{}
		explicit Vector<3, Type>(const Type _x, const Type _y)
			: x{ _x }
			, y{ _y }
			, z{}
		{}
		explicit Vector<3, Type>(const Type _x, const Type _y, const Type _z)
			: x{ _x }
			, y{ _y }
			, z{ _z }
		{}
		explicit Vector<3, Type>(const Point<3, Type>& from, const Point<3, Type>& to)
			: x{ to.x - from.x }
			, y{ to.y - from.y }
			, z{ to.z - from.z }
		{}
		explicit Vector<3, Type>(const Vector<2, Type>& v)
			: x{ v.x }
			, y{ v.y }
			, z{}
		{}
#pragma endregion

#pragma region Rule Of 5
		Vector<3, Type>(const Vector<3, Type>& other) noexcept
			: x{ other.x }
			, y{ other.y }
			, z{ other.z }
		{}
		Vector<3, Type>(Vector<3, Type>&& other) noexcept
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
			, z{ std::move(other.z) }
		{}
		Vector<3, Type>& operator=(const Vector<3, Type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		Vector<3, Type>& operator=(Vector<3, Type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			z = std::move(other.z);
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
				Type x, y, z;
				Vector<2, Type> xy;
			};
#pragma warning ( pop )
		};
#pragma endregion
	};

#pragma region Arithmetic Operators
	template<typename Type>
	Vector<3, Type> operator+(const Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
	}

	template<typename Type>
	Vector<3, Type> operator+(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
	}

	template<typename Type>
	Vector<3, Type> operator-(const Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
	}

	template<typename Type>
	Vector<3, Type> operator-(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
	}

	template<typename Type>
	Vector<3, Type> operator*(const Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x* rhs, lhs.y* rhs, lhs.z* rhs};
	}

	template<typename Type>
	Vector<3, Type> operator*(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x* rhs.x, lhs.y* rhs.y, lhs.z* rhs.z};
	}
	
	template<typename Type>
	Vector<3, Type> operator/(const Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
	}

	template<typename Type>
	Vector<3, Type> operator/(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Vector<3, Type>{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
	}
#pragma endregion

#pragma region Compound Arithmetic Operators
	template<typename Type>
	Vector<3, Type>& operator+=(Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x += rhs;
		lhs.y += rhs;
		lhs.z += rhs;

		return lhs;
	}

	template<typename Type>
	Vector<3, Type>& operator+=(Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;

		return lhs;
	}

	template<typename Type>
	Vector<3, Type>& operator-=(Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x -= rhs;
		lhs.y -= rhs;
		lhs.z -= rhs;

		return lhs;
	}

	template<typename Type>
	Vector<3, Type>& operator-=(Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;

		return lhs;
	}

	template<typename Type>
	Vector<3, Type>& operator*=(Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		lhs.z *= rhs;

		return lhs;
	}

	template<typename Type>
	Vector<3, Type>& operator*=(Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;

		return lhs;
	}

	template<typename Type>
	Vector<3, Type>& operator/=(Vector<3, Type>& lhs, const Type& rhs) noexcept
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		lhs.z /= rhs;

		return lhs;
	}

	template<typename Type>
	Vector<3, Type>& operator/=(Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;

		return lhs;
	}
#pragma endregion

#pragma region Relational Operators
	template<typename Type>
	bool operator==(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Utils::AreEqual(lhs.x, rhs.x) && Utils::AreEqual(lhs.y, rhs.y) && Utils::AreEqual(rhs.z, lhs.z);
	}

	template<typename Type>
	bool operator!=(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return !(lhs == rhs);
	}
#pragma endregion

#pragma region Functions
	template<typename Type>
	Type Dot(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	template<typename Type>
	Vector<3, Type> Cross(const Vector<3, Type>& lhs, const Vector<3, Type>& rhs) noexcept
	{
		return Vector<3, Type>{ lhs.y* rhs.z - lhs.z * rhs.y,
								lhs.x* rhs.y - lhs.y * rhs.x };
								lhs.z* rhs.x - lhs.x * rhs.z,
	}

	template<typename Type>
	Vector<3, Type> Orthogonal(const Vector<3, Type>& lhs, const Vector<3, Type>& cpVector = Vector<3, Type>{ Type(0),Type(0),Type(1) }) noexcept
	{
		return Cross<Type>(lhs, cpVector);
	}
#pragma endregion

#pragma region Miscellanneous Operators
	template<typename Type>
	std::ostream& operator<<(std::ostream& os, const Vector<3, Type>& v) noexcept
	{
		os << vector.x << ", " << vector.y << ", " << vector.z;
		return os;
	}
#pragma endregion
}