#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../DataType/DataType.h"
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
			
			WriteType(data);

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
		template<typename Data>
		void WriteType(const Data& data) noexcept
		{
			typedef std::remove_const_t<std::remove_reference_t<decltype(data)>> removeCVData;

			if constexpr (std::is_same_v<removeCVData, uint8_t>)
			{
				DataType type{ DataType::uint8_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, uint16_t>)
			{
				DataType type{ DataType::uint16_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, uint32_t>)
			{
				DataType type{ DataType::uint32_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, uint64_t>)
			{
				DataType type{ DataType::uint64_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, int8_t>)
			{
				DataType type{ DataType::int8_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, int16_t>)
			{
				DataType type{ DataType::int16_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, int32_t>)
			{
				DataType type{ DataType::int32_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, int64_t>)
			{
				DataType type{ DataType::int64_t };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, float>)
			{
				DataType type{ DataType::floatP };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, double>)
			{
				DataType type{ DataType::doubleP };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
			else if constexpr (std::is_same_v<removeCVData, std::string>)
			{
				DataType type{ DataType::string };
				m_File.write(reinterpret_cast<const char*>(&type), sizeof(size_t));
			}
		}

		std::fstream m_File;
	};
}