#pragma once

#include <string>

struct SDL_Window;
namespace Integrian2D
{
	class Window final
	{
	public:
		Window(const int windowWidth, const int windowHeight, const std::string windowTitle);
		~Window();

		const SDL_Window* const GetSDLWindow() const noexcept;

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

	private:
		int m_WindowWidth;
		int m_WindowHeight;
		std::string m_WindowTitle;

		SDL_Window* m_pWindow;
	};
}

