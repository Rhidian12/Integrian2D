#pragma once

#include "../../GameInput/GameInput.h"

#include <string>

namespace Integrian2D
{
	struct InputAxis final
	{
		std::string axis{};
		GameInput positiveInput{ KeyboardInput::INVALID };
		GameInput negativeInput{ KeyboardInput::INVALID };
	};

	inline bool operator==(const InputAxis& a, const InputAxis& b) noexcept
	{
		return a.axis == b.axis && a.positiveInput == b.positiveInput && a.negativeInput == b.negativeInput;
	}

	inline bool operator!=(const InputAxis& a, const InputAxis& b) noexcept
	{
		return !(a == b);
	}
}