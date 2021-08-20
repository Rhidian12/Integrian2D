#pragma once

#ifndef INTEGRIAN2D_LOCATOR_H
#define INTEGRIAN2D_LOCATOR_H

namespace Integrian2D
{
	class InputManager;

	class Locator final
	{
	public:
		static Locator* GetInstance() noexcept;
		static void Cleanup() noexcept;

		InputManager* const GetInputManager() const noexcept;

	private:
		Locator() = default;

		inline static Locator* m_pInstance{};
	};
}

#endif // !INTEGRIAN2D_LOCATOR_H