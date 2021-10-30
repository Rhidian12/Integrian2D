#include "EventQueue.h"
#include "../IListener/IListener.h"

#include <algorithm>

namespace Integrian2D
{
	EventQueue::EventQueue()
		: m_Events{}
		, m_pListeners{}
	{}

	void EventQueue::QueueEvent(const Event& event) noexcept
	{
		m_Events.push_back(event);
	}

	void EventQueue::Update() noexcept
	{
		if (!m_Events.empty())
		{
			for (Event& event : m_Events)
				if (event.delay == 0 || event.delayCounter++ >= event.delay) /* If there is no delay or the delayCounter has exceeded the expected delay */
					for (IListener* const pListener : m_pListeners)
						if (pListener->m_IsActive)
							if (pListener->OnEvent(event))
								event.isExecuted = true;

			// Erase events that have been executed
			m_Events.erase(std::remove_if(m_Events.begin(), m_Events.end(), [](const Event& event)->bool
				{
					return event.isExecuted;
				}), m_Events.end());
		}
	}

	void EventQueue::AddListener(IListener* const pListener) noexcept
	{
		const std::vector<IListener*>::const_iterator cIt{ std::find(m_pListeners.cbegin(), m_pListeners.cend(), pListener) };

		if (cIt == m_pListeners.cend())
			m_pListeners.push_back(pListener);
	}

	void EventQueue::RemoveListener(IListener* const pListener) noexcept
	{
		const std::vector<IListener*>::const_iterator cIt{ std::find(m_pListeners.cbegin(), m_pListeners.cend(), pListener) };

		if (cIt != m_pListeners.cend())
			m_pListeners.erase(cIt);
	}

	bool EventQueue::AreAllEventsProcessed() const noexcept
	{
		return m_Events.empty();
	}
}