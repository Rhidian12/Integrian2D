#pragma once

#include <stdint.h>
#include <utility>
#include <algorithm>

#include "../Utils/Utils.h"

#ifdef max
#undef max
#endif

namespace Integrian2D
{
#pragma region Betteruint8_t
	struct Betteruint8_t
	{
		Betteruint8_t(const uint8_t _value)
			: v{ _value }
		{}

		uint8_t v;

		operator uint8_t()
		{
			return v;
		}
	};
	inline Betteruint8_t operator+(const Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v + b.v));
	}
	inline Betteruint8_t& operator+=(Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		static_cast<uint8_t>(a.v += b.v);
		return a;
	}
	inline Betteruint8_t operator+(const Betteruint8_t& a, const uint8_t b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v + b));
	}
	inline Betteruint8_t& operator+=(Betteruint8_t& a, const uint8_t b) noexcept
	{
		static_cast<uint8_t>(a.v += b);
		return a;
	}
	inline Betteruint8_t operator-(const Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v - b.v));
	}
	inline Betteruint8_t& operator-=(Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		static_cast<uint8_t>(a.v -= b.v);
		return a;
	}
	inline Betteruint8_t operator-(const Betteruint8_t& a, const uint8_t b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v - b));
	}
	inline Betteruint8_t& operator-=(Betteruint8_t& a, const uint8_t b) noexcept
	{
		static_cast<uint8_t>(a.v -= b);
		return a;
	}
	inline Betteruint8_t operator*(const Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v * b.v));
	}
	inline Betteruint8_t& operator*=(Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		static_cast<uint8_t>(a.v *= b.v);
		return a;
	}
	inline Betteruint8_t operator*(const Betteruint8_t& a, const uint8_t b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v * b));
	}
	inline Betteruint8_t& operator*=(Betteruint8_t& a, const uint8_t b) noexcept
	{
		static_cast<uint8_t>(a.v *= b);
		return a;
	}
	inline Betteruint8_t operator/(const Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v / b.v));
	}
	inline Betteruint8_t& operator/=(Betteruint8_t& a, const Betteruint8_t& b) noexcept
	{
		static_cast<uint8_t>(a.v /= b.v);
		return a;
	}
	inline Betteruint8_t operator/(const Betteruint8_t& a, const uint8_t b) noexcept
	{
		return Betteruint8_t(static_cast<uint8_t>(a.v / b));
	}
	inline Betteruint8_t& operator/=(Betteruint8_t& a, const uint8_t b) noexcept
	{
		static_cast<uint8_t>(a.v /= b);
		return a;
	}
#pragma endregion

	struct RGBColour final
	{
#pragma region Constructors
		RGBColour()
			: r{ 0 }
			, g{ 0 }
			, b{ 0 }
			, a{ 1 }
		{}
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
		union
		{
			Betteruint8_t data[4]; // r, g, b, a

#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
			struct
			{
				Betteruint8_t r, g, b, a; // uint8_t has a range of [0, 255]
			};
#pragma warning ( pop )
		};
#pragma endregion

#pragma region Member Functions
		uint8_t& operator[](uint8_t i)
		{
			Utils::Assert(i < sizeof(data) / sizeof(uint8_t), "Point<P, Type>::operator[] > Index is out of bounds!");
			return data[i].v;
		}

		const uint8_t& operator[](uint8_t i) const
		{
			Utils::Assert(i < sizeof(data) / sizeof(uint8_t), "Point<P, Type>::operator[] > Index is out of bounds!");
			return data[i].v;
		}
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

#pragma region RGBColour Functions
	inline void MaxToOne(RGBColour& colour) noexcept
	{
		uint8_t max{ std::max(colour.r.v, std::max(colour.g.v, colour.b.v)) };

		colour /= max;
	}
#pragma endregion
}