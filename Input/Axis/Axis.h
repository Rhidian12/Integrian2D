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
}