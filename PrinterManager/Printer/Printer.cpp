#include "Printer.h"
#include "../../Texture/Texture.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	/* Standard layout of a TTF file */
	inline const std::string possibleCharacters{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:;'\"(!?)+-*/=" };
	inline const size_t amountOfCharacters{ possibleCharacters.size() };

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
				PRectf{ Point2f{ location.x + m_CharWidth * i, location.y },m_CharWidth, m_CharHeight, angle, scale },
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

	float Printer::GetCharacterWidth() const noexcept
	{
		return m_CharWidth;
	}

	float Printer::GetCharacterHeight() const noexcept
	{
		return m_CharHeight;
	}

	Rectf Printer::CalculateSourceRect(const char c) const noexcept
	{
		return Rectf{ m_CharWidth * possibleCharacters.find(c),0.f,m_CharWidth,m_CharHeight };
	}
}