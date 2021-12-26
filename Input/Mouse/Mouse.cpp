#include "Mouse.h" // Header
#include "../../Command/Command.h"

#include <SDL.h>

namespace Integrian2D
{
	void Mouse::Activate(Scene* const pScene) noexcept
	{
		m_IsActive = true;

		for (CommandAndButton& commandButton : m_MouseCommands)
			if (commandButton.pCommand->GetScene() == pScene)
				commandButton.isActive = true;
	}

	void Mouse::Deactivate(Scene* const pScene) noexcept
	{
		ResetInputs();

		m_IsActive = false;

		for (CommandAndButton& commandButton : m_MouseCommands)
			if (commandButton.pCommand->GetScene() == pScene)
				commandButton.isActive = false;
	}

	Mouse* const Mouse::CreateMouse() noexcept
	{
		ASSERT(m_pInstance == nullptr, "Mouse::CreateMouse() > Mouse is default created by the Input Manager!");

		m_pInstance = new Mouse{};

		return m_pInstance;
	}

	void Mouse::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	Mouse::~Mouse()
	{
		m_MouseCommands.clear();
	}

	void Mouse::AddCommand(const MouseButton mouseButton, const State keyState, Command* const pCommand) noexcept
	{
		m_MouseCommands.push_back(CommandAndButton{ pCommand,keyState,GameInput{ mouseButton } });
	}

	void Mouse::ExecuteCommands() noexcept
	{
		if (!m_IsActive)
			return;

		for (CommandAndButton& commandButton : m_MouseCommands)
		{
			if (commandButton.isActive)
			{
				const State currentKeystate{ GetKeystate(commandButton.gameInput.mouseButton, commandButton.previousKeystate) };
				if (currentKeystate == commandButton.wantedKeystate)
					commandButton.pCommand->Execute();

				commandButton.previousKeystate = currentKeystate;
			}
		}
	}

	bool Mouse::IsPressed(const MouseButton gameInput) const noexcept
	{
		return static_cast<std::underlying_type_t<MouseButton>>(gameInput) == SDL_GetMouseState(NULL, NULL);
	}

	bool Mouse::WasPressed(const State previousState) const noexcept
	{
		return (previousState == State::OnPress || previousState == State::OnHeld);
	}

	State Mouse::GetKeystate(const MouseButton mouseButton, const State previousState) const noexcept
	{
		if (WasPressed(previousState))
		{
			if (IsPressed(mouseButton))
				return State::OnHeld;
			else
				return State::OnRelease;
		}

		if (IsPressed(mouseButton))
			return State::OnPress;

		return State::NotPressed;
	}

	const std::vector<CommandAndButton>& Mouse::GetCommands() const noexcept
	{
		return m_MouseCommands;
	}

	void Mouse::RemoveCommand(Command* const pCommand) noexcept
	{
		m_MouseCommands.erase(std::remove_if(m_MouseCommands.begin(), m_MouseCommands.end(), [pCommand](const CommandAndButton& c)
			{
				return pCommand == c.pCommand;
			}), m_MouseCommands.end());
	}

	void Mouse::RemoveAllCommands() noexcept
	{
		m_MouseCommands.clear();
	}

	void Mouse::ResetInputs() noexcept
	{
		for (CommandAndButton& commandButton : m_MouseCommands)
			commandButton.previousKeystate = State::NotPressed;
	}
}