#pragma once

#include "Polygon.h"
#include "PLine.h"
#include "Point2.h"
#include "Vector2.h"
#include "../Utils/Utils.h"

#include <algorithm>

#undef min
#undef max

namespace Integrian2D
{
	// == Specialisation of Polygon, being a Triangle ==
	template<typename Type>
	struct Polygon<3, Type>
	{
#pragma region Constructors
		//		    pointTwo
		//		   /		\
		//		  /			 \
		//		 /			  \
		//		/			   \
		//	   /				\
		//	  /					 \
		// pointOne ========= pointThree
		explicit Polygon<3, Type>()
		{}
		explicit Polygon<3, Type>(const Point<2, Type>& _center, const Type& _width, const Type& _height)
			: Polygon<3, Type>{ _center, _width, _height, Point<2, Type>{static_cast<Type>(1.f), static_cast<Type>(1.f)}, static_cast<Type>(0.f) }
		{}
		explicit Polygon<3, Type>(const Point<2, Type>& _center, const Type _width, const Type _height, const Point<2, Type>& _scale)
			: Polygon<3, Type>{ _center, _width, _height, _scale, static_cast<Type>(0.f) }
		{}
		explicit Polygon<3, Type>(const Point<2, Type>& _center, const Type _width, const Type _height, const Point<2, Type>& _scale, const Type _angle)
			: points{}
		{
			const Type halfWidth{ _width * static_cast<Type>(0.5f) };
			const Type halfHeight{ _height * static_cast<Type>(0.5f) };
			points.center = _center;
			points.pivotPoint = _center;
			points.pointOne = { _center.x - halfWidth, _center.y - halfHeight };
			points.pointTwo = { _center.x, _center.y + halfHeight };
			points.pointThree = { _center.x + halfWidth, _center.y - halfHeight };
			width = _width;
			height = _height;
			scaleX = _scale.x;
			scaleY = _scale.y;
			angle = _angle;

			if (!Utils::AreEqual(scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(scaleY, static_cast<Type>(1.f)))
				SetScale(*this, _scale);

			if (!Utils::AreEqual(_angle, static_cast<Type>(0.f)))
				SetRotation(*this, _angle);
		}
		explicit Polygon<3, Type>(const Point<2, Type>& _pointOne, const Point<2, Type>& _pointTwo, const Point<2, Type>& _pointThree)
			: Polygon<3, Type>{ _pointOne, _pointTwo, _pointThree, Point<2, Type>{static_cast<Type>(1.f), static_cast<Type>(1.f)}, static_cast<Type>(0.f) }
		{}
		explicit Polygon<3, Type>(const Point<2, Type>& _pointOne, const Point<2, Type>& _pointTwo, const Point<2, Type>& _pointThree,
			const Point<2, Type>& _scale, const Type _angle)
			: points{}
		{
			points.center = (_pointOne + _pointTwo + _pointThree) / static_cast<Type>(3.f);
			points.pivotPoint = points.center;

			points.pointOne = _pointOne;
			points.pointTwo = _pointTwo;
			points.pointThree = _pointThree;

			width = std::max(std::max(_pointOne.x, _pointTwo.x), _pointThree.x) - std::min(std::min(_pointOne.x, _pointTwo.x), _pointThree.x);
			height = std::max(std::max(_pointOne.y, _pointTwo.y), _pointThree.y) - std::min(std::min(_pointOne.y, _pointTwo.y), _pointThree.y);

			scaleX = _scale.x;
			scaleY = _scale.y;
			angle = _angle;

			if (!Utils::AreEqual(scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(scaleY, static_cast<Type>(1.f)))
				SetScale(*this, _scale);

			if (!Utils::AreEqual(_angle, static_cast<Type>(0.f)))
				SetRotation(*this, _angle);
		}
#pragma endregion

#pragma region Data
		class Points final
		{
		private:
			friend struct Polygon<3, Type>;

			template<int V, typename Type>
			friend void Translate(Polygon<3, Type>& p, const Vector<V, Type>& v) noexcept;
			template<typename Type>
			friend void Rotate(Polygon<3, Type>& p, const Type _angleChange) noexcept;
			template<typename Type>
			friend void SetRotation(Polygon<3, Type>& p, const Type _angle) noexcept;
			template<typename Type>
			friend void Scale(Polygon<3, Type>& p, const Point<2, Type>& scale) noexcept;
			template<typename Type>
			friend void SetScale(Polygon<3, Type>& p, const Point<2, Type>& scale) noexcept;
			template<typename Type>
			friend void SetCenter(Polygon<3, Type>& p, const Point<2, Type>& _center) noexcept;
			template<typename Type>
			friend void SetPivotPoint(Polygon<3, Type>& p, const Point<2, Type>& _pivotPoint) noexcept;
			template<typename Type>
			friend const Point<2, Type>& GetCenter(const Polygon<3, Type>& p) noexcept;
			template<typename Type>
			friend const Point<2, Type>& GetPivotPoint(const Polygon<3, Type>& p) noexcept;
			template<typename Type>
			friend void SetWidth(Polygon<3, Type>& p, const Type _width) noexcept;
			template<typename Type>
			friend void SetHeight(Polygon<3, Type>& p, const Type _height) noexcept;
			template<typename Type>
			friend Type GetArea(const Polygon<3, Type>& p) noexcept;
			template<typename Type>
			friend bool IsPointInTriangle(const Polygon<3, Type>& t, const Point<2, Type>& p) noexcept;
			template<typename Type>
			friend Polygon<2, Type> GetEdgeOne(const Polygon<3, Type>& t) noexcept;
			template<typename Type>
			friend Polygon<2, Type> GetEdgeTwo(const Polygon<3, Type>& t) noexcept;
			template<typename Type>
			friend Polygon<2, Type> GetEdgeThree(const Polygon<3, Type>& t) noexcept;

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

		Points points;
		Type width, height, scaleX, scaleY, angle;
#pragma endregion

#pragma region Iterator
		class iterator final
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = Point<2, Type>;
			using pointer = value_type*;
			using reference = value_type&;

			iterator(pointer pPointer) noexcept
				: m_Pointer{ pPointer }
			{}

			reference operator*() const noexcept { return *m_Pointer; }
			pointer operator->() noexcept { return m_Pointer; }

			iterator& operator++() noexcept { ++m_Pointer; return *this; }
			iterator& operator++(int) noexcept { iterator tmp = *this; ++(*this); return tmp; }
			iterator& operator--() noexcept { --m_Pointer; return *this; }
			iterator& operator--(int) noexcept { iterator tmp = *this; --(*this); return tmp; }
			iterator& operator+(const int v) noexcept { m_Pointer += v; return *this; }
			iterator& operator-(const int v) noexcept { m_Pointer -= v; return *this; }

			bool operator==(const iterator& other) const noexcept { return m_Pointer == other.m_Pointer; }
			bool operator!=(const iterator& other) const noexcept { return m_Pointer != other.m_Pointer; }

		private:
			pointer m_Pointer;
		};

		class const_iterator final
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = const Point<2, Type>;
			using pointer = value_type*;
			using reference = value_type&;

			const_iterator(pointer pPointer) noexcept
				: m_Pointer{ pPointer }
			{}

			reference operator*() const noexcept { return *m_Pointer; }
			pointer operator->() noexcept { return m_Pointer; }

			const_iterator& operator++() noexcept { ++m_Pointer; return *this; }
			const_iterator& operator++(int) noexcept { const_iterator tmp = *this; ++(*this); return tmp; }
			const_iterator& operator--() noexcept { --m_Pointer; return *this; }
			const_iterator& operator--(int) noexcept { const_iterator tmp = *this; --(*this); return tmp; }
			const_iterator& operator+(const int v) noexcept { m_Pointer += v; return *this; }
			const_iterator& operator-(const int v) noexcept { m_Pointer -= v; return *this; }

			bool operator==(const const_iterator& other) const noexcept { return m_Pointer == other.m_Pointer; }
			bool operator!=(const const_iterator& other) const noexcept { return m_Pointer != other.m_Pointer; }

		private:
			pointer m_Pointer;
		};

		iterator begin() noexcept
		{
			return iterator{ &points.pointOne };
		}

		const_iterator begin() const noexcept
		{
			return const_iterator{ &points.pointOne };
		}

		iterator end() noexcept
		{
			return iterator{ &points.pointThree + 1 };
		}

		const_iterator end() const noexcept
		{
			return const_iterator{ &points.pointThree + 1 };
		}
#pragma endregion
	};

#pragma region Relational Operators
	template<typename Type>
	bool operator==(const Polygon<3, Type>& a, const Polygon<3, Type>& b) noexcept
	{
		return a.points == b.points && a.width == b.width && a.height == b.height && a.scaleX == b.scaleX
			&& a.angle == b.angle;
	}

