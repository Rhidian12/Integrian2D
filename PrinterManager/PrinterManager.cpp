#include "PrinterManager.h"
#include "../Utils/Utils.h"
#include "Printer/Printer.h"

namespace Integrian2D
{
	PrinterManager* PrinterManager::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new PrinterManager{};

		return m_pInstance;
	}

	void PrinterManager::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	PrinterManager::~PrinterManager()
	{
		for (Printer* pPrinter : m_pPrinters)
			Utils::SafeDelete(pPrinter);
	}

	Printer* const PrinterManager::CreatePrinter(Texture* const pFont, const int textSize, const RGBColour& textColour) noexcept
	{
		if (auto it = std::find_if(m_pPrinters.cbegin(), m_pPrinters.cend(), [pFont, textSize, &textColour](Printer* const pPrinter)->bool
			{
				return pFont == pPrinter->GetFont() && textSize == pPrinter->GetTextSize() && textColour == pPrinter->GetTextColour();
			}); it == m_pPrinters.cend())
		{
			m_pPrinters.push_back(new Printer{ pFont, textSize, textColour });
			return m_pPrinters.back();
		}
		else
			return *it;
	}
}