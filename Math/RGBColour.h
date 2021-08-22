#pragma once

#include <stdint.h>
#include <utility>

#include "../Utils/Utils.h"

namespace Integrian2D
{
	struct RGBColour final
	{
#pragma region Constructors
		RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b)
			: r{ _r }
			, g{ _g }
			, b{ _b }
			, a{ 1 }
		{}
		RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a)
			: r{ _r }
			, g{ _g }
			, b{ _b }
			, a{ _a }
		{
			// r, g, b dont need a clamp since their natural range is [0, 255]
			Utils::Clamp(a, static_cast<uint8_t>(0), static_cast<uint8_t>(1));
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
		union
		{
			uint8_t data[4]; // r, g, b, a

#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
			struct
			{
				uint8_t r, g, b, a; // uint8_t has a range of [0, 255]
			};
#pragma warning ( pop )
		};
#pragma endregion

#pragma region Member Functions
		uint8_t& operator[](uint8_t i)
		{
			Utils::Assert(i < sizeof(data)/sizeof(uint8_t), "Point<P, Type>::operator[] > Index is out of bounds!");
			return data[i];
		}

		const uint8_t& operator[](uint8_t i) const
		{
			Utils::Assert(i < sizeof(data) / sizeof(uint8_t), "Point<P, Type>::operator[] > Index is out of bounds!");
			return data[i];
		}
#pragma endregion
	};

#pragma region Arithmetic Operators
	RGBColour operator+(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r + cTwo.r, cOne.b + cTwo.b, cOne.g + cTwo.g, cOne.a + cTwo.a };
	}

	RGBColour operator+(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r + inc, cOne.b + inc, cOne.g + inc, cOne.a + inc };
	}

	RGBColour operator-(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r - cTwo.r, cOne.b - cTwo.b, cOne.g - cTwo.g, cOne.a - cTwo.a };
	}

	RGBColour operator-(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r - inc, cOne.b - inc, cOne.g - inc, cOne.a - inc };
	}

	RGBColour operator*(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r * cTwo.r, cOne.b * cTwo.b, cOne.g * cTwo.g, cOne.a * cTwo.a };
	}

	RGBColour operator*(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r * inc, cOne.b * inc, cOne.g * inc, cOne.a * inc };
	}

	RGBColour operator/(const RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		return RGBColour{ cOne.r / cTwo.r, cOne.b / cTwo.b, cOne.g / cTwo.g, cOne.a / cTwo.a };
	}

	RGBColour operator/(const RGBColour& cOne, const uint8_t inc) noexcept
	{
		return RGBColour{ cOne.r / inc, cOne.b / inc, cOne.g / inc, cOne.a / inc };
	}
#pragma endregion

#pragma region Compound Arithmetic Operators
	RGBColour& operator+=(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r += cTwo.r;
		cOne.g += cTwo.g;
		cOne.b += cTwo.b;
		cOne.a += cTwo.a;

		return cOne;
	}

	RGBColour& operator+=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r += inc;
		cOne.g += inc;
		cOne.b += inc;
		cOne.a += inc;

		return cOne;
	}

	RGBColour& operator-=(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r -= cTwo.r;
		cOne.g -= cTwo.g;
		cOne.b -= cTwo.b;
		cOne.a -= cTwo.a;

		return cOne;
	}

	RGBColour& operator-=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r -= inc;
		cOne.g -= inc;
		cOne.b -= inc;
		cOne.a -= inc;

		return cOne;
	}

	RGBColour& operator*(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r *= cTwo.r;
		cOne.g *= cTwo.g;
		cOne.b *= cTwo.b;
		cOne.a *= cTwo.a;

		return cOne;
	}

	RGBColour& operator*=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r *= inc;
		cOne.g *= inc;
		cOne.b *= inc;
		cOne.a *= inc;

		return cOne;
	}

	RGBColour& operator/=(RGBColour& cOne, const RGBColour& cTwo) noexcept
	{
		cOne.r /= cTwo.r;
		cOne.g /= cTwo.g;
		cOne.b /= cTwo.b;
		cOne.a /= cTwo.a;

		return cOne;
	}

	RGBColour& operator/=(RGBColour& cOne, const uint8_t inc) noexcept
	{
		cOne.r /= inc;
		cOne.g /= inc;
		cOne.b /= inc;
		cOne.a /= inc;

		return cOne;
	}
#pragma endregion

#pragma RGBColour Functions
	void MaxToOne(RGBColour& colour) noexcept
	{
		uint8_t max{ std::max(colour.r, std::max(colour.g, colour.b)) };

		colour /= max;
	}
#pragma endregion
}