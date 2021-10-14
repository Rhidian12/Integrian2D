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
		explicit Triangle(const Point<2, Type>& _leftPoint, const Point<2, Type>& _topPoint, const Point<2, Type>& _rightPoint)
			: leftPoint{ _leftPoint }
			, topPoint{ _topPoint }
			, rightPoint{ _rightPoint }
		{}
#pragma endregion

#pragma region Rule of 5
		Triangle(const Triangle& other) noexcept
			: leftPoint{ other.leftPoint }
			, topPoint{ other.topPoint }
			, rightPoint{ other.rightPoint }
		{}
		Triangle(Triangle&& other) noexcept
			: leftPoint{ std::move(other.leftPoint) }
			, topPoint{ std::move(other.topPoint) }
			, rightPoint{ std::move(other.rightPoint) }
		{}
		Triangle& operator=(const Triangle& other) noexcept
		{
			leftPoint = other.leftPoint;
			rightPoint = other.rightPoint;
			topPoint = other.topPoint;

			return *this;
		}
		Triangle& operator=(Triangle&& other) noexcept
		{
			leftPoint = std::move(other.leftPoint);
			rightPoint = std::move(other.rightPoint);
			topPoint = std::move(other.topPoint);

			return *this;
		}
#pragma endregion

#pragma region Data
		Point<2, Type> leftPoint, topPoint, rightPoint;
#pragma endregion
	};

#pragma region Relational Operators
	template<typename Type>
	inline bool operator==(const Triangle<Type>& a, const Triangle<Type>& b) noexcept
	{
		return a.leftPoint == b.leftPoint && a.topPoint == b.topPoint && a.rightPoint == b.rightPoint;
	}

	template<typename Type>
	inline bool operator!=(const Triangle<Type>& a, const Triangle<Type>& b) noexcept
	{
		return !(a == b);
	}
#pragma endregion
}