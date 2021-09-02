#pragma once

#include "../Utils/Utils.h"
#include "Point2.h"

#include <utility>

namespace Integrian2D
{
	template<typename Type>
	struct Rect
	{
#pragma region Constructors
		Rect()
			: leftBottom{}
			, leftTop{}
			, rightTop{}
			, rightBottom{}
			, width{}
			, height{}
		{}
		Rect(const Type _x, const Type _y, const Type _width, const Type _height)
			: leftBottom{ _x, _y }
			, leftTop{ _x, _y + _height }
			, rightTop{ _x + _width, _y + _height }
			, rightBottom{ _x + _width, _y }
			, width{ _width }
			, height{ _height }
		{}
		Rect(const Point<2, Type> _xy, const Type _width, const Type _height)
			: leftBottom{ _xy }
			, leftTop{ _xy.x, _xy.y + _height }
			, rightTop{ _xy.x + _width, _xy.y + _height }
			, rightBottom{ _xy.x + _width, _xy }
			, width{ _width }
			, height{ _height }
		{}
#pragma endregion

#pragma region Rule of 5
		Rect(const Rect& other) noexcept
			: leftBottom{ other.leftBottom }
			, leftTop{ other.leftTop }
			, rightTop{ other.rightTop }
			, rightBottom{ other.rightBottom }
			, width{ other.width }
			, height{ other.height }
		{}
		Rect(Rect&& other) noexcept
			: leftBottom{ std::move(other.leftBottom) }
			, leftTop{ std::move(other.leftTop) }
			, rightTop{ std::move(other.rightTop) }
			, rightBottom{ std::move(other.rightBottom) }
			, width{ std::move(other.width) }
			, height{ std::move(other.height) }
		{}
		Rect& operator=(const Rect& other) noexcept
		{
			leftBottom = other.leftBottom;
			leftTop = other.leftTop;
			rightTop = other.rightTop;
			rightBottom = other.rightBottom;
			width = other.width;
			height = other.height;

			return *this;
		}
		Rect& operator=(Rect&& other) noexcept
		{
			leftBottom = std::move(other.leftBottom);
			leftTop = std::move(other.leftTop);
			rightTop = std::move(other.rightTop);
			rightBottom = std::move(other.rightBottom);
			width = std::move(other.width);
			height = std::move(other.height);

			return *this;
		}
#pragma endregion

#pragma region Data
		union
		{
			// data[0] == leftBottom
			// data[1] == leftTop
			// data[2] == rightTop
			// data[3] == rightBottom
			// data[4] == width, height
			Point<2, Type> data[5];

#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
			struct
			{
				Point<2, Type> leftBottom;
				float width, height;
			
			private:
				Point<2, Type> leftTop, rightTop, rightBottom
			};
#pragma warning ( pop )
		};
#pragma endregion

#pragma region Member Operators
		Point<2, Type>& operator[](uint8_t i)
		{
			Utils::Assert(i < sizeof(data) / sizeof(Type), "Rect<Type>::operator[] > Index is out of bounds!");
			return data[i];
		}

		const Point<2, Type>& operator[](uint8_t i) const
		{
			Utils::Assert(i < sizeof(data) / sizeof(Type), "Rect<Type>::operator[] > Index is out of bounds!");
			return data[i];
		}
#pragma endregion
	};

	template<typename Type>
	bool operator==(const Rect<Type>& r1, const Rect<Type>& r2) noexcept
	{
		return (r1.leftBottom == r2.leftBottom) && (r1.leftTop == r2.leftTop) &&
			(r1.rightTop == r2.rightTop) && (r1.rightBottom == r2.rightBottom) &&
			Utils::AreEqual(r1.width, r2.width) && Utils::AreEqual(r1.height, r2.height);
	}

	template<typename Type>
	bool operator!=(const Rect<Type>& r1, const Rect<Type>& r2) noexcept
	{
		return !(r1 == r2);
	}
}