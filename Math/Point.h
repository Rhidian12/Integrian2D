#pragma once

#include "Vector.h"

namespace Integrian2D
{
	/* This is the base class representing a point
	   I suggest using the provided Point2f type, but others can be created using this class */

	template<int P, typename Type>
	struct Point
	{
		// == Data ==
		Type data[P];

#pragma region Access Operators
		Type& operator[](const int index) noexcept
		{
			return data[index];
		}
		const Type& operator(const int index) const noexcept
		{
			return data[index];
		}
#pragma endregion
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
