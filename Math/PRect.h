#pragma once

#include "Polygon.h"
#include "../Utils/Utils.h"
#include "Vector.h"
#include "Point2.h"

#include <utility>

namespace Integrian2D
{
	// == Specialisation of Polygon, Being a Rectangle ==
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
			const Type halfWidth{ _width * static_cast<Type>(0.5f) };
			const Type halfHeight{ _height * static_cast<Type>(0.5f) };

			points.center = _xy;
			points.leftBottom = { _xy.x - halfWidth, _xy.y - halfHeight };
			points.leftTop = { _xy.x - halfWidth, _xy.y + halfHeight };
			points.rightTop = { _xy.x + halfWidth, _xy.y + halfHeight };
			points.rightBottom = { _xy.x + halfWidth, _xy.y - halfHeight };
			points.pivotPoint = _xy; // pivot point is in the center by default
			width = _width;
			height = _height;
			scaleX = _scaleX;
			scaleY = _scaleY;
			angle = _angle;

			// == Rotate, but only if the angle is not 0 ==
			if (!Utils::AreEqual(angle, static_cast<Type>(0.f)))
				SetRotation(*this, angle);

			// == Scale, but only if the scale is not 1 ==
			if (!Utils::AreEqual(scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(scaleY, static_cast<Type>(1.f)))
				SetScale(*this, Point<2, Type>{ scaleX, scaleY });
		}
#pragma endregion

#pragma region Rule Of 5
		Polygon<4, Type>(const Polygon<4, Type>& other) noexcept
		{
			points = other.points;
			width = other.width;
			height = other.height;
			scaleX = other.scaleX;
			scaleY = other.scaleY;
			angle = other.angle;
		}
		Polygon<4, Type>(Polygon<4, Type>&& other) noexcept
		{
			points = std::move(other.points);
			width = std::move(other.width);
			height = std::move(other.height);
			scaleX = std::move(other.scaleX);
			scaleY = std::move(other.scaleY);
			angle = std::move(other.angle);
		}
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
		class Points final
		{
		private:
			friend struct Polygon<4, Type>;

			template<int V, typename Type>
			friend void Translate(Polygon<4, Type>& p, const Vector<V, Type>& v) noexcept;
			template<typename Type>
			friend void Rotate(Polygon<4, Type>& p, const Type _angleChange) noexcept;
			template<typename Type>
			friend void Scale(Polygon<4, Type>& p, const Point<2, Type> scale) noexcept;
			template<typename Type>
			friend void SetRotation(Polygon<4, Type>& p, const Type _angle) noexcept;
			template<typename Type>
			friend void SetScale(Polygon<4, Type>& p, const Point<2, Type> scale) noexcept;
			template<typename Type>
			friend void SetCenter(Polygon<4, Type>& p, const Point<2, Type> _center) noexcept;
			template<typename Type>
			friend const Point<2, Type>& GetCenter(const Polygon<4, Type>& p) noexcept;
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

			Point<2, Type> center, leftBottom, leftTop, rightTop, rightBottom, pivotPoint;

		public:
			bool operator==(const Points& rhs) const noexcept
			{
				return (leftBottom == rhs.leftBottom) && (leftTop == rhs.leftTop)
					&& (rightTop == rhs.rightTop) && (rightBottom == rhs.rightBottom)
					&& (pivotPoint == rhs.pivotPoint) && (center == rhs.center);
			}

			bool operator!=(const Points& rhs) noexcept
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

			inline reference operator*() const noexcept { return *m_Pointer; }
			inline pointer operator->() noexcept { return m_Pointer; }
			
			inline iterator& operator++() noexcept { ++m_Pointer; return *this; }
			inline iterator& operator++(int) noexcept { iterator tmp = *this; ++(*this); return tmp; }
			inline iterator& operator--() noexcept { --m_Pointer; return *this; }
			inline iterator& operator--(int) noexcept { iterator tmp = *this; --(*this); return tmp; }

			inline bool operator==(const iterator& other) const noexcept { return m_Pointer == other.m_Pointer; }
			inline bool operator!=(const iterator& other) const noexcept { return m_Pointer != other.m_Pointer; }

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

			inline reference operator*() const noexcept { return *m_Pointer; }
			inline pointer operator->() noexcept { return m_Pointer; }

			inline const_iterator& operator++() noexcept { ++m_Pointer; return *this; }
			inline const_iterator& operator++(int) noexcept { const_iterator tmp = *this; ++(*this); return tmp; }
			inline const_iterator& operator--() noexcept { --m_Pointer; return *this; }
			inline const_iterator& operator--(int) noexcept { const_iterator tmp = *this; --(*this); return tmp; }

			inline bool operator==(const const_iterator& other) const noexcept { return m_Pointer == other.m_Pointer; }
			inline bool operator!=(const const_iterator& other) const noexcept { return m_Pointer != other.m_Pointer; }

		private:
			pointer m_Pointer;
		};

		iterator begin() noexcept
		{
			return iterator{ &points.center };
		}

		const_iterator begin() const noexcept
		{
			return const_iterator{ &points.center };
		}

		iterator end() noexcept
		{
			return iterator{ &points.rightBottom + 1 };
		}

