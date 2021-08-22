#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	class BinaryWriter final
	{
	public:
		BinaryWriter(std::string filePath);
		~BinaryWriter();

		void Close() noexcept;

		template<typename Data>
		void Write(const Data& data) noexcept
		{
			Utils::Assert(m_File.is_open(), "BinaryWriter could not open the file!");

			typedef std::remove_const_t<std::remove_reference_t<decltype(data)>> removeCVData;

			Utils::Assert(!std::is_same_v<removeCVData, char[]>, "String literals are not supported! Only strings!");
			
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
	};
}