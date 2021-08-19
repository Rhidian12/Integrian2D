#pragma once

#ifndef INTEGRIAN2D_INTEGRIAN2D_H
#define INTEGRIAN2D_INTEGRIAN2D_H

#include <string>

struct SDL_Window;

namespace Integrian2D
{
	class Scene;

	class Integrian2D final
	{
	public:
		Integrian2D(const int windowWidth, const int windowHeight, std::string windowTitle);
		~Integrian2D();

		Integrian2D(const Integrian2D&) = delete;
		Integrian2D(Integrian2D&&) = delete;
		Integrian2D& operator=(const Integrian2D&) = delete;
		Integrian2D& operator=(Integrian2D&&) = delete;

	private:
		bool InitializeLibraries(std::string windowTitle) noexcept;
		void ShutdownLibraries() noexcept;

		SDL_Window* m_pWindow;
		int m_WindowWidth;
		int m_WindowHeight;
	};
}

#endif // !INTEGRIAN2D_INTEGRIAN2D_H