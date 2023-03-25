#pragma once

#include "../Integrian2D_API.h"

#include <limits>

namespace Integrian2D::Math
{
	template<typename T>
	__NODISCARD constexpr bool AreEqual(const T a, const T b, const T epsilon = std::numeric_limits<T>::epsilon())
	{
		static_assert(std::is_fundamental_v<T>, "Math::AreEqual<T>() > T must be a fundamental type");

		return static_cast<T>(abs(a - b)) <= epsilon;
	}
}