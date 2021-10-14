#pragma once

#include "Point2.h"

#include <utility>

namespace Integrian2D
{
	template<typename Type>
	struct Triangle
	{
#pragma region Constructors
		explicit Triangle()
			: leftPoint{}
			, topPoint{}
			, rightPoint{}
		{}

#pragma endregion

#pragma region Data
		Point<2, Type> leftPoint, topPoint, rightPoint;
#pragma endregion
	};
}