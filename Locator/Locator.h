#pragma once

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
