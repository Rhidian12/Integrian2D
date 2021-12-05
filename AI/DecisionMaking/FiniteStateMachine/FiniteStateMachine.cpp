#include "FiniteStateMachine.h"

namespace Integrian2D
{
	FiniteStateMachine::FiniteStateMachine(AIComponent* const pAIComponent, State* const pStartState)
		: BaseDecisionMaking{ pAIComponent }
		, m_pCurrentState{ pStartState }
	{
		m_pStates.push_back(pStartState);
	}

	void FiniteStateMachine::AddState(State* const pState) noexcept
	{
		m_pStates.push_back(pState);
	}

	void FiniteStateMachine::AddTransition(Transition* const pTransition) noexcept
	{
		m_pTransitions.push_back(pTransition);
	}

	void FiniteStateMachine::Update()
	{
	}

	State::State(AIComponent* const pAIComponent, FiniteStateMachine* const pFSM, const Action& action)
		: BaseDecisionMaking{ pAIComponent }
		, m_pFSM{ pFSM }
		, m_Action{ action }
		, m_CurrentState{ BehaviourState::Failure }
	{}

	void State::Update()
	{
		if (m_Action)	
			m_CurrentState = m_Action();
	}

	FiniteStateMachine* const State::GetFiniteStateMachine() const noexcept
	{
		return m_pFSM;
	}

	const State::Action& State::GetAction() const noexcept
	{
		return m_Action;
	}

	const BehaviourState State::GetCurrentState() const noexcept
	{
		return m_CurrentState;
	}

	Transition::Transition(FiniteStateMachine* const pFSM, State* const pFrom, State* const pTo, const Predicate& predicate)
		: m_pFSM{ pFSM }
		, m_Predicate{ predicate }
		, m_pFrom{ pFrom }
		, m_pTo{ pTo }
	{
	}

	bool Transition::Execute()
	{
		return m_Predicate();
	}
}