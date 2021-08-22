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
			: x{}
			, y{}
			, width{}
			, height{}
		{}
		Rect(const Type _x, const Type _y, const Type _width, const Type _height)
			: x{ _x }
			, y{ _y }
			, width{ _width }
			, height{ _height }
		{}
		Rect(const Point<2, Type> _xy, const Type _width, const Type _height)
			: xy{ _xy }
			, width{ _width }
			, height{ _height }
		{}
#pragma endregion

#pragma region Rule of 5
		Rect(const Rect& other) noexcept
			: x{ other.x }
			, y{ other.y }
			, width{ other.width }
			, height{ other.height }
		{}
		Rect(Rect&& other) noexcept
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
			, width{ std::moveother.width) }
			, height{ std::moveother.height) }
		{}
		Rect& operator=(const Rect& other) noexcept
		{
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;

			return *this;
		}
		Rect& operator=(Rect&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			width = std::move(other.width);
			height = std::move(other.height);

			return *this;
		}
#pragma endregion

#pragma region Data
		union
		{
			// data[0] == x
			// data[1] == y
			// data[2] == width
			// data[3] == height
			Type data[4];

#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
			struct
			{
				float x, y, width, height;
				Point<2, Type> xy;
			};
#pragma warning ( pop )
		};
#pragma endregion

#pragma region Member Operators
		Type& operator[](uint8_t i)
		{
			Utils::Assert(i < sizeof(data) / sizeof(Type), "Rect<Type>::operator[] > Index is out of bounds!");
			return data[i];
		}

		const Type& operator[](uint8_t i) const
		{
			Utils::Assert(i < sizeof(data) / sizeof(Type), "Rect<Type>::operator[] > Index is out of bounds!");
			return data[i];
		}
#pragma endregion
	};

	template<typename Type>
	bool operator==(const Rect<Type>& r1, const Rect<Type>& r2) noexcept
	{
		return (r1.xy == r2.xy) && Utils::AreEqual(r1.width, r2.width) && Utils::AreEqual(r1.height, r2.height);
	}

	template<typename Type>
	bool operator!=(const Rect<Type>& r1, const Rect<Type>& r2) noexcept
	{
		return !(r1 == r2);
	}
}