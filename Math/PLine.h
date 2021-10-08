#pragma once

#include "Polygon.h"
#include "Point2.h"

#include <utility>

namespace Integrian2D
{
	// == Specialisation of Polygon, Being a Line ==
	template<typename Type>
	struct Polygon<2, Type>
	{
#pragma region Constructors
		explicit Polygon<2, Type>()
			: Polygon<2, Type>{ Point<2, Type>{}, Point<2, Type>{}, static_cast<Type>(1.f), static_cast<Type>(1.f) }
		{}
		explicit Polygon<2, Type>(const Point<2, Type>& from, const Point<2, Type>& to)
			: Polygon<2, Type>{ from, to, static_cast<Type>(1.f), static_cast<Type>(1.f) }
		{}
		explicit Polygon<2, Type>(const Point<2, Type>& from, const Point<2, Type>& to, const Type& _scaleX, const Type& _scaleY)
			: Polygon<2, Type>{ from, to, static_cast<Type>(1.f), static_cast<Type>(1.f), static_cast<Type>(0.f) }
		{}
		explicit Polygon<2, Type>(const Point<2, Type>& from, const Point<2, Type>& to, const Type& _scaleX, const Type& _scaleY, const Type& _angle)
			: begin{ from }
			, end{ to }
		{
			center = Point<2, Type>{ to.x - from.x, to.y - from.y };
			pivotPoint = center;

			width = to.x >= from.x ? to.x - from.x : from.x - to.x;
			height = to.y >= from.y ? to.y - from.y : from.y - to.y;
			scaleX = _scaleX;
			scaleY = _scaleY;
			angle = _angle;
		}
#pragma endregion

#pragma region Rule Of 5
		Polygon<2, Type>(const Polygon<2, Type>& other) noexcept
			: begin{ other.begin }
			, end{ other.end }
		{}
		Polygon<2, Type>(Polygon<2, Type>&& other) noexcept
			: begin{ std::move(other.begin) }
			, end{ std::move(other.end) }
		{}
		Polygon<2, Type>& operator=(const Polygon<2, Type>& other) noexcept
		{
			begin = other.begin;
			end = other.end;

			return *this;
		}
		Polygon<2, Type>& operator=(Polygon<2, Type>&& other) noexcept
		{
			begin = std::move(other.begin);
			end = std::move(other.end);

			return *this;
		}
#pragma endregion

#pragma region Data
		class Points final
		{
		private:
			friend struct Polygon<2, Type>;

			template<int V, typename Type>
			friend void Translate(Polygon<2, Type>& p, const Vector<V, Type>& v) noexcept;
			template<typename Type>
			friend void Rotate(Polygon<2, Type>& p, const Type& _angleChange) noexcept;
			template<typename Type>
			friend void Scale(Polygon<2, Type>& p, const Point<2, Type>& scale) noexcept;
			template<typename Type>
			friend void SetRotation(Polygon<2, Type>& p, const Type& _angle) noexcept;
			template<typename Type>
			friend void SetScale(Polygon<2, Type>& p, const Point<2, Type>& scale) noexcept;
			template<typename Type>
			friend void SetCenter(Polygon<2, Type>& p, const Point<2, Type> _center) noexcept;
			template<typename Type>
			friend const Point<2, Type>& GetCenter(const Polygon<2, Type>& p) noexcept;
			template<typename Type>
			friend void SetPivotPoint(Polygon<2, Type>& p, const Point<2, Type> _pivotPoint) noexcept;
			template<typename Type>
			friend const Point<2, Type>& GetPivotPoint(const Polygon<2, Type>& p) noexcept;

			Point<2, Type> center, pivotPoint;

		public:
			bool operator==(const Points& other) const noexcept
			{
				return center == other.center && pivotPoint == other.pivotPoint;
			}

			bool operator!=(const Points& other) const noexcept
			{
				return !(*this == other);
			}
		};

		Point<2, Type> begin, end;
		Type width, height, scaleX, scaleY, angle;
#pragma endregion
	};

#pragma region Functions
	template<int V, typename Type>
	void Translate(Polygon<2, Type>& p, const Vector<V, Type>& v) noexcept
	{
		static_assert(V > 1, "A vector needs at least two dimensions");

		p.begin += v;
		p.end += v;
		p.points.center += v;
		p.points.pivotPoint += v;
	}
	
