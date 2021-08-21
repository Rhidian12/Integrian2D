#include "BinaryReader.h"

namespace Integrian2D
{
	BinaryReader::BinaryReader(std::string fileName)
		: m_File{}
	{
		m_File.open(fileName, std::ios::in, std::ios::binary);
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