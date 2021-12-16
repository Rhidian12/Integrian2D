#pragma once

#include "../../../Integrian2D_API.h"
#include "../../BehaviourState.h"

namespace Integrian2D
{
	class AIComponent;
	class Blackboard;

	class BaseDecisionMaking 
	{
	public:
		INTEGRIAN2D_API BaseDecisionMaking();
		INTEGRIAN2D_API virtual ~BaseDecisionMaking() = default;

		INTEGRIAN2D_API virtual BehaviourState Update(Blackboard* const) = 0;

		INTEGRIAN2D_API BehaviourState GetCurrentState() const noexcept;

	protected:
		BehaviourState m_CurrentState;
	};
}