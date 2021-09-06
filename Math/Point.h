#pragma once

#include <limits> // std::numeric_limits
#include <cstdint>
#include "Vector.h"
#include "../Utils/Utils.h"

namespace Integrian2D
{
	template<int P, typename Type>
	struct Point
	{
		// == Data ==
		Type data[P];
	};

	// == Non-Member Functions That Are Useful For All Points ==
	template<int P, typename Type>
	Type DistanceSquared(const Point<P, Type>& p1, const Point<P, Type>& p2) noexcept
	{
		const Vector<P, Type> vector{ p1, p2 };
		return static_cast<Type>(MagnitudeSquared(vector));
	}
	template<int P, typename Type>
	Type Distance(const Point<P, Type>& p1, const Point<P, Type>& p2) noexcept
	{
		const Vector<P, Type> vector{ p1, p2 };
		return static_cast<Type>(sqrt(MagnitudeSquared(vector)));
	}
};
