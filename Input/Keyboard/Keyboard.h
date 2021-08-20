#pragma once

#ifndef INTEGRIAN2D_KEYBOARDINPUT_H
#define INTEGRIAN2D_KEYBOARDINPUT_H

#include "../../GameInput/GameInput.h" // GameInput
#include <unordered_map> // std::unordered_map
#include <vector> // std::vector

namespace Integrian2D
{
	class Command;
	class Keyboard final
	{
	public:
		~Keyboard();

	private:
		friend class InputManager;

		using CommandPair = std::pair<KeyboardInput, std::vector<CommandAndButton>>;
		using UMapIterator = std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>::iterator;

		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&& other) noexcept;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&& other) noexcept;

		void AddCommand(const KeyboardInput keyboardInput, const State keyState, const std::function<void()>& pCommand) noexcept;
		void ExecuteCommands() noexcept;

		void ResetInputs() noexcept;

		[[nodiscard]] bool IsPressed(const KeyboardInput gameInput) const noexcept;
		bool WasPressed(const State previousState) const noexcept;
		State GetKeystate(const KeyboardInput keyboardInput, const State previousState) const noexcept;
		[[nodiscard]] const std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>& GetCommands() const noexcept;
		[[nodiscard]] KeyboardInput GetWhichKeyIsPressed() const noexcept;

		void RemoveCommand(const std::function<void()>& pCommand) noexcept;

		std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> m_KeyboardCommands{};
	};
}

#endif // !INTEGRIAN_KEYBOARDINPUT_H