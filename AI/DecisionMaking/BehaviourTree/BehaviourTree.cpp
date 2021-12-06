#include "BehaviourTree.h"

namespace Integrian2D
{
	BehaviourTree::BehaviourTree(const std::vector<BehaviourTreeNode*>& nodes)
		: m_Nodes{ nodes }
		, m_pCurrentNode{}
	{
	}

	BehaviourState BehaviourTree::Update(Blackboard* const pBlackboard)
	{
		auto it{ m_Nodes.cbegin() };
		auto end{ m_Nodes.cend() };

		for (; it != end; ++it)
		{
			if (m_pCurrentNode)
				if (m_pCurrentNode != *it)
					continue;

			switch ((*it)->Execute(pBlackboard))
			{
			case BehaviourState::Failure:
				m_pCurrentNode = nullptr;
				return BehaviourState::Failure;
			case BehaviourState::Running:
				m_pCurrentNode = *it;
				return BehaviourState::Running;
			case BehaviourState::Success:
				if (m_pCurrentNode)
					m_pCurrentNode = nullptr;
				break;
			}
		}

		return BehaviourState::Success;
	}

	ActionNode::ActionNode(const Action& action)
		: m_Action{ action }
	{
	}

	BehaviourState ActionNode::Execute(Blackboard* const pBlackboard) const
	{
		return m_Action(pBlackboard);
	}

	ConditionalNode::ConditionalNode(const Predicate& predicate)
		: m_Predicate{ predicate }
	{
	}

	BehaviourState ConditionalNode::Execute(Blackboard* const pBlackboard) const
	{
		if (m_Predicate(pBlackboard))
			return BehaviourState::Success;
		else
			return BehaviourState::Failure;
	}

	InvertedConditionalNode::InvertedConditionalNode(const Predicate& predicate)
		: m_Predicate{ predicate }
	{
	}

	BehaviourState InvertedConditionalNode::Execute(Blackboard* const pBlackboard) const
	{
		if (!m_Predicate(pBlackboard))
			return BehaviourState::Success;
		else
			return BehaviourState::Failure;
	}

	SequenceNode::SequenceNode(const std::vector<BehaviourTreeNode*>& nodes)
		: m_Nodes{ nodes }
	{
	}

	BehaviourState SequenceNode::Execute(Blackboard* const pBlackboard) const
	{
		for (const BehaviourTreeNode* const pNode : m_Nodes)
		{
			switch (pNode->Execute(pBlackboard))
			{
			case BehaviourState::Failure:
				return BehaviourState::Failure;
			case BehaviourState::Running:
				return BehaviourState::Running;
			case BehaviourState::Success:
				break;
			}
		}

		return BehaviourState::Success;
	}
}