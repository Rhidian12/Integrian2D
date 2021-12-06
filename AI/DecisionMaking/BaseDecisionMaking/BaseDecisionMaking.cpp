#include "BaseDecisionMaking.h"

namespace Integrian2D
{
	BaseDecisionMaking::BaseDecisionMaking()
		: m_CurrentState{ BehaviourState::Failure }
	{
	}

	BehaviourState BaseDecisionMaking::GetCurrentState() const noexcept
	{
		return m_CurrentState;
	}
}