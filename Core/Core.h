#pragma once

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
		void InitializeLibraries(const int windowWidth, const int windowHeight, const std::string windowTitle) noexcept;
		void ShutdownLibraries() noexcept;

		Window* m_pWindow;
		int m_WindowWidth;
		int m_WindowHeight;
	};
}
