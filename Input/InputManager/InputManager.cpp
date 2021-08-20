#include "InputManager.h"
#include "../../Utils/Utils.h"

#include <SDL.h>

extern bool volatile g_IsLooping;

namespace Integrian2D
{
	void InputManager::HandleInput() noexcept
	{
		int x{}, y{};
		const Uint32 mouseState = SDL_GetMouseState(&x, &y);

		//m_MousePosition = Point2f{ float(x),float(m_WindowHeight - y) };

		m_AmountOfControllers = uint8_t(SDL_NumJoysticks()); // check if controllers have been added / removed

		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				g_IsLooping = false;
				break;
			default:
				break;
			}
		}

		m_Keyboard.ExecuteCommands();
		m_Mouse.ExecuteCommands();

		//SDL_GameControllerUpdate();
		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i].ExecuteCommands();
	}

	void InputManager::AddCommand(const GameInput& gameInput, const std::function<void()>& pCommand, const State keyState, const uint8_t controllerIndex) noexcept
	{
		if (gameInput.controllerInput != ControllerInput::INVALID)
			m_Controllers[controllerIndex].AddCommand(gameInput.controllerInput, keyState, pCommand);

		else if (gameInput.mouseButton != MouseButton::INVALID)
			m_Mouse.AddCommand(gameInput.mouseButton, keyState, pCommand);

		else /*if (gameInput.keyboardInput != KeyboardInput::INVALID)*/
			m_Keyboard.AddCommand(gameInput.keyboardInput, keyState, pCommand);
	}

	void InputManager::RemoveCommandFromInput(const GameInput& input, std::function<void()>& pCommand, const uint8_t controllerIndex) noexcept
	{
		if (input.mouseButton != MouseButton::INVALID)
			m_Mouse.RemoveCommand(pCommand);

		else if (input.keyboardInput != KeyboardInput::INVALID)
			m_Keyboard.RemoveCommand(pCommand);

		else
			m_Controllers[controllerIndex].RemoveCommand(pCommand);
	}

	void InputManager::RemoveCommand(const std::function<void()>& pCommand, const uint8_t controllerIndex) noexcept
	{
		m_Mouse.RemoveCommand(pCommand);
		m_Keyboard.RemoveCommand(pCommand);
		m_Controllers[controllerIndex].RemoveCommand(pCommand);
	}

	void InputManager::RemoveAllCommands() noexcept
	{
		for (uint8_t i{}; i < 4; ++i)
			m_Controllers[i].m_pCommands.clear();

		m_Keyboard.m_KeyboardCommands.clear();

		m_Mouse.m_MouseCommands.clear();
	}

	bool InputManager::IsKeyboardKeyPressed(const KeyboardInput gameInput) const noexcept
	{
		return m_Keyboard.IsPressed(gameInput);
	}

	bool InputManager::IsControllerButtonPressed(const ControllerInput gameInput, const uint8_t playerIndex) const noexcept
	{
		return m_Controllers[playerIndex].IsPressed(gameInput);
	}

	bool InputManager::IsMouseButtonPressed(const MouseButton gameInput) const noexcept
	{
		return m_Mouse.IsPressed(gameInput);
	}

	const KeyboardInput InputManager::GetWhichKeyIsPressed() const noexcept
	{
		return m_Keyboard.GetWhichKeyIsPressed();

	}

	const Point2f& InputManager::GetMousePosition() const noexcept
	{
		return m_MousePosition;
	}

	double InputManager::GetJoystickMovement(const ControllerInput axis, const uint8_t playerIndex) const noexcept
	{
		return m_Controllers[playerIndex].GetJoystickMovement(axis);
	}

	double InputManager::GetTriggerMovement(const ControllerInput axis, const uint8_t playerIndex) const noexcept
	{
		return m_Controllers[playerIndex].GetTriggerMovement(axis);
	}

	const std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>& InputManager::GetKeyboardCommands() const noexcept
	{
		return m_Keyboard.m_KeyboardCommands;
	}

	const std::unordered_map<MouseButton, std::vector<CommandAndButton>>& InputManager::GetMouseCommands() const noexcept
	{
		return m_Mouse.m_MouseCommands;
	}

	const std::unordered_map<ControllerInput, std::vector<CommandAndButton>>& InputManager::GetControllerCommands(const uint8_t index) const noexcept
	{
		return m_Controllers[index].m_pCommands;
	}

	void InputManager::ResetInputs() noexcept
	{
		m_Keyboard.ResetInputs();
		m_Mouse.ResetInputs();
		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i].ResetInputs();
	}

	InputManager::InputManager()
		: m_MousePosition{}
		, m_WindowWidth{}
		, m_WindowHeight{}
		, m_AmountOfControllers{ uint8_t(SDL_NumJoysticks()) }
		, m_Controllers{}
		, m_Keyboard{}
		, m_Mouse{}
	{
		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i] = std::move(GameController{ uint8_t(i) });

		m_Keyboard = std::move(Keyboard{});

		m_Mouse = std::move(Mouse{});
	}
}
