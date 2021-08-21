#include "BinaryWriter.h"

namespace Integrian2D
{
	BinaryWriter::BinaryWriter(std::string filePath)
		: m_File{}
	{
		m_File.open(filePath, std::ios::out | std::ios::binary);
	}

	BinaryWriter::~BinaryWriter()
	{
		Close();
	}

	void BinaryWriter::Close() noexcept
	{
		m_File.close();
	}
}