#pragma once

#ifndef INTEGRIAN2D_MOUSE_H
#define INTEGRIAN2D_MOUSE_H

#include "../../GameInput/GameInput.h" // GameInput
#include <unordered_map> // std::unordered_map
#include <vector> // std::vector

namespace Integrian2D
{
	class Mouse final
	{
	public:
		~Mouse();

	private:
		friend class InputManager;

		using CommandPair = std::pair<MouseButton, std::vector<CommandAndButton>>;
		using UMapIterator = std::unordered_map<MouseButton, std::vector<CommandAndButton>>::iterator;

		Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&& other) noexcept;
		Mouse& operator=(const Mouse&) = delete;
		Mouse& operator=(Mouse&& other) noexcept;

		void AddCommand(const MouseButton mouseButton, const State keyState, const std::function<void()>& pCommand) noexcept;
		void ExecuteCommands() noexcept;

		[[nodiscard]] bool IsPressed(const MouseButton gameInput) const noexcept;
		bool WasPressed(const State previousState) const noexcept;
		State GetKeystate(const MouseButton mouseButton, const State previousState) const noexcept;
		[[nodiscard]] const std::unordered_map<MouseButton, std::vector<CommandAndButton>>& GetCommands() const noexcept;

		void RemoveCommand(const std::function<void()>& pCommand) noexcept;

		void ResetInputs() noexcept;

		std::unordered_map<MouseButton, std::vector<CommandAndButton>> m_MouseCommands{};
	};
}

#endif // !INTEGRIAN_MOUSE_H