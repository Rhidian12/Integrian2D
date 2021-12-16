#pragma once

#include "../Integrian2D_API.h"
#include "Event/Event.h"

namespace Integrian2D
{
	class IListener;

	class INTEGRIAN2D_API EventQueue final
	{
	public:
		~EventQueue();

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

		class EventQueueImpl;

		EventQueue();

		EventQueueImpl* m_pEventQueueImpl;
	};
}
