#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	class Writer final
	{
	public:
		Writer(const std::string filePath);
		~Writer();

		void Open(const std::string filePath) noexcept;
		void Close() noexcept;

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
	};
}