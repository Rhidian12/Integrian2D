#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	/* This is a RAII reader to read data from non-binary files */
	class Reader final
	{
	public:
		/* Opens the non-binary file with path filePath */
		Reader(const std::string filePath);
		~Reader();

		/* Open a new non-binary file */
		void Open(const std::string filePath) noexcept;

		/* Close the non-binary file
		   This happens automatically on destruction of the reader */
		void Close() noexcept;

		/* Sets the Reader's internal line number 
		   E.g. Calling this function with parameter 0 will set the reader to the beginning of the file 
		   Note that this function has a linear time complexity, the further the line number the longer this takes */
		void SetLine(const unsigned int line) noexcept;

		/* Read data from the non-binary file
		   If the requested data is wrong, this function will result in undefined behaviour */
		template<typename Type>
		void Read() const noexcept
		{
			ASSERT(m_File.is_open(), "Reader::Read() > File is not open!");

			Type data{};

			m_File >> data;

			return data;
		}

		/* Get amount of lines this non-binary file contains 
		   Note that this function has a linear time complexity */
		unsigned int GetAmountOfLines() noexcept;

		/* Read a specific line from the file */
		std::string GetLine(const unsigned int line) noexcept;

	private:
		std::fstream m_File;
	};
}