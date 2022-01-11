#pragma once

#include "../Integrian2D_API.h"
#include <stdint.h>
#include <utility>
#include <algorithm>
#include <string>

#include "../Utils/Utils.h"
#include "BetterUint8.h"

#ifdef max /* This macro was destroying the entire file */
#undef max
#endif

namespace Integrian2D
{
	/* This class represents a RGB colour, note that the rgb components range from [0, 255] and the a component ranges from [0, 1] */

	/* A list of available operators:

	   RGBColour operator+(const RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour operator+(const RGBColour& cOne, const uint8_t inc)

	   RGBColour operator-(const RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour operator-(const RGBColour& cOne, const uint8_t inc)

	   RGBColour operator*(const RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour operator*(const RGBColour& cOne, const uint8_t inc)

	   RGBColour operator/(const RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour operator/(const RGBColour& cOne, const uint8_t inc)

	   RGBColour& operator+=(RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour& operator+=(RGBColour& cOne, const uint8_t inc)

	   RGBColour& operator-=(RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour& operator-=(RGBColour& cOne, const uint8_t inc)

	   RGBColour& operator*=(RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour& operator*=(RGBColour& cOne, const uint8_t inc)

	   RGBColour& operator/=(RGBColour& cOne, const RGBColour& cTwo)
	   RGBColour& operator/=(RGBColour& cOne, const uint8_t inc)
	   */

	   /* A list of available functions:

		 void MaxToOne(RGBColour& colour)
		 =>		Finds the maximum value of the rgb components, then divides every component by that max value
		 =>		This function essentially normalizes the colour

		 std::string ToString(const RGBColour&)
		 =>		Returns the rgba values of the provided colour in a CSV manner
		*/

	struct INTEGRIAN2D_API RGBColour final
	{
#pragma region Constructors
		explicit RGBColour()
			: RGBColour{ 0,0,0,1 }
		{}
		explicit RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b)
			: RGBColour{ _r,_g,_b,1 }
		{}
		explicit RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a)
			: r{ _r }
			, g{ _g }
			, b{ _b }
			, a{ _a }
		{
			// r, g, b dont need a clamp since their natural range is [0, 255]
			Utils::Clamp(a.v, static_cast<uint8_t>(0), static_cast<uint8_t>(1));
		}
#pragma endregion

#pragma region Rule of 5
		RGBColour(const RGBColour& other) noexcept
			: r{ other.r }
			, g{ other.g }
			, b{ other.b }
			, a{ other.a }
		{}
		RGBColour(RGBColour&& other) noexcept
			: r{ std::move(other.r) }
			, g{ std::move(other.g) }
			, b{ std::move(other.b) }
			, a{ std::move(other.a) }
		{}
		RGBColour& operator=(const RGBColour& other) noexcept
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;

			return *this;
		}
		RGBColour& operator=(RGBColour&& other) noexcept
		{
			r = std::move(other.r);
			g = std::move(other.g);
			b = std::move(other.b);
			a = std::move(other.a);

			return *this;
		}
#pragma endregion

#pragma region Data
		Betteruint8_t r, g, b, a; // uint8_t has a range of [0, 255]
#pragma endregion
	};

#pragma region Arithmetic Operators
	inline RGBColour operator+(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r + cTwo.r, cOne.b + cTwo.b, cOne.g + cTwo.g, cOne.a + cTwo.a };
	}

	inline RGBColour operator+(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r + inc, cOne.b + inc, cOne.g + inc, cOne.a + inc };
	}

	inline RGBColour operator-(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r - cTwo.r, cOne.b - cTwo.b, cOne.g - cTwo.g, cOne.a - cTwo.a };
	}

	inline RGBColour operator-(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r - inc, cOne.b - inc, cOne.g - inc, cOne.a - inc };
	}

	inline RGBColour operator*(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r * cTwo.r, cOne.b * cTwo.b, cOne.g * cTwo.g, cOne.a * cTwo.a };
	}

	inline RGBColour operator*(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r * inc, cOne.b * inc, cOne.g * inc, cOne.a * inc };
	}

	inline RGBColour operator/(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r / cTwo.r, cOne.b / cTwo.b, cOne.g / cTwo.g, cOne.a / cTwo.a };
	}

	inline RGBColour operator/(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r / inc, cOne.b / inc, cOne.g / inc, cOne.a / inc };
	}
#pragma endregion

#pragma region Compound Arithmetic Operators
	inline RGBColour& operator+=(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r += cTwo.r;
		cOne.g += cTwo.g;
		cOne.b += cTwo.b;
		cOne.a += cTwo.a;

		return cOne;
	}

	inline RGBColour& operator+=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r += inc;
		cOne.g += inc;
		cOne.b += inc;
		cOne.a += inc;

		return cOne;
	}

	inline RGBColour& operator-=(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r -= cTwo.r;
		cOne.g -= cTwo.g;
		cOne.b -= cTwo.b;
		cOne.a -= cTwo.a;

		return cOne;
	}

	inline RGBColour& operator-=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r -= inc;
		cOne.g -= inc;
		cOne.b -= inc;
		cOne.a -= inc;

		return cOne;
	}

	inline RGBColour& operator*(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r *= cTwo.r;
		cOne.g *= cTwo.g;
		cOne.b *= cTwo.b;
		cOne.a *= cTwo.a;

		return cOne;
	}

	inline RGBColour& operator*=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r *= inc;
		cOne.g *= inc;
		cOne.b *= inc;
		cOne.a *= inc;

		return cOne;
	}

	inline RGBColour& operator/=(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r /= cTwo.r;
		cOne.g /= cTwo.g;
		cOne.b /= cTwo.b;
		cOne.a /= cTwo.a;

		return cOne;
	}

	inline RGBColour& operator/=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r /= inc;
		cOne.g /= inc;
		cOne.b /= inc;
		cOne.a /= inc;

		return cOne;
	}
#pragma endregion

#pragma region Relational Operators
	inline bool operator==(const RGBColour& c1, const RGBColour& c2) noexcept
	{
		return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
	}

	inline bool operator!=(const RGBColour& c1, const RGBColour& c2) noexcept
	{
		return !(c1 == c2);
	}
#pragma endregion

#pragma region Miscellaneous Operators
	inline std::ostream& operator<<(std::ostream& os, const RGBColour& c) noexcept
	{
		return os << c.r << ", " << c.g << ", " << c.b << ", " << c.a << std::endl;
	}
#pragma endregion

#pragma region RGBColour Functions
	inline void MaxToOne(RGBColour& colour) noexcept
	{
		const uint8_t max{ std::max(colour.r.v, std::max(colour.g.v, colour.b.v)) };

		colour /= max;
	}

	inline std::string ToString(const RGBColour& colour) noexcept
	{
		return std::to_string(colour.r.v) + ", " + std::to_string(colour.g.v) + ", " + std::to_string(colour.b.v) + ", " + std::to_string(colour.a.v);
	}
#pragma endregion
}