	template<typename Type>
	bool operator!=(const Polygon<3, Type>& a, const Polygon<3, Type>& b) noexcept
	{
		return !(a == b);
	}
#pragma endregion

#pragma region Functions
	template<int V, typename Type>
	void Translate(Polygon<3, Type>& p, const Vector<V, Type>& v) noexcept
	{
		static_assert(V > 1, "Polygon<3, Type>(=>Trianglef)::Translate() > A vector needs at least two dimensions");

		p.points.center += v;
		p.points.pivotPoint += v;
		p.points.pointOne += v;
		p.points.pointTwo += v;
		p.points.pointThree += v;
	}

	template<typename Type>
	void Rotate(Polygon<3, Type>& p, const Type _angleChange) noexcept
	{
		p.angle += _angleChange;

		SetRotation(p, p.angle);
	}

	template<typename Type>
	void SetRotation(Polygon<3, Type>& p, const Type _angle) noexcept
	{
		p.angle = _angle;

		const Type c{ static_cast<Type>(cos(_angle)) };
		const Type s{ static_cast<Type>(sin(_angle)) };
		const Point<2, Type>& pivotPoint{ p.points.pivotPoint };

		// == Translate all points with pivotpoint ==
		p.points.center -= pivotPoint;
		p.points.pointOne -= pivotPoint;
		p.points.pointTwo -= pivotPoint;
		p.points.pointThree -= pivotPoint;

		// == Rotate All Points ==
		p.points.center = { p.points.center.x * c - p.points.center.y * s, p.points.center.x * s + p.points.center.y * c };
		p.points.pointOne = { p.points.pointOne.x * c - p.points.pointOne.y * s, p.points.pointOne.x * s + p.points.pointOne.y * c };
		p.points.pointTwo = { p.points.pointTwo.x * c - p.points.pointTwo.y * s, p.points.pointTwo.x * s + p.points.pointTwo.y * c };
		p.points.pointThree = { p.points.pointThree.x * c - p.points.pointThree.y * s, p.points.pointThree.x * s + p.points.pointThree.y * c };

		// == Translate All Points Back ==
		p.points.center += pivotPoint;
		p.points.pointOne += pivotPoint;
		p.points.pointTwo += pivotPoint;
		p.points.pointThree += pivotPoint;
	}

