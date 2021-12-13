#pragma once

namespace Integrian2D
{
	class EventQueue;

	/* This class can be used to get access to Scene-specific classes in a Singleton-manner */
	class Locator final
	{
	public:
		/* Get a Locator instance */
		static Locator* GetInstance() noexcept;

		/* Internal Usage */
		static void Cleanup() noexcept;

		EventQueue* const GetEventQueue() const noexcept;

	private:
		Locator() = default;

		inline static Locator* m_pInstance{};
	};
}
