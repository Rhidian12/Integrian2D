#include "GameController.h" // header
#include "../../Logger/Logger.h" // Logger
#include "../../Utils/Utils.h"
#include "../../Command/Command.h"

namespace Integrian2D
{
	GameController::GameController(const uint8_t index)
		: m_Commands{}
	{
		if (SDL_IsGameController(index))
		{
			m_pSDLGameControllers[index] = SDL_GameControllerOpen(index);

			if (!m_pSDLGameControllers[index])
				Logger::LogError("Error in controller: " + std::to_string(index) + "\n" + SDL_GetError());
		}
	}

	void GameController::Activate(const uint8_t index) noexcept
	{
		if (SDL_IsGameController(index))
		{
			m_pSDLGameControllers[index] = SDL_GameControllerOpen(index);

			if (!m_pSDLGameControllers[index])
				Logger::LogError("Error in controller: " + std::to_string(index) + "\n" + SDL_GetError());
		}
	}

	void GameController::Deactivate(const uint8_t index) noexcept
	{
		if (m_pSDLGameControllers[index])
		{
			SDL_GameControllerClose(m_pSDLGameControllers[index]);
			m_pSDLGameControllers[index] = nullptr;
		}
	}

	GameController* GameController::CreateGameController(const uint8_t index) noexcept
	{
		ASSERT(m_pInstances[index] == nullptr, "GameController::CreateGameController() > Input Manager default creates controllers!");
		return m_pInstances[index] = new GameController{ index };
	}

	void GameController::Cleanup(const uint8_t index) noexcept
	{
		Utils::SafeDelete(m_pInstances[index]);
	}

	GameController::~GameController()
	{
		for (int i{}; i < m_MaxAmountOfJoysticks; ++i)
		{
			if (m_pSDLGameControllers[i])
			{
				SDL_GameControllerClose(m_pSDLGameControllers[i]);
				m_pSDLGameControllers[i] = nullptr;
			}
		}

		m_Commands.clear();
	}

	void GameController::AddCommand(const ControllerInput controllerInput, const State keyState, Command* const pCommand) noexcept
	{
		m_Commands.push_back(CommandAndButton{ pCommand,keyState,GameInput{ controllerInput } });
	}

	void GameController::ExecuteCommands(const uint8_t index) noexcept
	{
		for (CommandAndButton& commandButton : m_Commands)
		{
			const State currentKeystate{ GetKeystate(commandButton.gameInput.controllerInput, commandButton.previousKeystate, index) };
			if (currentKeystate == commandButton.wantedKeystate)
				commandButton.pCommand->Execute();

			commandButton.previousKeystate = currentKeystate;
		}
	}

	bool GameController::IsPressed(const ControllerInput controllerInput, const uint8_t index) const noexcept
	{
		if (controllerInput == ControllerInput::LeftTrigger)
			return (SDL_GameControllerGetAxis(m_pSDLGameControllers[index], SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 0);

		if (controllerInput == ControllerInput::RightTrigger)
			return (SDL_GameControllerGetAxis(m_pSDLGameControllers[index], SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0);

		else
			return (SDL_GameControllerGetButton(m_pSDLGameControllers[index], static_cast<SDL_GameControllerButton>(controllerInput)) > 0);
	}

	bool GameController::WasPressed(const State previousState) const noexcept
	{
		return (previousState == State::OnPress || previousState == State::OnHeld);
	}

	State GameController::GetKeystate(const ControllerInput controllerInput, const State previousState, const uint8_t index) const noexcept
	{
		if (WasPressed(previousState))
		{
			if (IsPressed(controllerInput, index))
				return State::OnHeld;

			else
				return State::OnRelease;
		}

		if (IsPressed(controllerInput, index))
			return State::OnPress;

		return State::NotPressed;
	}

	double GameController::GetJoystickMovement(const ControllerInput axis, const uint8_t index) const noexcept
	{
		if (axis != ControllerInput::JoystickLeftHorizontalAxis && axis != ControllerInput::JoystickLeftVerticalAxis)
		{
			if (axis != ControllerInput::JoystickRightHorizontalAxis && axis != ControllerInput::JoystickRightVerticalAxis)
			{
				Logger::LogWarning("GetJoystickMovement() was called with a wrong parameter!\n");
				return 0.0;
			}
		}

		double movement{ static_cast<double>(SDL_GameControllerGetAxis(m_pSDLGameControllers[index], static_cast<SDL_GameControllerAxis>(axis)) / m_MaxJoystickValue) };
		Utils::Clamp(movement, -1.0, 1.0); // map to [-1, 1]
		return movement;
	}

	double GameController::GetTriggerMovement(const ControllerInput axis, const uint8_t index) const noexcept
	{
		if (axis != ControllerInput::LeftTrigger && axis != ControllerInput::RightTrigger)
		{
			Logger::LogWarning("GetTriggerMovement() was called with the wrong parameter!\n");
			return 0.0;
		}

		double movement{ static_cast<double>(SDL_GameControllerGetAxis(m_pSDLGameControllers[index], static_cast<SDL_GameControllerAxis>(axis)) / m_MaxJoystickValue) };
		Utils::Clamp(movement, 0.0, 1.0); // map to [-1, 1]
		return movement;
	}

	const std::vector<CommandAndButton>& GameController::GetCommands() const noexcept
	{
		return m_Commands;
	}

	void GameController::RemoveCommand(Command* const pCommand) noexcept
	{
		m_Commands.erase(std::remove_if(m_Commands.begin(), m_Commands.end(), [pCommand](const CommandAndButton& c)
			{
				return pCommand == c.pCommand;
			}), m_Commands.end());
	}

	void GameController::RemoveAllCommands() noexcept
	{
		m_Commands.clear();
	}

	void GameController::ResetInputs() noexcept
	{
		for (CommandAndButton& commandAndButton : m_Commands)
			commandAndButton.previousKeystate = State::NotPressed;
	}
}