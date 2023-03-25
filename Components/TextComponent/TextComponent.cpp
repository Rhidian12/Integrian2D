#include "TextComponent.h"
#include "../../Printer/Printer.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../TextureManager/TextureManager.h"
#include "../../Texture/Texture.h"

namespace Integrian2D
{
	TextComponent::TextComponent(GameObject* const pParent, const std::string& text)
		: TextComponent{ pParent, text, 50, nullptr, RGBColour{255u, 255u, 255u} }
	{}

	TextComponent::TextComponent(GameObject* const pParent, const std::string& text, const int textSize)
		: TextComponent{ pParent, text, textSize, nullptr, RGBColour{255u, 255u, 255u} }
	{}

	TextComponent::TextComponent(GameObject* const pParent, const std::string& text, const int textSize, const RGBColour& colour)
		: TextComponent{ pParent, text, textSize, nullptr, colour }
	{}

	TextComponent::TextComponent(GameObject* const pParent, const std::string& text, const int textSize, Texture* const pFont)
		: TextComponent{ pParent, text, textSize, pFont, RGBColour{255u, 255u, 255u} }
	{}

	TextComponent::TextComponent(GameObject* const pParent, const std::string& text, const int textSize, Texture* const pFont, const RGBColour& colour)
		: Component{ pParent }
		, m_TextToRender{ text }
		, m_TextSize{ textSize }
		, m_TextColour{ colour }
		, m_pFont{ pFont }
	{
		/* if we need to use the default font */
		if (!pFont)
		{
			/* check if this specific font exists */
			TextureManager* const pInstance{ TextureManager::GetInstance() };

			Texture* pTexture{ pInstance->GetTexture("_Integrian2D_DefaultFont_" + std::to_string(textSize) + ToString(colour)) };

			if (pTexture)
				m_pFont = pTexture;
			else
			{
				Texture* pNewTexture{ new Texture{ Printer::possibleCharacters, "Resources/defaultfont.ttf",textSize,colour } };
				pInstance->AddTexture("_Integrian2D_DefaultFont_" + std::to_string(textSize) + ToString(colour), pNewTexture);
				m_pFont = pNewTexture;
			}
		}
	}

	void TextComponent::Render() const
	{
		Printer::RenderString(m_pFont, m_pOwner->pTransform->GetWorldPosition(), m_pOwner->pTransform->GetWorldAngle(), m_pOwner->pTransform->GetWorldScale(), m_TextToRender);
	}

	void TextComponent::SetTextToRender(const std::string& text) noexcept
	{
		m_TextToRender = text;
	}

	void TextComponent::SetTextSize(const int textSize) noexcept
	{
		m_TextSize = textSize;
	}

	void TextComponent::SetTextColour(const RGBColour& textColour) noexcept
	{
		m_TextColour = textColour;
	}

	void TextComponent::SetTextFont(Texture* const pFont) noexcept
	{
		m_pFont = pFont;
	}

	const std::string& TextComponent::GetTextToRender() const noexcept
	{
		return m_TextToRender;
	}

	float TextComponent::GetTextWidth() const noexcept
	{
		return m_pFont->GetWidth();
	}

	float TextComponent::GetTextHeight() const noexcept
	{
		return m_pFont->GetHeight();
	}
}