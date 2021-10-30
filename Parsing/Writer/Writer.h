#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	/* This is a RAII writer to write data to non-binary files */
	class Writer final
	{
	public:
		/* Opens the non-binary file with path filePath */
		Writer(const std::string& filePath);
		~Writer();

		/* Open a new non-binary file */
		void OpenNewFile(const std::string& filePath) noexcept;

		/* Close the non-binary file
		   This happens automatically on destruction of the writer */
		void Close() noexcept;

		/* Write data to the non-binary file
		   If the requested data has no operator<<, this function will result in a compiler error */
		template<typename Type>
		void Write(const Type& data, const bool newLine) noexcept
		{
			ASSERT(m_File.is_open(), "Writer could not write to the file!");

			m_File << data;

			if (newLine)
				m_File << '\n';
		}

	private:
		std::ofstream m_File;
		std::string m_FileName;
	};
}