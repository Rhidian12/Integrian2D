#include "BinaryReader.h"

namespace Integrian2D
{
	BinaryReader::BinaryReader(const std::string& fileName)
		: m_File{}
		, m_FileName{ fileName }
	{
		m_File.open(fileName, std::ios::in | std::ios::binary);

		ASSERT(m_File.is_open(), "BinaryReader::BinaryReader() > File could not be opened!");
	}

	BinaryReader::~BinaryReader()
	{
		Close();
	}

	void BinaryReader::Open() noexcept
	{
		m_File.open(m_FileName, std::ios::in | std::ios::binary);
	}

	void BinaryReader::OpenNewFile(const std::string& newFile) noexcept
	{
		/* Close the binary file */
		m_File.close();

		m_FileName = newFile;

		m_File.open(m_FileName, std::ios::in | std::ios::binary);

		ASSERT(m_File.is_open(), "BinaryReader::OpenNewFile() > The new file could not be opened!");
	}

	void BinaryReader::Close() noexcept
	{
		m_File.close();
	}
}