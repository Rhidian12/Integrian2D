#pragma once

#include "../EventQueue/Event/Event.h"

namespace Integrian2D
{
	class IListener
	{
	public:
		IListener();
		virtual ~IListener() = default;

		virtual bool OnEvent(const Event&) = 0;

		bool m_IsActive;
	};
}