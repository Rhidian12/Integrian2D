#include "BinaryWriter.h"

namespace Integrian2D
{
	BinaryWriter::BinaryWriter(const std::string& filePath)
		: m_File{}
		, m_FileName{ filePath }
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