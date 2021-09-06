#pragma once

#include "Point.h"

namespace Integrian2D
{
	template<int Points, typename Type>
	struct Polygon
	{
		Point<2, Type> data[Points];

		// == Operator[] Is Required To Be A Member ==
		Type& operator[](const size_t i)
		{
			ASSERT(i < Points, "Point<Points, Type>::operator[] > Index is out of bounds!");
			return data[i];
		}

		const Type& operator[](const size_t i) const
		{
			ASSERT(i < Points, "Polygon<Points, Type>::operator[] > Index is out of bounds!");
			return data[i];
		}
	};
}