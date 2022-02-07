#include "EventImplementation.h"
#include "../../Utils/Utils.h"

#include <memory>

namespace Integrian2D
{
	EventImplementation::EventImplementation(const char* eventName)
		: m_Event{ eventName }
		, m_pData{}
	{}

	const char* EventImplementation::GetEvent() const noexcept
	{
		return m_Event;
	}
}