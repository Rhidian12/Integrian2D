#include "Event.h"
#include "../../Utils/Utils.h"

namespace Integrian2D
{
	Event::Event(Event&& other) noexcept
		: m_Event{ std::move(other.m_Event) }
		, m_pData{ std::move(other.m_pData) }
	{}

	Event& Event::operator=(Event&& other) noexcept
	{
		m_Event = std::move(other.m_Event);
		m_pData = std::move(other.m_pData);

		return *this;
	}

	Event::~Event()
	{
		Utils::SafeDelete(m_pData);
	}

	const std::string& Event::GetEvent() const noexcept
	{
		return m_Event;
	}
}