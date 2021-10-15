#include "Event.h"
#include "../../Utils/Utils.h"

namespace Integrian2D
{
	const std::string& Event::GetEvent() const noexcept
	{
		return m_Event;
	}
}