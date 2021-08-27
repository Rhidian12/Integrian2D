#pragma once

#ifndef INTEGRIAN2D_INTEGRIAN2D_H
#define INTEGRIAN2D_INTEGRIAN2D_H

#include <string>

#include "../Math/TypeDefines.h"

namespace Integrian2D
{
	class Scene;
	class Window;

	class Core final
	{
	public:
		Core(const int windowWidth, const int windowHeight, const std::string windowTitle);
		~Core();

		void Run();

		Core(const Core&) = delete;
		Core(Core&&) = delete;
		Core& operator=(const Core&) = delete;
		Core& operator=(Core&&) = delete;

	private:
		bool InitializeLibraries(const int windowWidth, const int windowHeight, const std::string windowTitle) noexcept;
		void ShutdownLibraries() noexcept;

		Window* m_pWindow;
		int m_WindowWidth;
		int m_WindowHeight;
	};
}

#endif // !INTEGRIAN2D_INTEGRIAN2D_H