#pragma once

namespace Integrian2D
{
	class AIComponent;

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

		virtual void Execute() noexcept = 0;

	protected:
		AIComponent* m_pAIComponent;
	};
}