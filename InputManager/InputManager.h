#pragma once

#ifndef INTEGRIAN2D_INPUTMANAGER_H
#define INTEGRIAN2D_INPUTMANAGER_H

namespace Integrian2D
{
	class InputManager final
	{
	public:
		static InputManager* const GetInstance() noexcept;
		static void Cleanup() noexcept;

		virtual ~InputManager() = default;

		/*
		This function gets called in the App::Run() every frame.
		All input gets processed, and commands linked to those inputs get executed
		*/
		void HandleInput();

		void AddCommand(const GameInput& gameInput, const std::function<void()>& pCommand, const State keyState, const uint8_t controllerIndex = 0);
		void RemoveCommandFromInput(const GameInput& input, std::function<void()>& pCommand, const uint8_t controllerIndex = 0);
		void RemoveCommand(const std::function<void()>& pCommand, const uint8_t controllerIndex = 0);
		void RemoveAllCommands();

		/* At the moment, this does nothing, so don't use it*/
		void SetWindowSize(const uint32_t width, const uint32_t height);

		/* Returns whether a keyboard key is pressed now */
		[[nodiscard]] bool IsKeyboardKeyPressed(const KeyboardInput gameInput) const;

		[[nodiscard]] const KeyboardInput GetWhichKeyIsPressed() const noexcept;

		/* Returns whether a mouse button is pressed now */
		[[nodiscard]] bool IsMouseButtonPressed(const MouseButton gameInput) const;

		[[nodiscard]] bool IsPressed(const GameInput gameInput, const uint8_t controllerIndex = 0) const noexcept;

		/*
		Returns whether a controller button is pressed now.
		This does not return how much of a Trigger is pressed, use GetTriggerMovement() for that
		*/
		[[nodiscard]] bool IsControllerButtonPressed(const ControllerInput gameInput, const uint8_t playerIndex = 0) const;

		/* Get current mouse position */
		[[nodiscard]] const Point2f& GetMousePosition() const;

		/* Get how much the joystick is moved mapped to a range of [-1, 1] */
		[[nodiscard]] double GetJoystickMovement(const ControllerInput axis, const uint8_t playerIndex = 0) const;

		/* Get how much a Trigger is pressed mapped to a range of [0, 1] */
		[[nodiscard]] double GetTriggerMovement(const ControllerInput axis, const uint8_t playerIndex = 0) const;

		/* Returns the map containing all inputs (with corresponding commands) linked to keyboard buttons */
		[[nodiscard]] const std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>& GetKeyboardCommands() const;

		/* Returns the map containing all inputs (with corresponding commands) linked to mouse buttons */
		[[nodiscard]] const std::unordered_map<MouseButton, std::vector<CommandAndButton>>& GetMouseCommands() const;

		/* Returns the map containing all inputs (with corresponding commands) linked to controller buttons */
		[[nodiscard]] const std::unordered_map<ControllerInput, std::vector<CommandAndButton>>& GetControllerCommands(const uint8_t index) const;

		void ResetInputs();

	private:
		friend class App;
		InputManager();

		inline static InputManager* m_pInstance{};

		void SetControllerCommands(std::unordered_map<ControllerInput, std::vector<CommandAndButton>> commands, const uint8_t index);
		void SetKeyboardCommands(std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> commands);
		void SetMouseCommands(std::unordered_map<MouseButton, std::vector<CommandAndButton>> commands);

		Point2f m_MousePosition;
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
		uint8_t m_AmountOfControllers;
		inline static constexpr uint8_t m_MaxAmountOfControllers{ 4 };

		std::array<GameController, m_MaxAmountOfControllers> m_Controllers;
		Keyboard m_Keyboard;
		Mouse m_Mouse;
	};
}

#endif // !INTEGRIAN2D_INPUTMANAGER_H