#pragma once

#include "Point.h"
#include "Point2.h"
#include "Point3.h"

#include "Vector.h"
#include "Vector2.h"

#include "Rect.h"
#include "Circle.h"
#include "RGBColour.h"

#include "Matrix.h"

#include "AreEqual.h"

#include <random> /* std::random_device */

namespace Integrian2D::Math
{
#pragma region Typedefs

	using Point2f = Point<2, float>;
	using Point3f = Point<3, float>;

	using Vector2f = Vector<2, float>;
	using Vector3f = Vector<3, float>;

	using Rectf = Rect<float>;
	using Circlef = Circle<float>;

	using Matrix2x2 = Matrix<2, 2, float>;
	using Matrix3x3 = Matrix<3, 3, float>;

#pragma endregion

#pragma region Variables

	inline constexpr double Pi{ 3.14159265358979323846264338327950288 };
	inline constexpr double Pi_2{ Pi / 2.0 };
	inline constexpr double Pi_4{ Pi / 4.0 };

	namespace Detail
	{
		inline size_t Seed{}; /* Set in Core::CreateCore() once at engine start up, can be set later as well by the user */
		inline std::mt19937 RNGEngine{ Seed };
	}

#pragma endregion

#pragma region Math_Functions

	INTEGRIAN2D_API void SetSeed(const size_t seed);

	template<typename T>
	__NODISCARD constexpr T ToRadians(const T deg)
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "Math::ToRadians<T>() > T must be an integral or floating point type");

		return static_cast<T>(deg * Pi / 180.0);
	}

	template<typename T>
	__NODISCARD constexpr T ToDegrees(const T rad)
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "Math::ToDegrees<T>() > T must be an integral or floating point type");

		return static_cast<T>(rad * 180.0 / Pi);
	}

	template<typename T>
	constexpr void Clamp(T& value, const T& min, const T& max)
	{
		if (value < min)
		{
			value = min;
		}

		if (value > max)
		{
			value = max;
		}
	}

	template<typename T>
	__NODISCARD constexpr bool IsInRange(const T& value, const T& min, const T& max)
	{
		if (value < min)
			return false;

		if (value >= max)
			return false;

		return true;
	}

	template<typename T>
	__INLINE __NODISCARD constexpr T Max(const T& a, const T& b)
	{
		return a < b ? b : a;
	}

	template<typename T>
	__INLINE __NODISCARD constexpr T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

#pragma endregion
}