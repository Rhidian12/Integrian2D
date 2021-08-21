#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../DataType/DataType.h"
#include "../../Utils/Utils.h"

namespace Integrian2D
{
	class BinaryReader final
	{
	public:
		BinaryReader(std::string fileName);
		~BinaryReader();

		void Close() noexcept;

		ReadData Read() noexcept
		{
			Utils::Assert(m_File.is_open(), "BinaryReader could not open the file!");

			DataType type{ ReadType() };
			ReadData readData{};

			switch (type)
			{
			case DataType::uint8_t:
			{
				uint8_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::uint16_t:
			{
				uint16_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::uint32_t:
			{
				uint32_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::uint64_t:
			{
				uint64_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::int8_t:
			{
				int8_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::int16_t:
			{
				int16_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::int32_t:
			{
				int32_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::int64_t:
			{
				int64_t data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::floatP:
			{
				float data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::doubleP:
			{
				double data{};
				m_File.read(reinterpret_cast<char*>(&data), sizeof(data));

				readData = ReadData{ data, type };
			}
			break;
			case DataType::string:
			{
				size_t stringSize{};

				m_File.read(reinterpret_cast<char*>(&stringSize), sizeof(size_t));

				std::string data{};
				data.resize(stringSize);

				m_File.read(&data[0], stringSize);

				readData = ReadData{ data, type };
			}
			break;
			default:
				Utils::Assert(false, "Type is not part of DataType!");
				break;
			}

			return readData;
		}

	private:
		DataType ReadType() noexcept
		{
			DataType type{};
			m_File.read(reinterpret_cast<char*>(&type), sizeof(size_t));

			return type;
		}

		std::fstream m_File;
	};
}

