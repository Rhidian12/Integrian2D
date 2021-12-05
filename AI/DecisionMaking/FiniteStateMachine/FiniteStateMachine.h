#pragma once

#include "../BaseDecisionMaking/BaseDecisionMaking.h"

namespace Integrian2D
{
	class FiniteStateMachine final : public BaseDecisionMaking
	{
	public:
		FiniteStateMachine(AIComponent* const pAIComponent);
	};
}