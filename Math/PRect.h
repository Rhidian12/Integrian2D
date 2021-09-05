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
				template<typename Type>
				friend void Rotate(Polygon<4, Type>& p, const Type _angleChange) noexcept;
				template<typename Type>
				friend void SetRotation(Polygon<4, Type>& p, const Type _angle) noexcept;
				template<typename Type>
				friend void SetLeftBottom(Polygon<4, Type>& p, const Point<2, Type> _leftBottom) noexcept;
				template<typename Type>
				friend const Point<2, Type>& GetLeftBottom(const Polygon<4, Type>& p) noexcept;
				template<typename Type>
				friend const Point<2, Type>& GetLeftTop(const Polygon<4, Type>& p) noexcept;
				template<typename Type>
				friend const Point<2, Type>& GetRightTop(const Polygon<4, Type>& p) noexcept;
				template<typename Type>
				friend const Point<2, Type>& GetRightBottom(const Polygon<4, Type>& p) noexcept;
				template<typename Type>
				friend void SetPivotPoint(Polygon<4, Type>& p, const Point<2, Type> _pivotPoint) noexcept;
				template<typename Type>
				friend const Point<2, Type>& GetPivotPoint(const Polygon<4, Type>& p) noexcept;
				template<typename Type>
				friend void SetWidth(Polygon<4, Type>& p, const Type _width) noexcept;
				template<typename Type>
				friend void SetHeight(Polygon<4, Type>& p, const Type _height) noexcept;

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

	template<typename Type>
	void Rotate(Polygon<4, Type>& p, const Type _angleChange) noexcept
	{
		p.angle += _angleChange;

		SetRotation(p, p.angle);
	}

	template<typename Type>
	void SetRotation(Polygon<4, Type>& p, const Type _angle) noexcept
	{
		p.angle = _angle;

		const Type c{ static_cast<Type>(cos(_angle)) };
		const Type s{ static_cast<Type>(sin(_angle)) };
		const Point<2, Type>& pivotPoint{ p.points.pivotPoint };

		// == Translate all points with pivotpoint ==
		p.points.leftBottom -= pivotPoint;
		p.points.leftTop -= pivotPoint;
		p.points.rightTop -= pivotPoint;
		p.points.rightBottom -= pivotPoint;

		// == Rotate All Points ==
		p.points.leftBottom = { p.points.leftBottom.x * c - p.points.leftBottom.y * s, p.points.leftBottom.x * s + p.points.leftBottom.y * c };
		p.points.leftTop = { p.points.leftTop.x * c - p.points.leftTop.y * s, p.points.leftTop.x * s + p.points.leftTop.y * c };
		p.points.rightTop = { p.points.rightTop.x * c - p.points.rightTop.y * s, p.points.rightTop.x * s + p.points.rightTop.y * c };
		p.points.rightBottom = { p.points.rightBottom.x * c - p.points.rightBottom.y * s, p.points.rightBottom.x * s + p.points.rightBottom.y * c };

		// == Translate All Points Back ==
		p.points.leftBottom += pivotPoint;
		p.points.leftTop += pivotPoint;
		p.points.rightTop += pivotPoint;
		p.points.rightBottom += pivotPoint;
	}

	template<typename Type>
	void SetLeftBottom(Polygon<4, Type>& p, const Point<2, Type> _leftBottom) noexcept
	{
		p.points.leftBottom = _leftBottom;
		p.points.leftTop = { _leftBottom.x, _leftBottom.y + p.height };
		p.points.rightTop = { _leftBottom.x + p.width, _leftBottom.y + p.height };
		p.points.rightBottom = { _leftBottom.x + p.width, _leftBottom.y };
		p.points.pivotPoint = { _leftBottom.x + p.width * static_cast<Type>(0.5f), _leftBottom.y + p.height * static_cast<Type>(0.5f) };

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
			SetRotation(p, p.angle);
	}

	template<typename Type>
	const Point<2, Type>& GetLeftBottom(const Polygon<4, Type>& p) noexcept
	{
		return p.points.leftBottom;
	}

	template<typename Type>
	const Point<2, Type>& GetLeftTop(const Polygon<4, Type>& p) noexcept
	{
		return p.points.leftTop;
	}

	template<typename Type>
	const Point<2, Type>& GetRightTop(const Polygon<4, Type>& p) noexcept
	{
		return p.points.rightTop;
	}

	template<typename Type>
	const Point<2, Type>& GetRightBottom(const Polygon<4, Type>& p) noexcept
	{
		return p.points.rightBottom;
	}

	template<typename Type>
	void SetPivotPoint(Polygon<4, Type>& p, const Point<2, Type> _pivotPoint) noexcept
	{
		p.points.pivotPoint = _pivotPoint;
	}

	template<typename Type>
	const Point<2, Type>& GetPivotPoint(const Polygon<4, Type>& p) noexcept
	{
		return p.points.pivotPoint;
	}

	template<typename Type>
	void SetWidth(Polygon<4, Type>& p, const Type _width) noexcept
	{
		p.width = _width;

		p.points.rightTop = { p.points.leftBottom.x + _width, p.points.rightTop.y };
		p.points.rightBottom = { p.points.leftBottom.x + _width, p.points.rightBottom.y };
		p.points.pivotPoint = { p.points.leftBottom.x + _width * static_cast<Type>(0.5f), p.points.pivotPoint.y };
	}

	template<typename Type>
	void SetHeight(Polygon<4, Type>& p, const Type _height) noexcept
	{
		p.height = _height;

		p.points.leftTop = { p.points.leftTop.x, p.points.leftBottom.y + _height };
		p.points.rightTop = { p.points.rightTop.x, p.points.leftBottom.y + _height };
		p.points.pivotPoint = { p.points.pivotPoint.x, p.points.leftBottom.y + _height * static_cast<Type>(0.5f) };
	}
#pragma endregion
}