#include "TextComponent.h"
#include "../../PrinterManager/PrinterManager.h"
#include "../../PrinterManager/Printer/Printer.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../TextureManager/TextureManager.h"
#include "../../Texture/Texture.h"

namespace Integrian2D
{
	TextComponent::TextComponent(GameObject* const pParent, const std::string& text)
		: TextComponent{ pParent, text, 10, nullptr, RGBColour{255u, 255u, 255u} }
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
		, m_pPrinter{}
	{
		/* if we need to use the default font */
		if (!pFont)
		{
			/* check if this specific font exists */

			int iterations{};
			TextureManager* const pInstance{ TextureManager::GetInstance() };
			Printer* pPrinter{};

			while (true)
			{
				/* try to find the texture in the texture manager */
				Texture* const pTexture{ pInstance->GetTexture("_Integrian2D_DefaultFont" + std::to_string(iterations)) };

				/* if there is no "default" font of this type */
				if (!pTexture)
					break;
				else
				{
					/* if the default font exists, does there exist a printer? */
					if (pPrinter = PrinterManager::GetInstance()->GetPrinter(pTexture, textSize, colour); pPrinter != nullptr)
						break;
					else
						++iterations;
				}
			}

			/* if there is no printer, create one */
			if (!pPrinter)
			{
				pInstance->AddTexture("_Integrian2D_DefaultFont" + std::to_string(iterations), new Texture{ text, "Resources/ubuntu.regular.ttf", textSize, colour});
				m_pPrinter = PrinterManager::GetInstance()->CreatePrinter(pInstance->GetTexture("_Integrian2D_DefaultFont" + std::to_string(iterations)), textSize, colour);
			}
			else
				m_pPrinter = pPrinter;
		}
	}

	Component* TextComponent::Clone(GameObject* pParent) noexcept
	{
		return new TextComponent{ pParent, m_TextToRender, m_TextSize, m_pFont, m_TextColour };
	}

	void TextComponent::Render() const
	{
		m_pPrinter->Render(m_pOwner->pTransform->GetWorldPosition(), m_pOwner->pTransform->GetWorldAngle(), m_pOwner->pTransform->GetWorldScale(), m_TextToRender);
	}

	void TextComponent::SetTextToRender(const std::string& text) noexcept
	{
		m_TextToRender = text;
	}

	void TextComponent::SetTextSize(const int textSize) noexcept
	{
		m_pPrinter = PrinterManager::GetInstance()->CreatePrinter(m_pFont, textSize, m_TextColour);
		m_TextSize = textSize;
	}

	void TextComponent::SetTextColour(const RGBColour& textColour) noexcept
	{
		m_pPrinter = PrinterManager::GetInstance()->CreatePrinter(m_pFont, m_TextSize, textColour);
		m_TextColour = textColour;
	}

	void TextComponent::SetTextFont(Texture* const pFont) noexcept
	{
		m_pPrinter = PrinterManager::GetInstance()->CreatePrinter(pFont, m_TextSize, m_TextColour);
		m_pFont = pFont;
	}

	const std::string& TextComponent::GetTextToRender() const noexcept
	{
		return m_TextToRender;
	}

	float TextComponent::GetTextWidth() const noexcept
	{
		return m_pPrinter->GetCharacterWidth() * m_TextToRender.size();
	}

	float TextComponent::GetTextHeight() const noexcept
	{
		return m_pPrinter->GetCharacterHeight();
	}
}