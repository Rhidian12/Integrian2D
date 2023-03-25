#pragma once

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

namespace Integrian2D
{
#ifdef _WIN32
	enum class MessageColour : uint8_t
	{
		Black = 0,
		IntenseBlue = 1,
		Green = 2,
		LightBlue = 3,
		Red = 4,
		Purple = 5,
		Yellow = 6,
		White = 7,
		Grey = 8,
		Blue = 9,
		LightGreen = 10,
		VeryLightBlue = 11,
		LightRed = 12,
		LightPurple = 13,
		VeryLightYellow = 14,
		IntenseWhite = 15
	};
#endif

	class Logger final
	{
	public:
		static Logger& GetInstance();

		void LogMessage(
			const std::string_view message,
			[[maybe_unused]] const int lineNumber,
			[[maybe_unused]] const std::string_view file,
			const bool bVerbose = false
		);

		void LogWarning(
			const std::string_view message,
			[[maybe_unused]] const int lineNumber,
			[[maybe_unused]] const std::string_view file,
			const bool bVerbose = false
		);

		void LogError(
			const std::string_view message,
			[[maybe_unused]] const int lineNumber,
			[[maybe_unused]] const std::string_view file,
			const bool bVerbose = false
		);

		void LogCustomMessage(
			const std::string_view message,
			[[maybe_unused]] const int lineNumber,
			[[maybe_unused]] const std::string_view file,
			const MessageColour colour,
			const bool bVerbose = false
		);

		void LogAssertion(
			const std::string_view message,
			[[maybe_unused]] const int lineNumber,
			[[maybe_unused]] const std::string_view file,
			const MessageColour colour,
			const bool bVerbose = false
		);

	private:
		Logger();

		friend std::unique_ptr<Logger> std::make_unique();
		inline static std::unique_ptr<Logger> Instance{};

		/* typedef void* HANDLE, ergo void* == HANDLE */
		void* ConsoleHandle;
	};
}

