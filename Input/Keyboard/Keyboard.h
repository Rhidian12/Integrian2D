#pragma once

#include "../../GameInput/GameInput.h" // GameInput
#include <vector> // std::vector

namespace Integrian2D
{
	class Command;

	class Keyboard final
	{
	public:
		static Keyboard* CreateKeyboard() noexcept;
		static void Cleanup() noexcept;
		~Keyboard();

	private:
		friend class InputManager;

		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;

		void Activate() noexcept;
		void Deactivate() noexcept;

		void AddCommand(const KeyboardInput keyboardInput, const State keyState, Command* const pCommand) noexcept;
		void ExecuteCommands() noexcept;

		void ResetInputs() noexcept;

		bool IsPressed(const KeyboardInput gameInput) const noexcept;
		bool WasPressed(const State previousState) const noexcept;
		State GetKeystate(const KeyboardInput keyboardInput, const State previousState) const noexcept;
		const std::vector<CommandAndButton>& GetCommands() const noexcept;
		KeyboardInput GetWhichKeyIsPressed() const noexcept;

		void RemoveCommand(Command* const pCommand) noexcept;
		void RemoveAllCommands() noexcept;

		bool m_IsActive{ true };
		inline static Keyboard* m_pInstance{};
		std::vector<CommandAndButton> m_KeyboardCommands{};
	};
}
