#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"

#include <string>

namespace Integrian2D
{
	class Texture;

	/* A Component to render text to the screen */
	class TextComponent final : public Component
	{
	public:
		/* If no Font is passed to the TextComponent, the default fonts gets used */
		TextComponent(GameObject* const pParent, const std::string& text);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize, const RGBColour& colour);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize, Texture* const pFont);
		TextComponent(GameObject* const pParent, const std::string& text, const int textSize, Texture* const pFont, const RGBColour& colour);

		virtual Component* Clone(GameObject* pParent) noexcept override;

		virtual void Render() const override;

		/* Set the text to be rendered to the screen */
		void SetTextToRender(const std::string& text) noexcept;

		/* Set the size of the text to be rendered 
			Note that this might require a new texture for the text to be initialized */
		void SetTextSize(const int textSize) noexcept;

		/* Set the colour of the text to be rendered
			Note that this might require a new texture for the text to be initialized */
		void SetTextColour(const RGBColour& textColour) noexcept;

		/* Set the font of the text to be rendered
			Note that this might require a new texture for the text to be initialized */
		void SetTextFont(Texture* const pFont) noexcept;

		/* Get the text that is being rendered to the screen */
		const std::string& GetTextToRender() const noexcept;

		/* Get the width of the text being rendered to the screen */
		float GetTextWidth() const noexcept;

		/* Get the height of the text being rendered to the screen */
		float GetTextHeight() const noexcept;

	private:
		std::string m_TextToRender;
		int m_TextSize;
		RGBColour m_TextColour;
		Texture* m_pFont;
	};
}