#pragma once

namespace Integrian2D
{
	class AIComponent;
	class Blackboard;

	enum class BehaviourState
	{
		Success = 0,
		Failure = 1,
		Running = 2
	};

	class BaseDecisionMaking 
	{
	public:
		BaseDecisionMaking(AIComponent* const pAIComponent);

		virtual BehaviourState Update(Blackboard* const) = 0;

		BehaviourState GetCurrentState() const noexcept;

	protected:
		AIComponent* m_pAIComponent;
		BehaviourState m_CurrentState;
	};
}