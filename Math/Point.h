#pragma once

#include "../Integrian2D_API.h"

#include "Vector.h"

namespace Integrian2D::Math
{
	template<int N, typename Type>
	struct Point
	{
		Type Data[N];
	};

	template<int N, typename T>
	T DistanceSquared(const Point<N, T>& p1, const Point<N, T>& p2) noexcept
	{
		const Vector<N, T> vector{ p1, p2 };
		return static_cast<T>(MagnitudeSquared(vector));
	}

	template<int N, typename T>
	T Distance(const Point<N, T>& p1, const Point<N, T>& p2) noexcept
	{
		const Vector<N, T> vector{ p1, p2 };
		return static_cast<T>(sqrt(MagnitudeSquared(vector)));
	}
};
