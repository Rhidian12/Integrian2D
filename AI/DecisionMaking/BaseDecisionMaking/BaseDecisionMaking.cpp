#include "BaseDecisionMaking.h"

namespace Integrian2D
{
	BaseDecisionMaking::BaseDecisionMaking(AIComponent* const pAIComponent)
		: m_pAIComponent{ pAIComponent }
		, m_CurrentState{ BehaviourState::Failure }
	{
	}

	BehaviourState BaseDecisionMaking::GetCurrentState() const noexcept
	{
		return m_CurrentState;
	}
}