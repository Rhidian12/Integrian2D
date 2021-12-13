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

		m_MousePosition = Point2f{ static_cast<float>(x), static_cast<float>(m_WindowHeight - y) };

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

		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i].ExecuteCommands();
	}

	void InputManager::AddCommand(const GameInput& gameInput, Command* const pCommand, const State keyState, const uint8_t controllerIndex) noexcept
	{
		if (gameInput.controllerInput != ControllerInput::INVALID)
			m_Controllers[controllerIndex].AddCommand(gameInput.controllerInput, keyState, pCommand);

		if (gameInput.mouseButton != MouseButton::INVALID)
			m_Mouse.AddCommand(gameInput.mouseButton, keyState, pCommand);

		if (gameInput.keyboardInput != KeyboardInput::INVALID)
			m_Keyboard.AddCommand(gameInput.keyboardInput, keyState, pCommand);
	}

	void InputManager::RemoveCommandFromInput(const GameInput& input, Command* const pCommand, const uint8_t controllerIndex) noexcept
	{
		if (input.mouseButton != MouseButton::INVALID)
			m_Mouse.RemoveCommand(pCommand);

		else if (input.keyboardInput != KeyboardInput::INVALID)
			m_Keyboard.RemoveCommand(pCommand);

		else
			m_Controllers[controllerIndex].RemoveCommand(pCommand);
	}

	void InputManager::RemoveCommand(Command* const pCommand, const uint8_t controllerIndex) noexcept
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

	void InputManager::AddAxis(const InputAxis& inputAxis) noexcept
	{
		if (std::find(m_Axis.cbegin(), m_Axis.cend(), inputAxis) == m_Axis.cend())
			m_Axis.push_back(inputAxis);
	}

	int8_t InputManager::GetAxis(const std::string& axisName, const uint8_t playerIndex)
	{
		const auto cIt{ std::find_if(m_Axis.cbegin(), m_Axis.cend(), [&axisName](const InputAxis& i)->bool
			{
				return i.axis == axisName;
			}) };

		ASSERT(cIt != m_Axis.cend(), "InputManager::GetAxis() > The provided axis name has not been added!");

		if (cIt != m_Axis.cend())
		{
			int8_t output{};

			/* first check all positive inputs */

			if (cIt->positiveInput.controllerInput != ControllerInput::INVALID)
				if (IsControllerButtonPressed(cIt->positiveInput.controllerInput, playerIndex))
					output += 1;

			if (cIt->positiveInput.keyboardInput != KeyboardInput::INVALID)
				if (IsKeyboardKeyPressed(cIt->positiveInput.keyboardInput))
					output += 1;

			if (cIt->positiveInput.mouseButton != MouseButton::INVALID)
				if (IsMouseButtonPressed(cIt->positiveInput.mouseButton))
					output += 1;

			/* then check all negative inputs */

			if (cIt->negativeInput.controllerInput != ControllerInput::INVALID)
				if (IsControllerButtonPressed(cIt->negativeInput.controllerInput, playerIndex))
					output -= 1;

			if (cIt->negativeInput.keyboardInput != KeyboardInput::INVALID)
				if (IsKeyboardKeyPressed(cIt->negativeInput.keyboardInput))
					output -= 1;

			if (cIt->negativeInput.mouseButton != MouseButton::INVALID)
				if (IsMouseButtonPressed(cIt->negativeInput.mouseButton))
					output -= 1;

			/* Clamp the final result to [-1, 1] */
			Utils::Clamp(output, static_cast<int8_t>(-1), static_cast <int8_t>(1));

			return output;
		}
		else
			return static_cast<int8_t>(0);
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

	const std::vector<CommandAndButton>& InputManager::GetKeyboardCommands() const noexcept
	{
		return m_Keyboard.GetCommands();
	}

	const std::vector<CommandAndButton>& InputManager::GetMouseCommands() const noexcept
	{
		return m_Mouse.GetCommands();
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

	void InputManager::Activate() noexcept
	{
		m_Keyboard.Activate();
		m_Mouse.Activate();
		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i].Activate();
	}

	void InputManager::Deactivate() noexcept
	{
		m_Keyboard.Deactivate();
		m_pMouse->Deactivate();
		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i].Deactivate();
	}

	InputManager::InputManager()
		: m_MousePosition{}
		, m_WindowWidth{}
		, m_WindowHeight{}
		, m_AmountOfControllers{ uint8_t(SDL_NumJoysticks()) }
		, m_Controllers{}
		, m_Keyboard{}
		, m_pMouse{ Mouse::CreateMouse() }
		, m_Axis{}
	{
		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i] = std::move(GameController{ uint8_t(i) });

		m_Keyboard = std::move(Keyboard{});
	}
}
