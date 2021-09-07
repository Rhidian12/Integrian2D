#include "Writer.h"

Integrian2D::Writer::Writer(const std::string filePath)
	: m_File{}
{
	m_File.open(filePath, std::ios::out);
}

Integrian2D::Writer::~Writer()
{
	m_File.close();
}

void Integrian2D::Writer::Open(const std::string filePath) noexcept
{
	m_File.open(filePath, std::ios::out);
}

void Integrian2D::Writer::Close() noexcept
{
	m_File.close();
}
