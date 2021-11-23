#pragma once

#include <string>

namespace Integrian2D
{
	class Scene;
	class Window;

	class Core final
	{
	public:
		/* Create an instance of the engine, this initializes the libraries used by the engine and creates a window 
		   Call this constructor only ONCE */
		Core(const int windowWidth, const int windowHeight, const std::string& windowTitle);
		~Core();

		/* This function starts the Engine and should be called ONCE */
		void Run();

		/* Is the Engine running? */
		bool IsEngineRunning() const noexcept;

		Core(const Core&) = delete;
		Core(Core&&) = delete;
		Core& operator=(const Core&) = delete;
		Core& operator=(Core&&) = delete;

	private:
		void InitializeLibraries(const int windowWidth, const int windowHeight, const std::string& windowTitle) noexcept;
		void ShutdownLibraries() noexcept;

		bool m_IsEngineRunning;

		Window* m_pWindow;
		int m_WindowWidth;
		int m_WindowHeight;
	};
}
