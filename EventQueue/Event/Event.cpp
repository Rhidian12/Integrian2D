#include "Event.h"

namespace Integrian2D
{
	Event::Event(const EventImplementation& _event, const int _delay)
		: event{ _event }
		, delay{ _delay }
		, delayCounter{}
		, isExecuted{}
	{}
}