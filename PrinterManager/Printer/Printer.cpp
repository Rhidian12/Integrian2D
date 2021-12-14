#include "Printer.h"
#include "../../Texture/Texture.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	/* Standard layout of a TTF file */
	inline constexpr const char* pPossibleCharacters{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:;'\"(!?)+-*/=" };
	inline constexpr unsigned int amountOfCharacters{ 77 };

	Printer::Printer(Texture* const pFont, const int textSize, const RGBColour& textColour)
		: m_pFont{ pFont }
		, m_CharWidth{ pFont->GetWidth() / amountOfCharacters }
		, m_CharHeight{ pFont->GetHeight() }
		, m_TextSize{ textSize }
		, m_TextColour{ textColour }
	{}

	void Printer::Render(const Point2f& location, const float angle, const Point2f& scale, const std::string& textToRender) const noexcept
	{
		for (size_t i{}; i < textToRender.size(); ++i)
		{
			Renderer::GetInstance()->RenderTexture(m_pFont,
				PRectf{ location,m_CharWidth, m_CharHeight,
				angle, scale },
				CalculateSourceRect(textToRender[i]));
		}
	}

	Texture* const Printer::GetFont() const noexcept
	{
		return m_pFont;
	}

	int Printer::GetTextSize() const noexcept
	{
		return m_TextSize;
	}

	const RGBColour& Printer::GetTextColour() const noexcept
	{
		return m_TextColour;
	}

	Rectf Printer::CalculateSourceRect(const char c) const noexcept
	{
		for (unsigned int i{}; i < amountOfCharacters; ++i)
		{
			if (pPossibleCharacters[i] == c)
				return Rectf{ m_CharWidth * i,0.f,m_CharWidth,m_CharHeight };
		}

		ASSERT(false, std::string{ "Printer::CalculateSourceRect() > The character: " } + c + " is not supported!");

		return Rectf{};
	}
}