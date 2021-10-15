#include "IListener.h"

#include "../Locator/Locator.h"
#include "../EventQueue/EventQueue.h"

namespace Integrian2D
{
	IListener::IListener()
		: m_IsActive{ true }
	{
		Locator::GetInstance()->GetEventQueue()->AddListener(this);
	}
}