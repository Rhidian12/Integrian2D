#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	/* This is a RAII reader to read data from binary files */
	class BinaryReader final
	{
	public:
		/* Opens the file with path fileName */
		BinaryReader(const std::string& fileName);
		~BinaryReader();

		/* Close the binary file 
		   This happens automatically on destruction of the reader */
		void Close() noexcept;	

		/* Read data from the binary file 
		   If the requested data is wrong, this function will result in undefined behaviour */
		template<typename Type>
		Type Read() noexcept
		{
			ASSERT(m_File.is_open(), "BinaryReader::Read() > The file has not been opened!");

			if constexpr (std::is_same_v<Type, std::string>)
			{
				size_t stringSize{};

				m_File.read(reinterpret_cast<char*>(&stringSize), sizeof(size_t));

				std::string data{};
				data.resize(stringSize);

				m_File.read(&data[0], stringSize);

				return data;
			}
			else
			{
				Type data{};

				m_File.read(reinterpret_cast<char*>(&data), sizeof(Type));

				return data;
			}
		}

	private:
		std::fstream m_File;
	};
}

