#pragma once

#include <functional>
#include "PossibleInputs.h"
#include "../Utils/Utils.h"

namespace Integrian2D
{
	enum class State
	{
		OnHeld = 1,
		OnRelease = 2,
		OnPress = 3,

		NotPressed = 0 // internal usage
	};

	class Command;

	/* Interal Usage */
	struct CommandAndButton final
	{
		CommandAndButton(Command* const pCommand, const State wantedKeystate)
			: pCommand{ pCommand }
			, wantedKeystate{ wantedKeystate }
			, previousKeystate{ State::NotPressed }
		{
		}

		Command* pCommand;
		State wantedKeystate;
		State previousKeystate;
	};

	/* Used by the InputManager to represent user input, either controller, mouse or keyboard input*/
	struct GameInput final
	{
		explicit GameInput(const ControllerInput controllerInput)
			: controllerInput{ controllerInput }
		{
		}
		explicit GameInput(const KeyboardInput keyboardInput)
			: keyboardInput{ keyboardInput }
		{
		}
		explicit GameInput(const MouseButton mouseButton)
			: mouseButton{ mouseButton }
		{
		}

		ControllerInput controllerInput{ ControllerInput::INVALID };
		KeyboardInput keyboardInput{ KeyboardInput::INVALID };
		MouseButton mouseButton{ MouseButton::INVALID };

		/* Internal Usage, TODO: Look into this? Is it actually being used? */
		uint64_t id{ Utils::RandomNumber(uint64_t(0), std::numeric_limits<uint64_t>::max()) };
	};

	inline bool operator==(const GameInput& a, const GameInput& b) noexcept
	{
		return a.id == b.id;
	}

	inline bool operator!=(const GameInput& a, const GameInput& b) noexcept
	{
		return a.id != b.id;
	}
}
