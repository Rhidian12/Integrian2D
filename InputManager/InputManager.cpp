#include "InputManager.h"
#include "../Utils/Utils.h"

#include <SDL.h>

extern bool g_IsLooping;

namespace Integrian2D
{
	InputManager* const Integrian2D::InputManager::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new InputManager{};

		return m_pInstance;
	}

	void InputManager::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	void InputManager::HandleInput()
	{
		int x{}, y{};
		const Uint32 mouseState = SDL_GetMouseState(&x, &y);

		//m_MousePosition = Point2f{ float(x),float(m_WindowHeight - y) };

		m_AmountOfControllers = uint8_t(SDL_NumJoysticks()); // check if controllers have been added / removed

		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				g_IsLooping = false;
				break;
			default:
				break;
			}
		}

		m_Keyboard.ExecuteCommands();
		m_Mouse.ExecuteCommands();

		//SDL_GameControllerUpdate();
		for (uint32_t i{}; i < m_AmountOfControllers; ++i)
			m_Controllers[i].ExecuteCommands();
	}
}
