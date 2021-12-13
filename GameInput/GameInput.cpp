#include "GameInput.h"

namespace Integrian2D
{
	CommandAndButton::CommandAndButton(Command* const pCommand, const State wantedKeystate, const GameInput gameInput, const bool _isActive)
		: pCommand{ pCommand }
		, wantedKeystate{ wantedKeystate }
		, previousKeystate{ State::NotPressed }
		, gameInput{ gameInput }
		, isActive{ _isActive }
	{}

	GameInput::GameInput(const ControllerInput controllerInput)
		: controllerInput{ controllerInput }
	{}

	GameInput::GameInput(const KeyboardInput keyboardInput)
		: keyboardInput{ keyboardInput }
	{}

	GameInput::GameInput(const MouseButton mouseButton)
		: mouseButton{ mouseButton }
	{}
}