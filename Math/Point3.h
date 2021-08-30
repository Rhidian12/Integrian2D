#pragma once

#include "Point.h" // Point

#include <utility>

namespace Integrian2D
{
	// == Point3 (Point Specialisation) == 
	template<typename Type>
	struct Point<3, Type>
	{
#pragma region Constructors
		Point<3, Type>()
			: x{}
			, y{}
			, z{}
		{}
		Point<3, Type>(const Type _x, const Type _y)
			: x{ _x }
			, y{ _y }
			, z{}
		{}
		Point<3, Type>(const Type _x, const Type _y, const Type _z)
			: x{ _x }
			, y{ _y }
			, z{ _z }
		{}
		Point<3, Type>(const Point<2, Type> _xy)
			: x{ _xy.x }
			, y{ _xy.y }
			, z{}
		{}
#pragma endregion

#pragma region Rule Of 5
		Point<3, Type>(const Point<3, Type>& other) noexcept
			: x{ other.x }
			, y{ other.y }
			, z{ other.z }
		{}
		Point<3, Type>(Point<3, Type>&& other) noexcept
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
			, z{ std::move(other.z) }
		{}
		Point<3, Type>& operator=(const Point<3, Type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			z = other.y;

			return *this;
		}
		Point<3, Type>& operator=(const Point<3, Type>& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			z = std::move(other.y);

			return *this;
		}
#pragma endregion

#pragma region Data
		union
		{
			Type data[3];

#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
			struct
			{
				Point<2, Type> xy;
				Type x, y, z;
			};
#pragma warning ( pop )
		};
#pragma endregion
	};

#pragma region Arithmetic Operators

#pragma endregion
}