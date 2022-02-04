#include "BaseDecisionMaking.h"

#include "../../../Utils/Utils.h"

namespace Integrian2D
{
	BaseDecisionMaking::BaseDecisionMaking(Blackboard* const pBlackboard)
		: m_CurrentState{ BehaviourState::Failure }
		, m_pBlackboard{ pBlackboard }
	{
	}

	BaseDecisionMaking::~BaseDecisionMaking()
	{
		Utils::SafeDelete(m_pBlackboard);
	}

	BehaviourState BaseDecisionMaking::GetCurrentState() const noexcept
	{
		return m_CurrentState;
	}

	Blackboard* const BaseDecisionMaking::GetBlackboard() const noexcept
	{
		return m_pBlackboard;
	}
}