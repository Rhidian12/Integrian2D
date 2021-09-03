#pragma once

#include "Polygon.h"
#include "../Utils/Utils.h"
#include "Vector.h"
#include "Point.h"

#include <utility>

namespace Integrian2D
{
	// == Specialisation of Polygon ==
	template<typename Type>
	struct Polygon<4, Type>
	{
#pragma region Constructors
		explicit Polygon<4, Type>()
			: Polygon<4, Type>{ static_cast<Type>(0.f),static_cast<Type>(0.f) ,static_cast<Type>(0.f) ,static_cast<Type>(0.f) }
		{}
		explicit Polygon<4, Type>(const Type _x, const Type _y, const Type _width, const Type _height)
			: Polygon<4, Type>{ _x, _y, _width, _height, static_cast<Type>(0.f) }
		{}
		explicit Polygon<4, Type>(const Type _x, const Type _y, const Type _width, const Type _height, const Type _angle)
			: Polygon<4, Type>{ _x, _y, _width, _height, _angle, static_cast<Type>(1.f), static_cast<Type>(1.f) }
		{}
		explicit Polygon<4, Type>(const Type _x, const Type _y, const Type _width, const Type _height, const Type _angle, const Type _scaleX, const Type _scaleY)
			: Polygon<4, Type>{ Point<2, Type>{ _x, _y }, _width, _height, _angle, _scaleX, _scaleY }
		{}
		explicit Polygon<4, Type>(const Point<2, Type> _xy, const Type _width, const Type _height, const Type _angle, const Type _scaleX, const Type _scaleY)
			: points{}
		{
			points.leftBottom = _xy;
			points.leftTop = { _xy.x, _xy.y + _height };
			points.rightTop = { _xy.x + _width, _xy.y + _height };
			points.rightBottom = { _xy.x + _width, _xy.y };
			points.pivotPoint = { _xy.x + _width * static_cast<Type>(0.5f), _xy.y + _height * static_cast<Type>(0.5f) }; // pivot point is in the center by default
			width = _width;
			height = _height;
			scaleX = _scaleX;
			scaleY = _scaleY;
			angle = _angle;
		}
#pragma endregion

#pragma region Rule Of 5
		Polygon<4, Type>(const Polygon<4, Type>& other) noexcept
			: points{ other.points }
			, width{ other.width }
			, height{ other.height }
			, scaleX{ other.scaleX }
			, scaleY{ other.scaleY }
			, angle{ other.angle }
		{}
		Polygon<4, Type>(Polygon<4, Type>&& other) noexcept
			: points{ std::move(other.points) }
			, width{ std::move(other.width) }
			, height{ std::move(other.height) }
			, scaleX{ std::move(other.scaleX) }
			, scaleY{ std::move(other.scaleY) }
			, angle{ std::move(other.angle) }
		{}
		Polygon<4, Type>& operator=(const Polygon& other) noexcept
		{
			points = other.points;
			width = other.width;
			height = other.height;
			scaleX = other.scaleX;
			scaleY = other.scaleY;
			angle = other.angle;

			return *this;
		}
		Polygon<4, Type>& operator=(Polygon&& other) noexcept
		{
			points = std::move(other.points);
			width = std::move(other.width);
			height = std::move(other.height);
			scaleX = std::move(other.scaleX);
			scaleY = std::move(other.scaleY);
			angle = std::move(other.angle);

			return *this;
		}
#pragma endregion

#pragma region Data
		union
		{
			class Points final
			{
			private:
				friend struct Polygon<4, Type>;

				template<int V, typename Type>
				friend void Translate(Polygon<4, Type>& p, const Vector<V, Type>& v) noexcept;

				Point<2, Type> leftBottom, leftTop, rightTop, rightBottom, pivotPoint;

			public:
				bool operator==(const Points& rhs) const noexcept
				{
					return (leftBottom == rhs.leftBottom) && (leftTop == rhs.leftTop)
						&& (rightTop == rhs.rightTop) && (rightBottom == rhs.rightBottom)
						&& (pivotPoint == rhs.pivotPoint);
				}

				bool operator!=(const Points& rhs) noexcept
				{
					return !(*this == rhs);
				}

			};

			Points points;
			Type width, height, scaleX, scaleY, angle;
		};
#pragma endregion
	};

#pragma region Relational Operators
	template<typename Type>
	bool operator==(const Polygon<4, Type>& lhs, const Polygon<4, Type>& rhs) noexcept
	{
		return (lhs.points == rhs.points) && Utils::AreEqual(lhs.width, rhs.width)
			&& Utils::AreEqual(lhs.height, rhs.height) && Utils::AreEqual(lhs.scaleX, rhs.scaleX)
			&& Utils::AreEqual(lhs.scaleY, rhs.scaleY) && Utils::AreEqual(lhs.angle, rhs.angle);
	}

	template<typename Type>
	bool operator!=(const Polygon<4, Type>& lhs, const Polygon<4, Type>& rhs) noexcept
	{
		return !(lhs == rhs);
	}
#pragma endregion

#pragma region Functions
	template<int V, typename Type>
	void Translate(Polygon<4, Type>& p, const Vector<V, Type>& v) noexcept
	{
		static_assert(V > 1, "A vector needs at least two dimensions");

		p.points.leftBottom += v;
		p.points.leftTop += v;
		p.points.rightTop += v;
		p.points.rightBottom += v;
		p.points.pivotPoint += v;
	}
#pragma endregion
}