#pragma once

#include "../BaseDecisionMaking/BaseDecisionMaking.h"

#include <functional>
#include <vector>

namespace Integrian2D
{
	class BehaviourTreeNode
	{
	public:
		virtual ~BehaviourTreeNode() = default;

		virtual BehaviourState Execute(Blackboard* const) const = 0;
	};

	class ActionNode final : public BehaviourTreeNode
	{
	public:
		using Action = std::function<BehaviourState(Blackboard* const)>;

		ActionNode(const Action& action);

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		Action m_Action;
	};

	class ConditionalNode final : public BehaviourTreeNode
	{
	public:
		using Predicate = std::function<bool(Blackboard* const)>;

		ConditionalNode(const Predicate& predicate);

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		Predicate m_Predicate;
	};

	class InvertedConditionalNode final : public BehaviourTreeNode
	{
	public:
		using Predicate = std::function<bool(Blackboard* const)>;

		InvertedConditionalNode(const Predicate& predicate);

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		Predicate m_Predicate;
	};

	class SequenceNode final : public BehaviourTreeNode
	{
	public:
		SequenceNode(const std::vector<BehaviourTreeNode*>& nodes);

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		std::vector<BehaviourTreeNode*> m_Nodes;
	};

	class BehaviourTree final : public BaseDecisionMaking
	{
	public:
		BehaviourTree(const std::vector<BehaviourTreeNode*>& nodes);
		~BehaviourTree();

		virtual BehaviourState Update(Blackboard* const pBlackboard) override;

	private:
		std::vector<BehaviourTreeNode*> m_Nodes;
		const BehaviourTreeNode* m_pCurrentNode;
	};
}