	template<typename Type>
	void Scale(Polygon<3, Type>& p, const Point<2, Type>& scale) noexcept
	{
		p.scaleX += scale.x;
		p.scaleY += scale.y;

		SetScale(p, Point<2, Type>{ p.scaleX, p.scaleY });
	}

	template<typename Type>
	void SetScale(Polygon<3, Type>& p, const Point<2, Type>& scale) noexcept
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

		p.points.pointOne = { center.x - halfWidth * scale.x, center.y - halfHeight * scale.y };
		p.points.pointTwo = { center.x, center.y + halfHeight * scale.y };
		p.points.pointThree = { center.x + halfWidth * scale.x, center.y - halfHeight * scale.y };

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);
	}

	template<typename Type>
	void SetCenter(Polygon<3, Type>& p, const Point<2, Type>& _center) noexcept
	{
		const Vector<2, Type> toNewCenter{ p.points.center, _center };

		Translate(p, toNewCenter);
	}

	template<typename Type>
	void SetPivotPoint(Polygon<3, Type>& p, const Point<2, Type>& _pivotPoint) noexcept
	{
		p.points.pivotPoint = _pivotPoint;

		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
			SetRotation(p, p.angle);
	}

	template<typename Type>
	const Point<2, Type>& GetCenter(const Polygon<3, Type>& p) noexcept
	{
		return p.points.center;
	}

	template<typename Type>
	const Point<2, Type>& GetPivotPoint(const Polygon<3, Type>& p) noexcept
	{
		return p.points.pivotPoint;
	}

	template<typename Type>
	void SetWidth(Polygon<3, Type>& p, const Type _width) noexcept
	{
		Type originalAngle{};
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
		{
			originalAngle = p.angle;
			SetRotation(p, static_cast<Type>(0.f));
		}

		Point<2, Type> originalScale{ static_cast<Type>(1.f), static_cast<Type>(1.f) };
		if (!Utils::AreEqual(p.scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(p.scaleY, static_cast<Type>(1.f)))
		{
			originalScale = Point<2, Type>{ p.scaleX, p.scaleY };
			SetScale(p, Point<2, Type>{ static_cast<Type>(1.f), static_cast<Type>(1.f) });
		}

		const Type halfWidth{ _width * static_cast<Type>(0.5f) };
		p.points.pointOne = { p.points.center.x - halfWidth, p.points.pointOne.y };
		p.points.pointThree = { p.points.center.x + halfWidth, p.points.pointThree.y };
		p.width = _width;

		// == Scale, but only if the scale is not {1, 1}
		if (!Utils::AreEqual(originalScale.x, static_cast<Type>(1.f)) || !Utils::AreEqual(originalScale.y, static_cast<Type>(1.f)))
			SetScale(*this, originalScale);

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);
	}

	template<typename Type>
	void SetHeight(Polygon<3, Type>& p, const Type _height) noexcept
	{
		Type originalAngle{};
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
		{
			originalAngle = p.angle;
			SetRotation(p, static_cast<Type>(0.f));
		}

		Point<2, Type> originalScale{ static_cast<Type>(1.f), static_cast<Type>(1.f) };
		if (!Utils::AreEqual(p.scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(p.scaleY, static_cast<Type>(1.f)))
		{
			originalScale = Point<2, Type>{ p.scaleX, p.scaleY };
			SetScale(p, Point<2, Type>{ static_cast<Type>(1.f), static_cast<Type>(1.f) });
		}

		const Type halfHeight{ _height * static_cast<Type>(0.5f) };
		p.points.pointOne = { p.points.pointOne.x, p.points.center.y - halfHeight };
		p.points.pointTwo = { p.points.pointTwo.x, p.points.center.y + halfHeight };
		p.points.pointThree = { p.points.pointThree.x, p.points.center.y - halfHeight };
		p.height = _height;

		// == Scale, but only if the scale is not {1, 1}
		if (!Utils::AreEqual(originalScale.x, static_cast<Type>(1.f)) || !Utils::AreEqual(originalScale.y, static_cast<Type>(1.f)))
			SetScale(*this, originalScale);

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);
	}

	template<typename Type>
	Type GetArea(const Polygon<3, Type>& p) noexcept
	{
		const Point<2, Type>& pointOne{ p.points.pointOne };
		const Point<2, Type>& pointTwo{ p.points.pointTwo };
		const Point<2, Type>& pointThree{ p.points.pointThree };

		return static_cast<Type>(0.5f) * (-pointTwo.y * pointThree.x + pointOne.y * (-pointTwo.x + pointThree.x) +
			pointOne.x * (pointTwo.y - pointThree.y) + pointTwo.x * pointThree.y);
	}

	template<typename Type>
	bool IsPointInTriangle(const Polygon<3, Type>& t, const Point<2, Type>& p) noexcept
	{
		const Point<2, Type>& pointOne{ t.points.pointOne };
		const Point<2, Type>& pointTwo{ t.points.pointTwo };
		const Point<2, Type>& pointThree{ t.points.pointThree };
		const Type area{ -GetArea(t) }; // since we have clockwise numbering, we need to invert the area

		const Type parameterOne{ static_cast<Type>(1.f) / (static_cast<Type>(2.f) * area) * (pointOne.y * pointThree.x - pointOne.x * pointThree.y +
			p.x * (pointThree.y - pointOne.y) + p.y * (pointOne.x - pointThree.x)) };
		const Type parameterTwo{ static_cast<Type>(1.f) / (static_cast<Type>(2.f) * area) * (pointOne.x * pointTwo.y - pointOne.y * pointTwo.x +
			p.x * (pointOne.y - pointTwo.y) + p.y * (pointTwo.x - pointOne.x) ) };

		return (parameterOne >= static_cast<Type>(0.f)) && (parameterTwo >= static_cast<Type>(0.f)) &&
			((static_cast<Type>(1.f) - parameterOne - parameterTwo) >= static_cast<Type>(0.f));
	}

	template<typename Type>
	Polygon<2, Type> GetEdgeOne(const Polygon<3, Type>& t) noexcept
	{
		return Polygon<2, Type>{ t.points.pointOne, t.points.pointTwo };
	}

	template<typename Type>
	Polygon<2, Type> GetEdgeTwo(const Polygon<3, Type>& t) noexcept
	{
		return Polygon<2, Type>{ t.points.pointTwo, t.points.pointThree };
	}

	template<typename Type>
	Polygon<2, Type> GetEdgeThree(const Polygon<3, Type>& t) noexcept
	{
		return Polygon<2, Type>{ t.points.pointThree, t.points.pointOne };
	}
#pragma endregion
}