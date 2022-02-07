#include "EventImplementation.h"
#include "../../Utils/Utils.h"

#include <memory>

namespace Integrian2D
{
	EventImplementation::EventImplementation(const std::string& eventName)
		: m_Event{ eventName.c_str() }
		, m_pData{}
	{}

	const char* EventImplementation::GetEvent() const noexcept
	{
		return m_Event;
	}
}