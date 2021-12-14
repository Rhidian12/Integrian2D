#include "TextComponent.h"
#include "../../PrinterManager/PrinterManager.h"
#include "../../PrinterManager/Printer/Printer.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"

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
		, m_pPrinter{ PrinterManager::GetInstance()->CreatePrinter(pFont, textSize, colour) }
	{}

	void TextComponent::Render() const
	{
		m_pPrinter->Render(m_pOwner->pTransform->GetWorldPosition(), m_pOwner->pTransform->GetWorldAngle(), m_pOwner->pTransform->GetWorldScale(), m_TextToRender);
	}

	void TextComponent::SetTextToRender(const std::string& text) noexcept
	{
		m_TextToRender = text;
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