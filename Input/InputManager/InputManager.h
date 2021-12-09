#pragma once

#include "../Mouse/Mouse.h"
#include "../Keyboard/Keyboard.h"
#include "../GameController/GameController.h"
#include "../../Math/TypeDefines.h"
#include "../InputAxis/InputAxis.h"

#include <array>
#include <vector>

namespace Integrian2D
{
	class InputManager final
	{
	public:
		/*
		This function gets called in Core::Run() every frame.
		All input gets processed, and commands linked to those inputs get executed
		*/
		void HandleInput() noexcept;

		/* Add a Command to the InputManager with an input, a KeyState and an optional controller index */
		void AddCommand(const GameInput& gameInput, const std::function<void()>& pCommand, const State keyState, const uint8_t controllerIndex = 0) noexcept;
		
		/* Remove a previously added Command from a specific input */
		void RemoveCommandFromInput(const GameInput& input, std::function<void()>& pCommand, const uint8_t controllerIndex = 0) noexcept;

		/* Remove a previously added Command from all inputs it is linked to */
		void RemoveCommand(const std::function<void()>& pCommand, const uint8_t controllerIndex = 0) noexcept;

		/* Remove all Commands from the InputManager */
		void RemoveAllCommands() noexcept;

		/* Add a new Axis to the InputManager */
		void AddAxis(const InputAxis& inputAxis) noexcept;

		/* If the Axis' positive input is pressed, this function returns 1
			if the Axis' negative input is pressed, this function returns -1
			if the Axis' both inputs are pressed, this function returns 0 */
		int8_t GetAxis(const std::string& axisName, const uint8_t playerIndex = 0);

		/* Returns whether a keyboard key is pressed now */
		bool IsKeyboardKeyPressed(const KeyboardInput gameInput) const noexcept;

		/*
		Returns whether a controller button is pressed now.
		This does not return how much of a Trigger is pressed, use GetTriggerMovement() for that
		*/
		bool IsControllerButtonPressed(const ControllerInput gameInput, const uint8_t playerIndex = 0) const noexcept;

		/* Returns whether a mouse button is pressed now */
		bool IsMouseButtonPressed(const MouseButton gameInput) const noexcept;

		/* Get which key is being pressed at this time */
		const KeyboardInput GetWhichKeyIsPressed() const noexcept;

		/* Get current mouse position */
		const Point2f& GetMousePosition() const noexcept;

		/* Get how much the joystick is moved mapped to a range of [-1, 1] */
		double GetJoystickMovement(const ControllerInput axis, const uint8_t playerIndex = 0) const noexcept;

		/* Get how much a Trigger is pressed mapped to a range of [0, 1] */
		double GetTriggerMovement(const ControllerInput axis, const uint8_t playerIndex = 0) const noexcept;

		/* Returns the map containing all inputs (with corresponding commands) linked to keyboard buttons */
		const std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>& GetKeyboardCommands() const noexcept;

		/* Returns the map containing all inputs (with corresponding commands) linked to mouse buttons */
		const std::unordered_map<MouseButton, std::vector<CommandAndButton>>& GetMouseCommands() const noexcept;

		/* Returns the map containing all inputs (with corresponding commands) linked to controller buttons */
		const std::unordered_map<ControllerInput, std::vector<CommandAndButton>>& GetControllerCommands(const uint8_t index) const noexcept;

		/* Flush the Input states 
		   After calling this function, all inputs will be set to NotPressed 
		   This input state will only last for 1 frame, the next time HandleInput() gets called, all inputs get set to their current state */
		void ResetInputs() noexcept;

		/* Activate all inputs */
		void Activate() noexcept;

		/* Deactivate all inputs */
		void Deactivate() noexcept;

	private:
		friend class Scene;

		InputManager();

		Point2f m_MousePosition;
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
		uint8_t m_AmountOfControllers;
		inline static constexpr uint8_t m_MaxAmountOfControllers{ 4 };

		std::vector<InputAxis> m_Axis;

		std::array<GameController, m_MaxAmountOfControllers> m_Controllers;
		Keyboard m_Keyboard;
		Mouse m_Mouse;
	};
}

