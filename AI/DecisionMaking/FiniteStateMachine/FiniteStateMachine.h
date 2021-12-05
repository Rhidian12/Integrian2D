#pragma once

#include "../BaseDecisionMaking/BaseDecisionMaking.h"

#include <functional>
#include <vector>

namespace Integrian2D
{
	class FiniteStateMachine;

	class State final : public BaseDecisionMaking
	{
	public:
		using Action = std::function<BehaviourState(Blackboard* const)>;

		State(AIComponent* const pAIComponent, FiniteStateMachine* const pFSM, const Action& action);

		virtual BehaviourState Update(Blackboard* const pBlackboard) override;

		FiniteStateMachine* const GetFiniteStateMachine() const noexcept;
		const Action& GetAction() const noexcept;

	private:
		FiniteStateMachine* m_pFSM;
		Action m_Action;
	};

	class Transition final
	{
	public:
		using Predicate = std::function<bool(Blackboard* const)>;

		Transition(FiniteStateMachine* const pFSM, State* const pFrom, State* const pTo, const Predicate& predicate);

		bool Update(Blackboard* const pBlackboard);

		FiniteStateMachine* const GetFiniteStateMachine() const noexcept;
		State* const GetFrom() const noexcept;
		State* const GetTo() const noexcept;

	private:
		FiniteStateMachine* m_pFSM;
		Predicate m_Predicate;
		State* m_pFrom;
		State* m_pTo;
	};

	class FiniteStateMachine final : public BaseDecisionMaking
	{
	public:
		FiniteStateMachine(AIComponent* const pAIComponent, BaseDecisionMaking* const pStartState);

		void AddState(State* const pState) noexcept;
		void AddTransition(Transition* const pTransition) noexcept;

		virtual BehaviourState Update(Blackboard* const pBlackboard) override;

	private:
		std::vector<BaseDecisionMaking*> m_pStates;
		std::vector<Transition*> m_pTransitions;

		BaseDecisionMaking* m_pCurrentState;
	};
}