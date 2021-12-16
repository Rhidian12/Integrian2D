#pragma once

#include "../Integrian2D_API.h"

namespace Integrian2D
{
	class EventQueue;

	/* This class can be used to get access to Scene-specific classes in a Singleton-manner */
	class Locator final
	{
	public:
		/* Get a Locator instance */
		INTEGRIAN2D_API static Locator* GetInstance() noexcept;

		/* Internal Usage */
		INTEGRIAN2D_API static void Cleanup() noexcept;

		INTEGRIAN2D_API EventQueue* const GetEventQueue() const noexcept;

	private:
		Locator() = default;

		inline static Locator* m_pInstance{};
	};
}
