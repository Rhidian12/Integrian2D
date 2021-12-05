#include "FiniteStateMachine.h"

#include <algorithm>

namespace Integrian2D
{
	FiniteStateMachine::FiniteStateMachine(AIComponent* const pAIComponent, BaseDecisionMaking* const pStartState)
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

	BehaviourState FiniteStateMachine::Update(Blackboard* const pBlackboard)
	{
		if (m_pCurrentState)
		{
			switch (m_pCurrentState->Update(pBlackboard))
			{
			case BehaviourState::Failure:
				m_CurrentState = BehaviourState::Failure;
				break;
			case BehaviourState::Running:
				m_CurrentState = BehaviourState::Running;
				break;
			case BehaviourState::Success:
			{
				/* we need to know whether it's a State or a BHT */
				State* const pState{ dynamic_cast<State*>(m_pCurrentState) };
				if (pState)
				{
					/* it's a simple state in a FSM */
					auto it{ std::find_if(m_pTransitions.cbegin(), m_pTransitions.cend(), [pState](const Transition* const pT)->bool
						{
							return pState == pT->GetFrom();
						}) };

					/* If the transition's requirements are met, change the State */
					if ((*it)->Update(pBlackboard))
						m_pCurrentState = (*it)->GetTo();

					m_CurrentState = BehaviourState::Success;
					break;
				}

				/* TODO: ADD BHT */
			}
			}

			return m_CurrentState;
		}
		else
			return m_CurrentState = BehaviourState::Failure;
	}

	State::State(AIComponent* const pAIComponent, FiniteStateMachine* const pFSM, const Action& action)
		: BaseDecisionMaking{ pAIComponent }
		, m_pFSM{ pFSM }
		, m_Action{ action }
	{}

	BehaviourState State::Update(Blackboard* const pBlackboard)
	{
		return m_CurrentState = m_Action(pBlackboard);
	}

	FiniteStateMachine* const State::GetFiniteStateMachine() const noexcept
	{
		return m_pFSM;
	}

	const State::Action& State::GetAction() const noexcept
	{
		return m_Action;
	}

	Transition::Transition(FiniteStateMachine* const pFSM, State* const pFrom, State* const pTo, const Predicate& predicate)
		: m_pFSM{ pFSM }
		, m_Predicate{ predicate }
		, m_pFrom{ pFrom }
		, m_pTo{ pTo }
	{
	}

	bool Transition::Update(Blackboard* const pBlackboard)
	{
		return m_Predicate(pBlackboard);
	}

	FiniteStateMachine* const Transition::GetFiniteStateMachine() const noexcept
	{
		return m_pFSM;
	}

	State* const Transition::GetFrom() const noexcept
	{
		return m_pFrom;
	}

	State* const Transition::GetTo() const noexcept
	{
		return m_pTo;
	}
}