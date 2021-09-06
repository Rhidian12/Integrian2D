#pragma once

#include "../Utils/Utils.h"

namespace Integrian2D
{
	template<int V, typename Type>
	struct Vector
	{
		// == Data == 
		Type data[V];
	};

	// == Non-Member Methods That Are Useful For All Vectors ==
	template<int V, typename Type>
	Type MagnitudeSquared(const Vector<V, Type>& v1) noexcept
	{
		return Dot(v1, v1);
	}

	template<int V, typename Type>
	Type Magnitude(const Vector<V, Type>& v1) noexcept
	{
		return static_cast<Type>(sqrt(MagnitudeSquared(v1)));
	}

	template<int V, typename Type>
	Type Normalize(Vector<V, Type>& v1)
	{
		const Type magnitude{ Magnitude(v1) };

		ASSERT(magnitude != static_cast<Type>(0.f), "Vector::Normalize() > Magnitude cannot be 0!");

		v1 /= magnitude;
		return magnitude;
	}

	template<int V, typename Type>
	Vector<V, Type> GetNormalized(const Vector<V, Type>& v1)
	{
		Vector<V, Type> temp{ v1 };
		Normalize(temp);
		return temp;
	}
}

