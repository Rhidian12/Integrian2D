#include "InputManager.h"
#include "../../Utils/Utils.h"
#include "../Mouse/Mouse.h"
#include "../Keyboard/Keyboard.h"
#include "../GameController/GameController.h"
#include "../../Command/Command.h"
#include "../../Core/Core.h"

#include <SDL.h>

extern inline bool volatile g_IsLooping;

namespace Integrian2D
{
	InputManager::~InputManager()
	{
		m_pKeyboard->Cleanup();
		m_pMouse->Cleanup();

		for (uint8_t i{}; i < m_MaxAmountOfControllers; ++i)
			m_pControllers[i]->Cleanup(i);

		for (Command* pCommand : m_pCommands)
			Utils::SafeDelete(pCommand);
	}

	InputManager* const InputManager::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new InputManager{};

		return m_pInstance;
	}

	void InputManager::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	void InputManager::HandleInput() noexcept
	{
		int x{}, y{};
		SDL_GetMouseState(&x, &y);

		m_MousePosition = Point2f{ static_cast<float>(x), static_cast<float>(m_WindowHeight) - static_cast<float>(y) };

		std::cout << m_MousePosition << std::endl;

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

		m_pKeyboard->ExecuteCommands();
		m_pMouse->ExecuteCommands();

		for (uint8_t i{}; i < m_AmountOfControllers; ++i)
			m_pControllers[i]->ExecuteCommands(i);
	}

	void InputManager::AddCommand(const GameInput& gameInput, Command* const pCommand, const State keyState, const uint8_t controllerIndex) noexcept
	{
		if (gameInput.controllerInput != ControllerInput::INVALID)
			m_pControllers[controllerIndex]->AddCommand(gameInput.controllerInput, keyState, pCommand);

		if (gameInput.mouseButton != MouseButton::INVALID)
			m_pMouse->AddCommand(gameInput.mouseButton, keyState, pCommand);

		if (gameInput.keyboardInput != KeyboardInput::INVALID)
			m_pKeyboard->AddCommand(gameInput.keyboardInput, keyState, pCommand);

		if (std::find(m_pCommands.cbegin(), m_pCommands.cend(), pCommand) == m_pCommands.cend())
			m_pCommands.push_back(pCommand);
	}

	void InputManager::RemoveCommand(Command* const pCommand, const uint8_t controllerIndex) noexcept
	{
		m_pMouse->RemoveCommand(pCommand);
		m_pKeyboard->RemoveCommand(pCommand);
		m_pControllers[controllerIndex]->RemoveCommand(pCommand);
	}

	void InputManager::RemoveAllCommands() noexcept
	{
		for (uint8_t i{}; i < 4; ++i)
			m_pControllers[i]->RemoveAllCommands();

		m_pKeyboard->RemoveAllCommands();

		m_pMouse->RemoveAllCommands();
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
		return m_pKeyboard->IsPressed(gameInput);
	}

	bool InputManager::IsControllerButtonPressed(const ControllerInput gameInput, const uint8_t playerIndex) const noexcept
	{
		return m_pControllers[playerIndex]->IsPressed(gameInput, playerIndex);
	}

	bool InputManager::IsMouseButtonPressed(const MouseButton gameInput) const noexcept
	{
		return m_pMouse->IsPressed(gameInput);
	}

	const KeyboardInput InputManager::GetWhichKeyIsPressed() const noexcept
	{
		return m_pKeyboard->GetWhichKeyIsPressed();
	}

	const Point2f& InputManager::GetMousePosition() const noexcept
	{
		return m_MousePosition;
	}

	double InputManager::GetJoystickMovement(const ControllerInput axis, const uint8_t playerIndex) const noexcept
	{
		return m_pControllers[playerIndex]->GetJoystickMovement(axis, playerIndex);
	}

	double InputManager::GetTriggerMovement(const ControllerInput axis, const uint8_t playerIndex) const noexcept
	{
		return m_pControllers[playerIndex]->GetTriggerMovement(axis, playerIndex);
	}

	const std::vector<CommandAndButton>& InputManager::GetKeyboardCommands() const noexcept
	{
		return m_pKeyboard->GetCommands();
	}

	const std::vector<CommandAndButton>& InputManager::GetMouseCommands() const noexcept
	{
		return m_pMouse->GetCommands();
	}

	const std::vector<CommandAndButton>& InputManager::GetControllerCommands(const uint8_t index) const noexcept
	{
		return m_pControllers[index]->GetCommands();
	}

	void InputManager::ResetInputs() noexcept
	{
		m_pKeyboard->ResetInputs();
		m_pMouse->ResetInputs();
		for (uint8_t i{}; i < m_AmountOfControllers; ++i)
			m_pControllers[i]->ResetInputs();
	}

	void InputManager::Activate(Scene* const pScene) noexcept
	{
		m_pKeyboard->Activate(pScene);
		m_pMouse->Activate(pScene);
		for (uint8_t i{}; i < m_AmountOfControllers; ++i)
			m_pControllers[i]->Activate(pScene, i);
	}

	void InputManager::Deactivate(Scene* const pScene) noexcept
	{
		m_pKeyboard->Deactivate(pScene);
		m_pMouse->Deactivate(pScene);
		for (uint8_t i{}; i < m_AmountOfControllers; ++i)
			m_pControllers[i]->Deactivate(pScene, i);
	}

	InputManager::InputManager()
		: m_MousePosition{}
		, m_WindowWidth{}
		, m_WindowHeight{}
		, m_AmountOfControllers{ uint8_t(SDL_NumJoysticks()) }
		, m_pControllers{}
		, m_pKeyboard{ Keyboard::CreateKeyboard() }
		, m_pMouse{ Mouse::CreateMouse() }
		, m_Axis{}
		, m_pCommands{}
	{
		for (uint8_t i{}; i < m_AmountOfControllers; ++i)
			m_pControllers[i] = GameController::CreateGameController(i);

		ASSERT(Core::GetInstance() != nullptr, "InputManager::InputManager() > First create the Core before calling the InputManager!");

		m_WindowWidth = Core::GetInstance()->GetWindowWidth();
		m_WindowHeight = Core::GetInstance()->GetWindowHeight();
	}
}
