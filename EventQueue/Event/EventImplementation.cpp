#include "EventImplementation.h"
#include "../../Utils/Utils.h"

namespace Integrian2D
{
	const std::string& EventImplementation::GetEvent() const noexcept
	{
		return m_Event;
	}
}