#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	class Reader final
	{
	public:
		Reader(const std::string filePath);
		~Reader();

		void Open(const std::string filePath) noexcept;
		void Close() noexcept;

		void SetLine(const unsigned int line) noexcept;

		template<typename Type>
		void Read() const noexcept
		{
			ASSERT(m_File.is_open(), "Reader::Read() > File is not open!");

			Type data{};

			m_File >> data;

			return data;
		}

		unsigned int GetAmountOfLines() noexcept;
		std::string GetLine(const unsigned int line) noexcept;

	private:
		std::fstream m_File;
	};
}