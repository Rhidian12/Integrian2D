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
		using Action = std::function<BehaviourState()>;

		State(AIComponent* const pAIComponent, FiniteStateMachine* const pFSM, const Action& action);

		virtual BehaviourState Update() override;

		FiniteStateMachine* const GetFiniteStateMachine() const noexcept;
		const Action& GetAction() const noexcept;
		const BehaviourState GetCurrentState() const noexcept;

	private:
		FiniteStateMachine* m_pFSM;
		Action m_Action;
		BehaviourState m_CurrentState;
	};

	class Transition final
	{
	public:
		using Predicate = std::function<bool()>;

		Transition(FiniteStateMachine* const pFSM, State* const pFrom, State* const pTo, const Predicate& predicate);

		bool Update();

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

		virtual BehaviourState Update() override;

	private:
		std::vector<BaseDecisionMaking*> m_pStates;
		std::vector<Transition*> m_pTransitions;

		BaseDecisionMaking* m_pCurrentState;
	};
}