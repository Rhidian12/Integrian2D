#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"

#include <string>

namespace Integrian2D
{
	class Printer;
	class Texture;

	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject* const pParent, const std::string& text);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize, const RGBColour& colour);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize, Texture* const pFont);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize, Texture* const pFont, const RGBColour& colour);

		virtual Component* Clone(GameObject* pParent) noexcept override;

		virtual void Render() const override;

		void SetTextToRender(const std::string& text) noexcept;
		void SetTextSize(const int textSize) noexcept;
		void SetTextColour(const RGBColour& textColour) noexcept;
		void SetTextFont(Texture* const pFont) noexcept;

		const std::string& GetTextToRender() const noexcept;
		float GetTextWidth() const noexcept;
		float GetTextHeight() const noexcept;

	private:
		std::string m_TextToRender;
		int m_TextSize;
		RGBColour m_TextColour;
		Texture* m_pFont;
		Printer* m_pPrinter;
	};
}