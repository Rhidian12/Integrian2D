#pragma once

#include "Polygon.h"
#include "Point2.h"

namespace Integrian2D
{
	// == Specialisation of Polygon, being a Triangle ==
	template<typename Type>
	struct Polygon<3, Type>
	{

#pragma region Data
		class Points final
		{
		private:
			friend struct Polygon<3, Type>;

			Point<2, Type> pointOne, pointTwo, pointThree, center, pivotPoint;

		public:
			bool operator==(const Points& rhs) const noexcept
			{
				return (pointOne == rhs.pointOne) && (pointTwo == rhs.pointTwo) && (pointThree == rhs.pointThree)
					&& (center == rhs.center) && (pivotPoint == rhs.pivotPoint);
			}
			bool operator!=(const Points& rhs) const noexcept
			{
				return !(*this == rhs);
			}
		};
	};
#pragma endregion
}