#include "Locator.h"
#include "../Utils/Utils.h"

namespace Integrian2D
{
	Locator* Locator::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new Locator{};

		return m_pInstance;
	}
	void Locator::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}
}