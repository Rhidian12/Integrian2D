#include "BehaviourTree.h"
#include "../../../Utils/Utils.h"

namespace Integrian2D
{
	BehaviourTree::BehaviourTree(const std::vector<BehaviourTreeNode*>& nodes)
		: m_Nodes{ nodes }
		, m_pCurrentNode{}
	{
	}

	BehaviourTree::~BehaviourTree()
	{
		for (BehaviourTreeNode*& pNode : m_Nodes)
			Utils::SafeDelete(pNode);
	}

#pragma region Rule Of 5
	BehaviourTree::BehaviourTree(const BehaviourTree& other) noexcept
		: m_Nodes{}
		, m_pCurrentNode{ other.m_pCurrentNode }
	{
		for (BehaviourTreeNode* const pNode : other.m_Nodes)
			m_Nodes.push_back(pNode->Clone());
	}

	BehaviourTree::BehaviourTree(BehaviourTree&& other) noexcept
		: m_Nodes{ std::move(other.m_Nodes) }
		, m_pCurrentNode{ std::move(other.m_pCurrentNode) }
	{
		other.m_Nodes.clear();
		other.m_pCurrentNode = nullptr;
	}

	BehaviourTree& BehaviourTree::operator=(const BehaviourTree& other) noexcept
	{
		for (BehaviourTreeNode* const pNode : other.m_Nodes)
			m_Nodes.push_back(pNode->Clone());

		m_pCurrentNode = other.m_pCurrentNode;

		return *this;
	}

	BehaviourTree& BehaviourTree::operator=(BehaviourTree&& other) noexcept
	{
		m_Nodes = std::move(other.m_Nodes);
		m_pCurrentNode = std::move(other.m_pCurrentNode);

		other.m_Nodes.clear();
		other.m_pCurrentNode = nullptr;

		return *this;
	}
#pragma endregion

	BaseDecisionMaking* BehaviourTree::Clone() noexcept
	{
		return new BehaviourTree{ m_Nodes };
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

	BehaviourTreeNode* Integrian2D::ActionNode::Clone() noexcept
	{
		return new ActionNode{ m_Action };
	}

	BehaviourState ActionNode::Execute(Blackboard* const pBlackboard) const
	{
		return m_Action(pBlackboard);
	}

	ConditionalNode::ConditionalNode(const Predicate& predicate)
		: m_Predicate{ predicate }
	{
	}

	BehaviourTreeNode* Integrian2D::ConditionalNode::Clone() noexcept
	{
		return new ConditionalNode{ m_Predicate };
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

	BehaviourTreeNode* Integrian2D::InvertedConditionalNode::Clone() noexcept
	{
		return new InvertedConditionalNode{ m_Predicate };
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

	SequenceNode::~SequenceNode()
	{
		for (BehaviourTreeNode* pNode : m_Nodes)
			Utils::SafeDelete(pNode);
	}

#pragma region Rule Of 5
	SequenceNode::SequenceNode(const SequenceNode& other) noexcept
		: m_Nodes{}
	{
		for (BehaviourTreeNode* const pNode : other.m_Nodes)
			m_Nodes.push_back(pNode->Clone());
	}

	SequenceNode::SequenceNode(SequenceNode&& other) noexcept
		: m_Nodes{ std::move(other.m_Nodes) }
	{
		other.m_Nodes.clear();
	}

	SequenceNode& SequenceNode::operator=(const SequenceNode& other) noexcept
	{
		for (BehaviourTreeNode* const pNode : other.m_Nodes)
			m_Nodes.push_back(pNode->Clone());

		return *this;
	}

	SequenceNode& SequenceNode::operator=(SequenceNode&& other) noexcept
	{
		m_Nodes = std::move(other.m_Nodes);
		other.m_Nodes.clear();

		return *this;
	}
#pragma endregion

	BehaviourTreeNode* Integrian2D::SequenceNode::Clone() noexcept
	{
		return new SequenceNode{ m_Nodes };
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