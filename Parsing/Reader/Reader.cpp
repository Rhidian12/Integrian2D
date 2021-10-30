#include "Reader.h"
#include <algorithm>

namespace Integrian2D
{
	Reader::Reader(const std::string& filePath)
		: m_File{}
		, m_FileName{ filePath }
	{
		m_File.open(filePath, std::ios::in);
	}

	Reader::~Reader()
	{
		m_File.close();
	}

	void Reader::Open(const std::string filePath) noexcept
	{
		m_File.open(filePath, std::ios::in);
	}

	void Reader::Close() noexcept
	{
		m_File.close();
	}

	void Reader::SetLine(const unsigned int line) noexcept
	{
		ASSERT(line < GetAmountOfLines(), "Reader::SetLine() > The line index is out of bounds!");

		m_File.seekg(0); // set to start of file

		for (unsigned int i{}; i < line; ++i)
		{
			std::string temp{};
			std::getline(m_File, temp);
		}
	}

	unsigned int Reader::GetAmountOfLines() noexcept
	{
		// Reference: https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file

		int lineCount{};

		while (m_File.peek() != std::ios::eofbit)
		{
			std::string temp{};
			std::getline(m_File, temp);

			++lineCount;
		}

		return lineCount;
	}

	std::string Reader::GetLine(const unsigned int line) noexcept
	{
		SetLine(line);

		std::string temp{};
		std::getline(m_File, temp);

		return temp;
	}
}
