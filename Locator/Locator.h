#pragma once

namespace Integrian2D
{
	class InputManager;
	class PhysicsEngine;
	class EventQueue;

	/* This class can be used to get access to Scene-specific classes in a Singleton-manner */
	class Locator final
	{
	public:
		/* Get a Locator instance */
		static Locator* GetInstance() noexcept;

		/* Internal Usage */
		static void Cleanup() noexcept;

		InputManager* const GetInputManager() const noexcept;
		PhysicsEngine* const GetPhysicsEngine() const noexcept;
		EventQueue* const GetEventQueue() const noexcept;

	private:
		Locator() = default;

		inline static Locator* m_pInstance{};
	};
}
