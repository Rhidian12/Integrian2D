#pragma once

#include "Event/Event.h"

#include <vector>
#include <deque>

namespace Integrian2D
{
	class IListener;

	class EventQueue final
	{
	public:
		void QueueEvent(const Event& event) noexcept;

		void Update() noexcept;

		void AddListener(IListener* const pListener) noexcept;
		void RemoveListener(IListener* const pListener) noexcept;

		bool AreAllEventsProcessed() const noexcept;

	private:
		friend class Scene;

		EventQueue();

		std::vector<IListener*> m_pListeners;
		std::deque<Event> m_Events;
	};
}
