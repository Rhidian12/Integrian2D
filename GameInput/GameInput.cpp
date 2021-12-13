#include "GameInput.h"

namespace Integrian2D
{
	CommandAndButton::CommandAndButton(Command* const pCommand, const State wantedKeystate, const GameInput gameInput)
		: pCommand{ pCommand }
		, wantedKeystate{ wantedKeystate }
		, previousKeystate{ State::NotPressed }
		, gameInput{ gameInput }
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