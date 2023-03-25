#include "AIComponent.h"
#include "../../AI/Blackboard/Blackboard.h"
#include "../../AI/DecisionMaking/BaseDecisionMaking/BaseDecisionMaking.h"
#include "../../Utils/Utils.h"

namespace Integrian2D
{
	AIComponent::AIComponent(GameObject* const pOwner, Blackboard* const pBlackboard, BaseDecisionMaking* const pAI)
		: Component{ pOwner }
		, m_pBlackboard{ pBlackboard }
		, m_pDecisionMaking{ pAI }
	{}

	AIComponent::~AIComponent()
	{
		Utils::SafeDelete(m_pBlackboard);
		Utils::SafeDelete(m_pDecisionMaking);
	}

	void AIComponent::Update()
	{
		m_pDecisionMaking->Update();
	}

	Blackboard* const AIComponent::GetBlackboard() const noexcept
	{
		return m_pBlackboard;
	}

	BaseDecisionMaking* const AIComponent::GetDecisionMaking() const noexcept
	{
		return m_pDecisionMaking;
	}

	BehaviourState AIComponent::GetCurrentState() const noexcept
	{
		return m_pDecisionMaking->GetCurrentState();
	}
}