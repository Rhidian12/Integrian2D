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

		virtual void Render() const override;

		void SetTextToRender(const std::string& text) noexcept;

		const std::string& GetTextToRender() const noexcept;
		float GetTextWidth() const noexcept;
		float GetTextHeight() const noexcept;

	private:
		std::string m_TextToRender;
		int m_TextSize;
		RGBColour m_TextColour;
		Printer* m_pPrinter;
	};
}