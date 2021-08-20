#include "Mouse.h" // Header

namespace Integrian2D
{
	Mouse::Mouse(Mouse&& other) noexcept
	{
		m_MouseCommands = other.m_MouseCommands;
		other.m_MouseCommands.clear();
	}

	Mouse& Mouse::operator=(Mouse&& other) noexcept
	{
		m_MouseCommands = other.m_MouseCommands;
		other.m_MouseCommands.clear();

		return *this;
	}

	Mouse::~Mouse()
	{
		m_MouseCommands.clear();
	}

	void Mouse::AddCommand(const MouseButton mouseButton, const State keyState, const std::function<void()>& pCommand) noexcept
	{
		m_MouseCommands[mouseButton].push_back(CommandAndButton{ pCommand,keyState });
	}

	void Mouse::ExecuteCommands() noexcept
	{
		for (std::pair<const MouseButton, std::vector<CommandAndButton>>& commandPair : m_MouseCommands)
		{
			for (CommandAndButton& commandAndButton : commandPair.second)
			{
				const State currentKeystate{ GetKeystate(commandPair.first, commandAndButton.previousKeystate) };
				if (currentKeystate == commandAndButton.wantedKeystate)
					commandAndButton.pCommand();

				commandAndButton.previousKeystate = currentKeystate;
			}
		}
	}

	bool Mouse::IsPressed(const MouseButton gameInput) const noexcept
	{
		return static_cast<std::underlying_type<MouseButton>::type>(gameInput) == SDL_GetMouseState(NULL, NULL);
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

	const std::unordered_map<MouseButton, std::vector<CommandAndButton>>& Mouse::GetCommands() const noexcept
	{
		return m_MouseCommands;
	}

	void Mouse::RemoveCommand(const std::function<void()>& pCommand) noexcept
	{
		for (const CommandPair& commandPair : m_MouseCommands)
			for (const CommandAndButton& commandAndButton : commandPair.second)
				if (commandAndButton.pCommand.target_type().hash_code() == pCommand.target_type().hash_code())
					m_MouseCommands.erase(commandPair.first);
	}

	void Mouse::ResetInputs() noexcept
	{
		for (std::pair<const MouseButton, std::vector<CommandAndButton>>& commandPair : m_MouseCommands)
			for (CommandAndButton& commandAndButton : commandPair.second)
				commandAndButton.previousKeystate = State::NotPressed;
	}
}