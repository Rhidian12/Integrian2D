#include "RGBColour.h"

namespace Integrian2D::Math
{
	RGBColour::RGBColour()
		: RGBColour{ 0,0,0,1 }
	{}
	RGBColour::RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b)
		: RGBColour{ _r,_g,_b,1 }
	{}
	RGBColour::RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a)
		: r{ _r }
		, g{ _g }
		, b{ _b }
		, a{ _a }
	{}

	bool operator==(const RGBColour& c1, const RGBColour& c2)
	{
		return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
	}

	bool operator!=(const RGBColour& c1, const RGBColour& c2)
	{
		return !(c1 == c2);
	}

	RGBColour& MaxToOne(RGBColour& colour)
	{
		const uint8_t max{ std::max(colour.r, std::max(colour.g, colour.b)) };

		colour.r /= max;
		colour.g /= max;
		colour.b /= max;

		return colour;
	}
}