		const_iterator end() const noexcept
		{
			return const_iterator{ &points.rightBottom + 1 };
		}
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
		p.points.center += v;
	}

	template<typename Type>
	void Rotate(Polygon<4, Type>& p, const Type _angleChange) noexcept
	{
		p.angle += _angleChange;

		SetRotation(p, p.angle);
	}

	template<typename Type>
	void Scale(Polygon<4, Type>& p, const Point<2, Type> scale) noexcept
	{
		p.scaleX += scale.x;
		p.scaleY += scale.y;

		SetScale(p, Point<2, Type>{ p.scaleX, p.scaleY });
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
		p.points.center -= pivotPoint;

		// == Rotate All Points ==
		p.points.leftBottom = { p.points.leftBottom.x * c - p.points.leftBottom.y * s, p.points.leftBottom.x * s + p.points.leftBottom.y * c };
		p.points.leftTop = { p.points.leftTop.x * c - p.points.leftTop.y * s, p.points.leftTop.x * s + p.points.leftTop.y * c };
		p.points.rightTop = { p.points.rightTop.x * c - p.points.rightTop.y * s, p.points.rightTop.x * s + p.points.rightTop.y * c };
		p.points.rightBottom = { p.points.rightBottom.x * c - p.points.rightBottom.y * s, p.points.rightBottom.x * s + p.points.rightBottom.y * c };
		p.points.center = { p.points.center.x * c - p.points.center.y * s, p.points.center.x * s + p.points.center.y * c };

		// == Translate All Points Back ==
		p.points.leftBottom += pivotPoint;
		p.points.leftTop += pivotPoint;
		p.points.rightTop += pivotPoint;
		p.points.rightBottom += pivotPoint;
		p.points.center += pivotPoint;
	}

	template<typename Type>
	void SetScale(Polygon<4, Type>& p, const Point<2, Type> scale) noexcept
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

		p.points.leftBottom = { center.x - halfWidth * scale.x, center.y - halfHeight * scale.y };
		p.points.leftTop = { center.x - halfWidth * scale.x, center.y + halfHeight * scale.y };
		p.points.rightTop = { center.x + halfWidth * scale.x, center.y + halfHeight * scale.y };
		p.points.rightBottom = { center.x + halfWidth * scale.x, center.y - halfHeight * scale.y };

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);
	}

	template<typename Type>
	void SetCenter(Polygon<4, Type>& p, const Point<2, Type> _center) noexcept
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
		p.points.leftBottom = { _center.x - halfWidth, _center.y - halfHeight };
		p.points.leftTop = { _center.x - halfWidth, _center.y + halfHeight };
		p.points.rightTop = { _center.x + halfWidth, _center.y + halfHeight };
		p.points.rightBottom = { _center.x + halfWidth, _center.y - halfHeight };
		p.points.pivotPoint = _center; // pivot point is in the center by default

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);

		// == Scale, but only if the scale is not 1 ==
		if (!Utils::AreEqual(p.scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(p.scaleY, static_cast<Type>(1.f)))
			SetScale(p, Point<2, Type>{ p.scaleX, p.scaleY });
	}

	template<typename Type>
	const Point<2, Type>& GetCenter(const Polygon<4, Type>& p) noexcept
	{
		return p.points.center;
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

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
			SetRotation(p, p.angle);
	}

	template<typename Type>
	const Point<2, Type>& GetPivotPoint(const Polygon<4, Type>& p) noexcept
	{
		return p.points.pivotPoint;
	}

	template<typename Type>
	void SetWidth(Polygon<4, Type>& p, const Type _width) noexcept
	{
		Type originalAngle{};
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
		{
			originalAngle = p.angle;
			SetRotation(p, static_cast<Type>(0.f));
		}

		p.width = _width;

		const Point<2, Type>& center{ p.points.center };
		const Type halfWidth{ _width * static_cast<Type>(0.5f) };

		p.points.leftBottom.x = center.x - halfWidth;
		p.points.leftTop.x = center.x - halfWidth;
		p.points.rightTop.x = center.x + halfWidth;
		p.points.rightBottom.x = center.x + halfWidth;

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);

		// == Scale, but only if the scale is not 1 ==
		if (!Utils::AreEqual(p.scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(p.scaleY, static_cast<Type>(1.f)))
			SetScale(p, Point<2, Type>{ p.scaleX, p.scaleY });
	}

	template<typename Type>
	void SetHeight(Polygon<4, Type>& p, const Type _height) noexcept
	{
		Type originalAngle{};
		if (!Utils::AreEqual(p.angle, static_cast<Type>(0.f)))
		{
			originalAngle = p.angle;
			SetRotation(p, static_cast<Type>(0.f));
		}

		p.height = _height;

		const Point<2, Type>& center{ p.points.center };
		const Type halfHeight{ _height * static_cast<Type>(0.5f) };

		p.points.leftBottom.y = center.y - halfHeight;
		p.points.leftTop.y = center.y + halfHeight;
		p.points.rightTop.y = center.y + halfHeight;
		p.points.rightBottom.y = center.y - halfHeight;

		// == Rotate, but only if the angle is not 0 ==
		if (!Utils::AreEqual(originalAngle, static_cast<Type>(0.f)))
			SetRotation(p, originalAngle);

		// == Scale, but only if the scale is not 1 ==
		if (!Utils::AreEqual(p.scaleX, static_cast<Type>(1.f)) || !Utils::AreEqual(p.scaleY, static_cast<Type>(1.f)))
			SetScale(p, Point<2, Type>{ p.scaleX, p.scaleY });
	}
#pragma endregion
}