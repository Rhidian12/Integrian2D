#pragma once

#include "Vector.h"
#include "Point.h"
#include <iostream>
#include <utility>

namespace Integrian2D
{
	// == Vector3f ==
	template<typename Type>
	struct Vector<3, Type>
	{
#pragma region Constructors
		Vector<3, Type>()
			: x{}
			, y{}
			, z{}
		{}
		Vector<3, Type>(const Type _x, const Type _y)
			: x{ _x }
			, y{ _y }
			, z{}
		{}
		Vector<3, Type>(const Type _x, const Type _y, const Type _z)
			: x{ _x }
			, y{ _y }
			, z{ _z }
		{}
		Vector<3, Type>(const Vector<3, Type>& from, const Vector<3, Type>& to)
			: x{ to.x - from.x }
			, y{ to.y - from.y }
			, z{ to.z - from.z }
		{}
		Vector<3, Type>(const Vector<2, Type>& v)
			: x{ v.x }
			, y{ v.y }
			, z{}
		{}
#pragma endregion

#pragma region Rule Of 5
		Vector<3, Type>(const Vector<3, Type>& other) noexcept
			: x{ other.x }
			, y{ other.y }
			, z{ other.z }
		{}
		Vector<3, Type>(Vector<3, Type>&& other) noexcept
			: x{ std::move(other.x) }
			, y{ std::move(other.y) }
			, z{ std::move(other.z) }
		{}
		Vector<3, Type>& operator=(const Vector<3, Type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		Vector<3, Type>& operator=(Vector<3, Type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			z = std::move(other.z);
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
				Type x, y, z;
				Vector<2, Type> xy;
			};
#pragma warning ( pop )
		};
#pragma endregion
	};
}