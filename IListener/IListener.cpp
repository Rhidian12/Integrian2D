#include "IListener.h"

#include "../Locator/Locator.h"

namespace Integrian2D
{
	IListener::IListener()
		: m_IsActive{ true }
	{
		Locator::GetInstance();
	}
}