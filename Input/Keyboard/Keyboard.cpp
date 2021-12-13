#include "Keyboard.h" // Header
#include "../../Logger/Logger.h" // Logger
#include "../../Command/Command.h"

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

	Keyboard* Keyboard::CreateKeyboard() noexcept
	{
		ASSERT(m_pInstance == nullptr, "Keyboard::CreateKeyboard() > The Input Manager default creates a Keyboard!");

		m_pInstance = new Keyboard{};

		return m_pInstance;
	}

	void Keyboard::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	Keyboard::~Keyboard()
	{
		m_KeyboardCommands.clear();
	}

	void Keyboard::AddCommand(const KeyboardInput keyboardInput, const State keyState, Command* const pCommand) noexcept
	{
		m_KeyboardCommands.push_back(CommandAndButton{ pCommand,keyState, GameInput{ keyboardInput } });
	}

	void Keyboard::ExecuteCommands() noexcept
	{
		if (!m_IsActive)
			return;

		for (CommandAndButton& commandButton : m_KeyboardCommands)
		{
			const State currentKeystate{ GetKeystate(commandButton.gameInput.keyboardInput, commandButton.previousKeystate) };
			if (currentKeystate == commandButton.wantedKeystate)
				commandButton.pCommand->Execute();

			commandButton.previousKeystate = currentKeystate;
		}
	}

	void Keyboard::ResetInputs() noexcept
	{
		for (CommandAndButton& commandButton : m_KeyboardCommands)
			commandButton.previousKeystate = State::NotPressed;
	}

	bool Keyboard::IsPressed(const KeyboardInput gameInput) const noexcept
	{
		if (gameInput == KeyboardInput::INVALID)
			return false;
		else
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

	const std::vector<CommandAndButton>& Keyboard::GetCommands() const noexcept
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

	void Keyboard::RemoveCommand(Command* const pCommand) noexcept
	{
		m_KeyboardCommands.erase(std::remove(m_KeyboardCommands.begin(), m_KeyboardCommands.end(), pCommand), m_KeyboardCommands.end());
	}
}