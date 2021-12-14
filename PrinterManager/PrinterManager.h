#pragma once

#include "../Math/TypeDefines.h"

#include <vector>

namespace Integrian2D
{
	class Texture;
	class Printer;

	class PrinterManager final
	{
	public:
		static PrinterManager* GetInstance() noexcept;
		static void Cleanup() noexcept;
		~PrinterManager();

		Printer* const CreatePrinter(Texture* const pFont, const int textSize, const RGBColour& textColour) noexcept;

	private:
		PrinterManager() = default;

		inline static PrinterManager* m_pInstance{};

		std::vector<Printer*> m_pPrinters;
	};
}