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

	void BinaryWriter::Open() noexcept
	{
		m_File.open(m_FileName, std::ios::out | std::ios::binary);
	}

	void BinaryWriter::OpenNewFile(const std::string& newFile) noexcept
	{
		/* Close the binary file */
		m_File.close();

		m_FileName = newFile;

		m_File.open(m_FileName, std::ios::in | std::ios::binary);

		ASSERT(m_File.is_open(), "BinaryReader::OpenNewFile() > The new file could not be opened!");
	}

	void BinaryWriter::Close() noexcept
	{
		m_File.close();
	}
}