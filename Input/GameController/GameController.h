#pragma once

#ifndef INTEGRIAN2D_GAMECONTROLLER_H
#define INTEGRIAN2D_GAMECONTROLLER_H

#include <unordered_map> // std::unordered_map
#include <vector> // std::vector
#include "../../GameInput/GameInput.h" // GameInput

namespace Integrian2D
{
	class Command;
	class GameController final
	{
	public:
		~GameController();

	private:
		friend class InputManager;

		GameController() = default;
		GameController(const uint8_t index);

		GameController(const GameController&) = delete;
		GameController(GameController&& other) noexcept;
		GameController& operator=(const GameController&) = delete;
		GameController& operator=(GameController&& other) noexcept;

		void AddCommand(const ControllerInput controllerInput, const State keyState, const std::function<void()>& pCommand) noexcept;
		void ExecuteCommands() noexcept;

		bool IsPressed(const ControllerInput controllerInput) const noexcept;
		bool WasPressed(const State previousState) const noexcept;
		State GetKeystate(const ControllerInput controllerInput, const State previousState) const noexcept;
		double GetJoystickMovement(const ControllerInput axis) const noexcept;
		double GetTriggerMovement(const ControllerInput axis) const noexcept;
		const std::unordered_map<ControllerInput, std::vector<CommandAndButton>>& GetCommands() const noexcept;

		void RemoveCommand(const std::function<void()>& pCommand) noexcept;

		void ResetInputs() noexcept;

		std::unordered_map<ControllerInput, std::vector<CommandAndButton>> m_pCommands{};

		SDL_GameController* m_pSDLGameController{};
		uint8_t m_Index{};
		static constexpr double m_MaxJoystickValue{ 32767.0 }; // double instead of integer to prevent typecasting

		using CommandPair = std::pair<ControllerInput, std::vector<CommandAndButton>>;
		using UMapIterator = std::unordered_map<ControllerInput, std::vector<CommandAndButton>>::iterator;
	};
}

#endif // INTEGRIAN_GAMECONTROLLER_H