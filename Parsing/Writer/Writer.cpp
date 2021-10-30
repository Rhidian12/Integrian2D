#include "Writer.h"

Integrian2D::Writer::Writer(const std::string& filePath)
	: m_File{}
	, m_FileName{ filePath }
{
	m_File.open(filePath);
}

Integrian2D::Writer::~Writer()
{
	m_File.close();
}

void Integrian2D::Writer::Open() noexcept
{
	m_File.open(m_FileName, std::ios::out);
}

void Integrian2D::Writer::OpenNewFile(const std::string& filePath) noexcept
{
	m_File.close();

	m_FileName = filePath;

	m_File.open(filePath);
}

void Integrian2D::Writer::Close() noexcept
{
	m_File.close();
}
