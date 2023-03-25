#pragma once

#include "../Integrian2D_API.h"
#include "AreEqual.h"
#include "Point2.h"

namespace Integrian2D::Math
{
	template<typename T>
	struct Circle
	{
	#pragma region Ctors

		Circle();
		Circle(const Point<2, T>& pos, const T _radius);

	#pragma endregion

	#pragma region Data

		T Radius;
		Point<2, T> Position; // centre of circle

	#pragma endregion
	};

	template<typename T>
	Circle<T>::Circle()
		: Radius{}
		, Position{}
	{}

	template<typename T>
	Circle<T>::Circle(const Point<2, T>& pos, const T _radius)
		: Radius{ _radius }
		, Position{ pos }
	{}

	template<typename T>
	bool operator==(const Circle<T>& c1, const Circle<T>& c2)
	{
		return AreEqual(c1.Radius, c2.Radius) && (c1.Position == c2.Position);
	}

	template<typename T>
	bool operator!=(const Circle<T>& c1, const Circle<T>& c2)
	{
		return !(c1 == c2);
	}
}