#pragma once

#include "../Integrian2D_API.h"
#include "Vector.h"
#include "Point.h"
#include "AreEqual.h"

namespace Integrian2D::Math
{
	template<typename T>
	struct Vector<3, T>
	{
	#pragma region Ctors

		Vector() = default;
		Vector(const T _x, const T _y, const T _z);
		Vector(const Point<3, T>& from, const Point<3, T>& to);

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

	#pragma region Required Member Operators
		Vector operator-() const
		{
			return Vector{ -x, -y, -z };
		}
	#pragma endregion
	};

	template<typename T>
	Vector<3, T>::Vector(const T _x, const T _y, const T _z)
		: x{ _x }
		, y{ _y }
		, z{ _z }
	{}

	template<typename T>
	Vector<3, T>::Vector(const Point<3, T>& from, const Point<3, T>& to)
		: x{ to.x - from.x }
		, y{ to.y - from.y }
		, z{ to.z - from.z }
	{}

	template<typename T>
	Vector<3, T> operator+(const Vector<3, T>& l, const Vector<3, T>& r)
	{
		return Vector<3, T>{ l.x + r.x, l.y + r.y, l.z + r.z };
	}

	template<typename T>
	Vector<3, T> operator-(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
	{
		return Vector<3, T>{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}

	template<typename T>
	Vector<3, T> operator*(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
	{
		return Vector<3, T>{ lhs.x* rhs.x, lhs.y* rhs.y, lhs.z*rhs.z };
	}

	template<typename T>
	Vector<3, T> operator*(const Vector<3, T>& lhs, const T rhs)
	{
		return Vector<3, T>{ lhs.x* rhs, lhs.y* rhs, lhs.z*rhs };
	}

	template<typename T>
	Vector<3, T> operator/(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
	{
		return Vector<3, T>{ lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
	}

	template<typename T>
	Vector<3, T> operator/(const Vector<3, T>& lhs, const T rhs)
	{
		return Vector<3, T>{ lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
	}

	template<typename T>
	Vector<3, T>& operator+=(Vector<3, T>& l, const Vector<3, T>& r)
	{
		l.x += r.x;
		l.y += r.y;
		l.z += r.z;

		return *this;
	}

	template<typename T>
	Vector<3, T>& operator-=(Vector<3, T>& l, const Vector<3, T>& r)
	{
		l.x -= r.x;
		l.y -= r.y;
		l.z -= r.z;

		return *this;
	}

	template<typename T>
	Vector<3, T>& operator*=(Vector<3, T>& l, const Vector<3, T>& r)
	{
		l.x *= r.x;
		l.y *= r.y;
		l.z *= r.z;

		return *this;
	}

	template<typename T>
	Vector<3, T>& operator*=(Vector<3, T>& l, const T r)
	{
		l.x *= r;
		l.y *= r;
		l.z *= z;

		return *this;
	}

	template<typename T>
	Vector<3, T>& operator/=(Vector<3, T>& l, const Vector<3, T>& r)
	{
		l.x /= r.x;
		l.y /= r.y;
		l.z /= r.z;

		return *this;
	}

	template<typename T>
	Vector<3, T>& operator/=(Vector<3, T>& l, const T r)
	{
		l.x /= r;
		l.y /= r;
		l.z /= r;

		return *this;
	}

	template<typename T>
	bool operator==(const Vector<3, T>& l, const Vector<3, T>& r)
	{
		return AreEqual(l.x, r.x) && AreEqual(l.y, r.y) && AreEqual(l.z, r.z);
	}

	template<typename T>
	bool operator!=(const Vector<3, T>& l, const Vector<3, T>& r)
	{
		return !(l == r);
	}

	template<typename T>
	T Dot(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	template<typename T>
	Vector<3, T> Cross(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
	{
		return Vector<3, T>{ 
			lhs.y* rhs.z - lhs.z * rhs.y,
			lhs.x* rhs.y - lhs.y * rhs.x, 
			lhs.z* rhs.x - lhs.x * rhs.z };
	}

	template<typename T>
	Vector<3, T> Orthogonal(const Vector<3, T>& lhs, const Vector<3, T>& cpVector = Vector<3, T>{ T(0),T(0),T(1) })
	{
		return Cross<T>(lhs, cpVector);
	}
}