	template<typename Type>
	void Rotate(Polygon<2, Type>& p, const Type& _angleChange) noexcept
	{
		p.angle += _angleChange;

		SetRotation(p, p.angle);
	}
	
	template<typename Type>
	void Scale(Polygon<2, Type>& p, const Point<2, Type>& scale) noexcept
	{
		p.scaleX += scale.x;
		p.scaleY += scale.y;

		SetScale(p, Point<2, Type>{ p.scaleX, p.scaleY });
	}
	
	template<typename Type>
	void SetRotation(Polygon<2, Type>& p, const Type& _angle) noexcept
	{
		p.angle = _angle;

		const Type c{ static_cast<Type>(cos(_angle)) };
		const Type s{ static_cast<Type>(sin(_angle)) };
		const Point<2, Type>& pivotPoint{ p.points.pivotPoint };

		// == Translate all points with pivotpoint ==
		p.begin -= pivotPoint;
		p.end -= pivotPoint;
		p.points.center -= pivotPoint;

		// == Rotate All Points ==
		p.begin = { p.begin.x * c - p.begin.y * s, p.begin.x * s + p.begin.y * c };
		p.end = { p.end.x * c - p.end.y * s, p.end.x * s + p.end.y * c };
		p.points.center = { p.points.center.x * c - p.points.center.y * s, p.points.center.x * s + p.points.center.y * c };

		// == Translate All Points Back ==
		p.begin += pivotPoint;
		p.end += pivotPoint;
		p.points.center += pivotPoint;
	}
	
	template<typename Type>
	void SetScale(Polygon<2, Type>& p, const Point<2, Type>& scale) noexcept
	{
		Type originalAngle{};
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
		{
			originalAngle = p.angle;
			SetRotation(p, static_cast<Type>(0.f));
		}

		p.scaleX = scale.x;
		p.scaleY = scale.y;

		const Type halfWidth{ p.width * static_cast<Type>(0.5f) };
		const Type halfHeight{ p.height * static_cast<Type>(0.5f) };
		const Point<2, Type>& center{ p.points.center };

		if (p.begin.x >= p.end.x)
		{
			p.begin.x = center.x + halfWidth * scale.x;
			p.end.x = center.x - halfWidth * scale.x;
		}
		else
		{
			p.begin.x = center.x - halfWidth * scale.x;
			p.end.x = center.x + halfWidth * scale.x;
		}

		if (p.begin.y >= p.end.y)
		{
			p.begin.y = center.y + halfHeight * scale.y;
			p.end.y = center.y - halfHeight * scale.y;
		}
		else
		{
			p.begin.y = center.y - halfHeight * scale.y;
			p.end.y = center.y + halfHeight * scale.y;
		}
		
		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);
	}

	template<typename Type>
	void SetCenter(Polygon<2, Type>& p, const Point<2, Type> _center) noexcept
	{
		Type originalAngle{};
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
		{
			originalAngle = p.angle;
			SetRotation(p, static_cast<Type>(0.f));
		}

		p.points.center = _center;

		const Type halfWidth{ p.width * static_cast<Type>(0.5f) };
		const Type halfHeight{ p.height * static_cast<Type>(0.5f) };

		p.points.center = _center;
		p.points.pivotPoint = _center; // pivot point is in the center by default
		
		if (p.begin.x >= p.end.x)
		{
			p.begin.x = _center.x + halfWidth;
			p.end.x = _center.x - halfWidth;
		}
		else
		{
			p.begin.x = center.x - halfWidth;
			p.end.x = center.x + halfWidth;
		}

		if (p.begin.y >= p.end.y)
		{
			p.begin.y = center.y + halfHeight;
			p.end.y = center.y - halfHeight;
		}
		else
		{
			p.begin.y = center.y - halfHeight;
			p.end.y = center.y + halfHeight;
		}

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);

		// == Scale, but only if the scale is not 1 ==
		if (!Utils::AreEqual(p.scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(p.scaleY, static_cast<Type>(1.f)))
			SetScale(p, Point<2, Type>{ p.scaleX, p.scaleY });
	}

	template<typename Type>
	const Point<2, Type>& GetCenter(const Polygon<2, Type>& p) noexcept
	{
		return p.points.center;
	}

	template<typename Type>
	void SetPivotPoint(Polygon<2, Type>& p, const Point<2, Type> _pivotPoint) noexcept
	{

	}

	template<typename Type>
	friend const Point<2, Type>& GetPivotPoint(const Polygon<2, Type>& p) noexcept;
#pragma endregion
}