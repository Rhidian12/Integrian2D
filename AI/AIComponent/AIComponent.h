#pragma once

#include "../DecisionMaking/BaseDecisionMaking/BaseDecisionMaking.h"
#include "../../Components/Component/Component.h"

namespace Integrian2D
{
	class Blackboard;

	class AIComponent final : public Component
	{
	public:
		AIComponent(GameObject* const pOwner, Blackboard* const pBlackboard, BaseDecisionMaking* const pAI);
		~AIComponent();

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		virtual void Update() override;

		Blackboard* const GetBlackboard() const noexcept;
		BaseDecisionMaking* const GetDecisionMaking() const noexcept;
		BehaviourState GetCurrentState() const noexcept;

	private:
		Blackboard* m_pBlackboard;
		BaseDecisionMaking* m_pDecisionMaking;
	};
}