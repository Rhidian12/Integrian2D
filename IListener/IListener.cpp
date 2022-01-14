#include "IListener.h"

#include "../EventQueue/EventQueue.h"

namespace Integrian2D
{
	IListener::IListener()
		: m_IsActive{ true }
	{
		EventQueue::GetInstance()->AddListener(this);
	}
}