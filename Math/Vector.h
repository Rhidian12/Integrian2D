#pragma once

#include "../Integrian2D_API.h"

namespace Integrian2D::Math
{
	template<int N, typename T>
	struct Vector
	{
		T Data[N];
	};

	template<int N, typename T>
	T MagnitudeSquared(const Vector<N, T>& v1)
	{
		return Dot(v1, v1);
	}

	template<int N, typename T>
	T Magnitude(const Vector<N, T>& v1)
	{
		return static_cast<T>(sqrt(MagnitudeSquared(v1)));
	}

	template<int N, typename T>
	T Normalize(Vector<N, T>& v1)
	{
		const T magnitude{ Magnitude(v1) };

		__ASSERT(magnitude != static_cast<T>(0.f) && "Vector::Normalize() > Magnitude cannot be 0!");

		v1 /= magnitude;
		return magnitude;
	}

	template<int N, typename T>
	Vector<N, T> GetNormalized(const Vector<N, T>& v1)
	{
		Vector<N, T> temp{ v1 };
		Normalize(temp);
		return temp;
	}
}