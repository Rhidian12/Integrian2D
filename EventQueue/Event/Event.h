#pragma once

#include "EventImplementation.h"

namespace Integrian2D
{
	struct Event final
	{
		Event(const EventImplementation& _event, const int _delay);

		EventImplementation event;
		int delay;
		int delayCounter;
		bool isExecuted;
	};
}