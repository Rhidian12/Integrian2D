#pragma once

#include "../../BehaviourState.h"

namespace Integrian2D
{
	class AIComponent;
	class Blackboard;

	class BaseDecisionMaking 
	{
	public:
		BaseDecisionMaking();
		virtual ~BaseDecisionMaking() = default;

		virtual BehaviourState Update(Blackboard* const) = 0;

		BehaviourState GetCurrentState() const noexcept;

	protected:
		BehaviourState m_CurrentState;
	};
}