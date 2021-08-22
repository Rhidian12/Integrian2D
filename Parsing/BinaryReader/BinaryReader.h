#pragma once

#include <string>
#include <fstream>
#include <type_traits>

#include "../../Utils/Utils.h"

namespace Integrian2D
{
	class BinaryReader final
	{
	public:
		BinaryReader(std::string fileName);
		~BinaryReader();

		void Close() noexcept;	

		template<typename Type>
		Type Read() noexcept
		{
			Utils::Assert(m_File.is_open(), "BinaryReader could not open the file!");

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

