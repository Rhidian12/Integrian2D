#include "BinaryReader.h"

namespace Integrian2D
{
	BinaryReader::BinaryReader(const std::string& fileName)
		: m_File{}
	{
		m_File.open(fileName, std::ios::in, std::ios::binary);

		ASSERT(m_File.is_open(), "BinaryReader::BinaryReader() > File could not be opened!");
	}

	BinaryReader::~BinaryReader()
	{
		Close();
	}

	void BinaryReader::Close() noexcept
	{
		m_File.close();
	}
}