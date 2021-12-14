#pragma once

#include "../../Math/TypeDefines.h"

#include <string>

namespace Integrian2D
{
	class Texture;

	class Printer final
	{
	public:
		void Render(const Point2f& location, const float angle, const Point2f& scale, const std::string& textToRender) const noexcept;

		Texture* const GetFont() const noexcept;

	private:
		friend class PrinterManager;

		Printer(Texture* const pFont);
		Rectf CalculateSourceRect(const char c) const noexcept;
	
		Texture* m_pFont;
		float m_CharWidth;
		float m_CharHeight;
	};
}