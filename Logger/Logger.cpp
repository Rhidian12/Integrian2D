#include "Logger.h"

namespace Integrian2D
{
	void Logger::LogNoWarning(const std::string& message, bool newLine) noexcept
	{
#if defined (_DEBUG) || ( not defined(LOGGER_DEBUGONLY) && defined(NDEBUG) )
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);
		std::cout << message;

		if (newLine)
			std::cout << std::endl;

		SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else
		int test;
		(void)message;
		(void)newLine;
#endif
	}

	void Logger::LogWarning(const std::string& message, bool newLine) noexcept
	{
#if defined (_DEBUG) || ( not defined(LOGGER_DEBUGONLY) && defined(NDEBUG) )
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 6);
		std::cout << message;

		if (newLine)
			std::cout << std::endl;

		SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else
		(void)message;
		(void)newLine;
#endif
	}

	void Logger::LogError(const std::string& message, bool newLine) noexcept
	{
#if defined (_DEBUG) || ( not defined(LOGGER_DEBUGONLY) && defined(NDEBUG) )
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << message;

		if (newLine)
			std::cout << std::endl;

		SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else
		(void)message;
		(void)newLine;
#endif
	}

	void Logger::LogSevereError(const std::string& message, bool newLine) noexcept
	{
#if defined (_DEBUG) || ( not defined(LOGGER_DEBUGONLY) && defined(NDEBUG) )
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 4);
		std::cout << message;

		if (newLine)
			std::cout << std::endl;

		SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else
		(void)message;
		(void)newLine;
#endif
	}
}