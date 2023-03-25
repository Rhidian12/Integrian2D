#include "Window.h"
#include "../Logger/Logger.h"
#include "../Renderer/Renderer.h"

#include <SDL.h>

namespace Integrian2D
{
	Window::Window(const int windowWidth, const int windowHeight, const std::string& windowTitle)
		: m_WindowWidth{ windowWidth }
		, m_WindowHeight{ windowHeight }
		, m_WindowTitle{ windowTitle }
	{
		m_pWindow = SDL_CreateWindow(
			windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_WindowWidth, m_WindowHeight,
			SDL_WINDOW_OPENGL);

		if (!m_pWindow)
			Logger::GetInstance().LogError(std::string{ "Window::Window() > m_pWindow creation failed" } + SDL_GetError(), __LINE__, __FILE__);

		SDL_GLContext context = SDL_GL_CreateContext(m_pWindow);
		if (context == nullptr)
			Logger::GetInstance().LogError(std::string{ "Window::Window() > Creating a openGL context failed" } + SDL_GetError(), __LINE__, __FILE__);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_pWindow);
	}

	const SDL_Window* const Window::GetSDLWindow() const
	{
		return m_pWindow;
	}
}