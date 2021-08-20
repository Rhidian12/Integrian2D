#pragma once

#ifndef INTEGRIAN2D_POINT_H
#define INTEGRIAN2D_POINT_H

#include <limits> // std::numeric_limits
#include <cstdint>
#include "Vector.h" // Vector
#include "../Utils/Utils.h"

namespace Integrian2D
{
	template<int P, typename Type>
	struct Point
	{
		// == Data ==
		Type data[P];
	
		// == Operator[] Is Required To Be A Member ==
		Type& operator[](uint8_t i)
		{
			Utils::Assert(i < P, "Point<P, Type>::operator[] > Index is out of bounds!");
			return data[i];
		}

		const Type& operator[](uint8_t i) const
		{
			Utils::Assert(i < P, "Point<P, Type>::operator[] > Index is out of bounds!");
			return data[i];
		}
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
}

#endif // !ENGINE_POINT_H