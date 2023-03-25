#pragma once

#include "../Integrian2D_API.h"
#include <stdint.h>
#include <utility>
#include <algorithm>
#include <string>

namespace Integrian2D::Math
{
	/* This class represents a RGB colour, note that the rgb components range from [0, 255] and the a component ranges from [0, 1] */

	struct INTEGRIAN2D_API RGBColour final
	{
	#pragma region Constructors

		RGBColour();
		RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b);
		RGBColour(const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a);

	#pragma endregion

	#pragma region Data

		uint8_t r, g, b, a;

	#pragma endregion
	};

	INTEGRIAN2D_API bool operator==(const RGBColour& c1, const RGBColour& c2);
	INTEGRIAN2D_API bool operator!=(const RGBColour& c1, const RGBColour& c2);

	INTEGRIAN2D_API RGBColour& MaxToOne(RGBColour& colour);

	namespace Colours
	{
		const static RGBColour White{ 255u, 255u, 255u };

		const static RGBColour Black{ 0u, 0u, 0u };
		const static RGBColour Grey{ 128u, 128u, 128u };

		const static RGBColour Red{ 255u, 0u, 0u };
		const static RGBColour DarkRed{ 139u, 0u, 0u };
		const static RGBColour LightRed{ 255u, 204u, 203u };
		const static RGBColour Crimson{ 220u, 20u, 60u };
		const static RGBColour Salmon{ 250u, 128u, 114u };

		const static RGBColour Green{ 0u, 255u, 0u };
		const static RGBColour DarkGreen{ 0u, 128u, 0u };
		const static RGBColour LightGreen{ 127u, 255u, 0u };
		const static RGBColour Olive{ 128u, 128u, 0u };
		const static RGBColour LightSeaGreen{ 32u, 128u, 0u };

		const static RGBColour Blue{ 0u, 0u, 255u };
		const static RGBColour LightBlue{ 0u, 191u, 255u };
		const static RGBColour DarkBlue{ 0u, 0u, 139u };
		const static RGBColour Cyan{ 0u, 255u, 255u };
		const static RGBColour Navy{ 0u, 0u, 128u };

		const static RGBColour Orange{ 255u, 165u, 0u };
		const static RGBColour DarkOrange{ 255u, 140u, 0u };

		const static RGBColour Purple{ 128u, 0u, 128u };
		const static RGBColour Indigo{ 75u, 0u, 130u };
		const static RGBColour Violet{ 238u, 130u, 238u };
		const static RGBColour DarkViolet{ 148u, 0u, 211u };
		const static RGBColour Fuchsia{ 255u, 0u, 255u };

		const static RGBColour Yellow{ 255u, 255u, 0u };
		const static RGBColour LightYellow{ 255u, 255u, 224u };
		const static RGBColour Khaki{ 240u, 230u, 140u };
		const static RGBColour DarkKhaki{ 189u, 183u, 107u };
		const static RGBColour Gold{ 212u, 175u, 55u };

		const static RGBColour Pink{ 255u, 192u, 203u };
		const static RGBColour LightPink{ 255u, 182u, 193u };
		const static RGBColour HotPink{ 255u, 105u, 180u };
		const static RGBColour DeepPink{ 255u, 20u, 147u };
	}
}