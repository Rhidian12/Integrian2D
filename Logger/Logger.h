#pragma once

#ifndef INTEGRIAN2D_LOGGER_H
#define INTEGRIAN2D_LOGGER_H

#pragma region Reference
// Reference: https://stackoverflow.com/questions/8765938/colorful-text-using-printf-in-c
// Reference: https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
// Reference: https://docs.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes
// Reference: https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c#:~:text=The%20simplest%20way%20you%20can,code%20for%20the%20text%20color.

// BOOL WINAPI SetConsoleTextAttribute(
// 	_In_ HANDLE hConsoleOutput,
//	_In_ WORD   wAttributes
// );
// 

// 0 = black
// 1 = intense blue
// 2 = green
// 3 = light blue
// 4 = red
// 5 = purple
// 6 = yellow
// 7 = white
// 8 = grey
// 9 = blue
// 10 = light green
// 11 = very light blue
// 12 = light red
// 13 = lighter purple
// 14 = very light yellow
// 15 = intense white
#pragma endregion

#include <iostream>
#include <string>
#include <Windows.h>

namespace Integrian2D
{
	class Logger final
	{
	public:
		static void LogNoWarning(const std::string& message, bool newLine = true) noexcept;
		static void LogWarning(const std::string& message, bool newLine = true) noexcept;
		static void LogError(const std::string& message, bool newLine = true) noexcept;
		static void LogSevereError(const std::string& message, bool newLine = true) noexcept;
	};
}

#endif // !INTEGRIAN2D_LOGGER_H