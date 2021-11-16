#include "Keyboard.h" // Header
#include "../../Logger/Logger.h" // Logger

namespace Integrian2D
{
	Keyboard::Keyboard(Keyboard&& other) noexcept
	{
		m_KeyboardCommands = other.m_KeyboardCommands;
		other.m_KeyboardCommands.clear();
	}

	Keyboard& Keyboard::operator=(Keyboard&& other) noexcept
	{
		m_KeyboardCommands = other.m_KeyboardCommands;
		other.m_KeyboardCommands.clear();

		return *this;
	}

	void Keyboard::Activate() noexcept
	{
		m_IsActive = true;
	}

	void Keyboard::Deactivate() noexcept
	{
		m_IsActive = false;
	}

	Keyboard::~Keyboard()
	{
		m_KeyboardCommands.clear();
	}

	void Keyboard::AddCommand(const KeyboardInput keyboardInput, const State keyState, const std::function<void()>& pCommand) noexcept
	{
		m_KeyboardCommands[keyboardInput].push_back(CommandAndButton{ pCommand,keyState });
	}

	void Keyboard::ExecuteCommands() noexcept
	{
		if (!m_IsActive)
			return;

		for (std::pair<const KeyboardInput, std::vector<CommandAndButton>>& commandPair : m_KeyboardCommands)
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

	void Keyboard::ResetInputs() noexcept
	{
		for (std::pair<const KeyboardInput, std::vector<CommandAndButton>>& commandPair : m_KeyboardCommands)
			for (CommandAndButton& commandAndButton : commandPair.second)
				commandAndButton.previousKeystate = State::NotPressed;
	}

	bool Keyboard::IsPressed(const KeyboardInput gameInput) const noexcept
	{
		if (gameInput == KeyboardInput::INVALID)
			return false;

		return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(gameInput)];
	}

	bool Keyboard::WasPressed(const State previousState) const noexcept
	{
		return (previousState == State::OnPress || previousState == State::OnHeld);
	}

	State Keyboard::GetKeystate(const KeyboardInput keyboardInput, const State previousState) const noexcept
	{
		if (WasPressed(previousState))
		{
			if (IsPressed(keyboardInput))
				return State::OnHeld;

			else
				return State::OnRelease;
		}

		if (IsPressed(keyboardInput))
			return State::OnPress;

		return State::NotPressed;
	}

	const std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>& Keyboard::GetCommands() const noexcept
	{
		return m_KeyboardCommands;
	}

	KeyboardInput Keyboard::GetWhichKeyIsPressed() const noexcept
	{
		const Uint8* pKeyboardState{ SDL_GetKeyboardState(nullptr) };

		for (int i{ static_cast<int>(SDL_SCANCODE_A) }; i <= SDL_SCANCODE_AUDIOFASTFORWARD; ++i) // SDL_NUM_SCANCODES is incorrect?
			if (pKeyboardState[static_cast<SDL_Scancode>(i)])
					return static_cast<KeyboardInput>(i);

		return KeyboardInput::INVALID;
	}

	void Keyboard::RemoveCommand(const std::function<void()>& pCommand) noexcept
	{
		for (const CommandPair& commandPair : m_KeyboardCommands)
			for (const CommandAndButton& commandAndButton : commandPair.second)
				if (commandAndButton.pCommand.target_type().hash_code() == pCommand.target_type().hash_code())
					m_KeyboardCommands.erase(commandPair.first);
	}
}