#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	/* This is a RAII writer to write data to binary files */
	class BinaryWriter final
	{
	public:
		/* Opens the file with path fileName */
		BinaryWriter(const std::string& filePath);
		~BinaryWriter();

		/* Open the binary file
		   This happens automatically on creation of the writer */
		void Open() noexcept;

		/* Open a new binary file */
		void OpenNewFile(const std::string& newFile) noexcept;

		/* Close the binary file
		   This happens automatically on destruction of the writer */
		void Close() noexcept;

		/* Read data from the binary file
		   If the requested data is not POD, this function might result in undefined behaviour */
		template<typename Data>
		void Write(const Data& data) noexcept
		{
			ASSERT(m_File.is_open(), "BinaryWriter could not open the file!");

			typedef std::remove_const_t<std::remove_reference_t<decltype(data)>> removeCVData;

			static_assert(!std::is_same_v<removeCVData, char[]>, "String literals are not supported! Only strings!");
			
			if constexpr (std::is_same_v<removeCVData, std::string>)
			{
				const size_t size{ data.size() };
				m_File.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
				m_File.write(data.c_str(), data.size());
			}
			else
				m_File.write(reinterpret_cast<const char*>(&data), sizeof(Data));
		}

	private:
		std::fstream m_File;
		std::string m_FileName;
	};
}