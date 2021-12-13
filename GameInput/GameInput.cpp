#include "GameInput.h"

namespace Integrian2D
{
	CommandAndButton::CommandAndButton(Command* const pCommand, const State wantedKeystate)
		: pCommand{ pCommand }
		, wantedKeystate{ wantedKeystate }
		, previousKeystate{ State::NotPressed }
	{
	}

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