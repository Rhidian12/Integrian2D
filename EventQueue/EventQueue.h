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
		/* Queue an event to the EventQueue, this EventQueue operates on a principle of FIFO (First In, First Out) */
		void QueueEvent(const Event& event) noexcept;

		/* This function gets called interally and should NOT get called manually 
		   All events that were added before Update() gets called get executed, or their timer gets increased by 1
		   See Event for documentation regarding the event timer */
		void Update() noexcept;

		/* Add a Listener class that should receive events from the EventQueue */
		void AddListener(IListener* const pListener) noexcept;

		/* Remove a Listener class from the EventQueue */
		void RemoveListener(IListener* const pListener) noexcept;

		/* Check if all events have been processed */
		bool AreAllEventsProcessed() const noexcept;

	private:
		friend class Scene;

		EventQueue();

		std::vector<IListener*> m_pListeners;
		std::deque<Event> m_Events;
	};
}
