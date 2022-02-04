#include "FiniteStateMachine.h"

#include "../BehaviourTree/BehaviourTree.h"
#include "../../../Utils/Utils.h"

#include <algorithm>

namespace Integrian2D
{
	FiniteStateMachine::FiniteStateMachine(Blackboard* const pBlackboard, FSMState* const pStartState)
		: BaseDecisionMaking{ pBlackboard }
		, m_pCurrentState{ pStartState }
	{
		m_pStates.push_back(pStartState);
	}

	FiniteStateMachine::FiniteStateMachine(const FiniteStateMachine& other) noexcept
		: BaseDecisionMaking{ other.m_pBlackboard }
		, m_pCurrentState{ other.m_pCurrentState }
	{
		for (FSMState* const pState : other.m_pStates)
			m_pStates.push_back(pState->Clone());

		for (Transition* const pTransition : other.m_pTransitions)
			m_pTransitions.push_back(pTransition->Clone());
	}

	FiniteStateMachine::FiniteStateMachine(FiniteStateMachine&& other) noexcept
		: BaseDecisionMaking{ std::move(other.m_pBlackboard) }
		, m_pCurrentState{ std::move(other.m_pCurrentState) }
		, m_pStates{ std::move(other.m_pStates) }
		, m_pTransitions{ std::move(other.m_pTransitions) }
	{
		other.m_pCurrentState = nullptr;
		other.m_pStates.clear();
		other.m_pTransitions.clear();
	}

	FiniteStateMachine& FiniteStateMachine::operator=(const FiniteStateMachine& other) noexcept
	{
		m_pCurrentState = other.m_pCurrentState;

		for (FSMState* const pState : other.m_pStates)
			m_pStates.push_back(pState->Clone());

		for (Transition* const pTransition : other.m_pTransitions)
			m_pTransitions.push_back(pTransition->Clone());

		return *this;
	}

	FiniteStateMachine& FiniteStateMachine::operator=(FiniteStateMachine&& other) noexcept
	{
		m_pCurrentState = std::move(other.m_pCurrentState);
		m_pStates = std::move(other.m_pStates);
		m_pTransitions = std::move(other.m_pTransitions);

		other.m_pCurrentState = nullptr;
		other.m_pStates.clear();
		other.m_pTransitions.clear();

		return *this;
	}

	FiniteStateMachine::~FiniteStateMachine()
	{
		for (Transition* pTransition : m_pTransitions)
			Utils::SafeDelete(pTransition);

		for (FSMState* pState : m_pStates)
			Utils::SafeDelete(pState);
	}

	BaseDecisionMaking* FiniteStateMachine::Clone() noexcept
	{
		return new FiniteStateMachine{ *this };
	}

	void FiniteStateMachine::AddState(FSMState* const pState) noexcept
	{
		m_pStates.push_back(pState);
	}

	void FiniteStateMachine::AddTransition(Transition* const pTransition) noexcept
	{
		m_pTransitions.push_back(pTransition);
	}

	BehaviourState FiniteStateMachine::Update()
	{
		if (m_pCurrentState)
		{
			switch (m_pCurrentState->Update(m_pBlackboard))
			{
			case BehaviourState::Failure:
				m_CurrentState = BehaviourState::Failure;
				break;
			case BehaviourState::Running:
				m_CurrentState = BehaviourState::Running;
				break;
			case BehaviourState::Success:
			{
				/* Find the state */
				auto it{ std::find_if(m_pTransitions.cbegin(), m_pTransitions.cend(), [this](const Transition* const pT)->bool
					{
						return m_pCurrentState == pT->GetFrom();
					}) };

				/* If the transition's requirements are met, change the State */
				if ((*it)->Update(m_pBlackboard))
					m_pCurrentState = (*it)->GetTo();

				m_CurrentState = BehaviourState::Success;
			}
			break;
			}

			return m_CurrentState;
		}
		else
			return m_CurrentState = BehaviourState::Failure;
	}

	FSMState::FSMState(FiniteStateMachine* const pFSM, const Action& action)
		: m_pFSM{ pFSM }
		, m_Action{ action }
	{}

	INTEGRIAN2D_API FSMState* FSMState::Clone() noexcept
	{
		return new FSMState{ m_pFSM, m_Action };
	}

	BehaviourState FSMState::Update(Blackboard* const pBlackboard)
	{
		return m_Action(pBlackboard);
	}

	FiniteStateMachine* const FSMState::GetFiniteStateMachine() const noexcept
	{
		return m_pFSM;
	}

	const FSMState::Action& FSMState::GetAction() const noexcept
	{
		return m_Action;
	}

	Transition::Transition(FiniteStateMachine* const pFSM, FSMState* const pFrom, FSMState* const pTo, const Predicate& predicate)
		: m_pFSM{ pFSM }
		, m_Predicate{ predicate }
		, m_pFrom{ pFrom }
		, m_pTo{ pTo }
	{
	}

	INTEGRIAN2D_API Transition* Transition::Clone() noexcept
	{
		return new Transition{ m_pFSM, m_pFrom, m_pTo, m_Predicate };
	}

	bool Transition::Update(Blackboard* const pBlackboard)
	{
		return m_Predicate(pBlackboard);
	}

	FiniteStateMachine* const Transition::GetFiniteStateMachine() const noexcept
	{
		return m_pFSM;
	}

	FSMState* const Transition::GetFrom() const noexcept
	{
		return m_pFrom;
	}

	FSMState* const Transition::GetTo() const noexcept
	{
		return m_pTo;
	}
}